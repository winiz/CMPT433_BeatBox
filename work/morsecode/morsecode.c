/*
 * demo_miscdrv.c
 * - Demonstrate how to use a misc driver to easily create a file system link
 *      Author: Brian Fraser
 */
#include <linux/module.h>
#include <linux/miscdevice.h>		// for misc-driver calls.
#include <linux/fs.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

//#error Are we building this?

// Morse Code Encodings (from http://en.wikipedia.org/wiki/Morse_code)
//   Encoding created by Brian Fraser. Released under GPL.
//
// Encoding description:
// - msb to be output first, followed by 2nd msb... (left to right)
// - each bit gets one "dot" time.
// - "dashes" are encoded here as being 3 times as long as "dots". Therefore
//   a single dash will be the bits: 111.
// - ignore trailing 0's (once last 1 output, rest of 0's ignored).
// - Space between dashes and dots is one dot time, so is therefore encoded
//   as a 0 bit between two 1 bits.
//
// Example:
//   R = dot   dash   dot       -- Morse code
//     =  1  0 111  0  1        -- 1=LED on, 0=LED off
//     =  1011 101              -- Written together in groups of 4 bits.
//     =  1011 1010 0000 0000   -- Pad with 0's on right to make 16 bits long.
//     =  B    A    0    0      -- Convert to hex digits
//     = 0xBA00                 -- Full hex value (see value in table below)
//
// Between characters, must have 3-dot times (total) of off (0's) (not encoded here)
// Between words, must have 7-dot times (total) of off (0's) (not encoded here).
//
static unsigned short morsecode_codes[] = {
		0xB800,	// A 1011 1
		0xEA80,	// B 1110 1010 1
		0xEBA0,	// C 1110 1011 101
		0xEA00,	// D 1110 101
		0x8000,	// E 1
		0xAE80,	// F 1010 1110 1
		0xEE80,	// G 1110 1110 1
		0xAA00,	// H 1010 101
		0xA000,	// I 101
		0xBBB8,	// J 1011 1011 1011 1
		0xEB80,	// K 1110 1011 1
		0xBA80,	// L 1011 1010 1
		0xEE00,	// M 1110 111
		0xE800,	// N 1110 1
		0xEEE0,	// O 1110 1110 111
		0xBBA0,	// P 1011 1011 101
		0xEEB8,	// Q 1110 1110 1011 1
		0xBA00,	// R 1011 101
		0xA800,	// S 1010 1
		0xE000,	// T 111
		0xAE00,	// U 1010 111
		0xAB80,	// V 1010 1011 1
		0xBB80,	// W 1011 1011 1
		0xEAE0,	// X 1110 1010 111
		0xEBB8,	// Y 1110 1011 1011 1
		0xEEA0	// Z 1110 1110 101
};

#define MY_DEVICE_FILE  "morse-code"

// Define the toy data:
#define START_CHAR 'A'
#define END_CHAR   'z'
#define DATA_SIZE  (END_CHAR - START_CHAR + 1)
#define ASCII_OFFSET -65;
static char data[DATA_SIZE];


/******************************************************
 * Initialization of Data Function
 ******************************************************/
static void initialize_data(void)
{
	int i = 0;
	for (i = 0; i < DATA_SIZE; i++) {
		data[i] = i + START_CHAR;
	}
}

/******************************************************
 * Callbacks
 ******************************************************/
static ssize_t my_read(struct file *file,
		char *buff, size_t count, loff_t *ppos)
{
	int buffer_idx = 0;
	int data_idx = (int) *ppos;
	int bytes_read = 0;

	printk(KERN_INFO "demo_miscdrv::my_read(), buff size %d, f_pos %d\n",
			(int) count, (int) *ppos);

	// Fill buffer 1 byte at a time
	for (buffer_idx = 0; buffer_idx < count; buffer_idx++) {

		if (data_idx >= DATA_SIZE) {
			break;
		}

		// Copy next byte of data into user's buffer.
		// copy_to_user returns 0 for success (# of bytes not copied)
		if (copy_to_user(&buff[buffer_idx], &data[data_idx], 1)) {
			printk(KERN_ERR "Unable to write to buffer.");
			return -EFAULT;
		}


		data_idx++;
		bytes_read++;
	}

	// Write to in/out parameters and return:
	*ppos = data_idx;
	return bytes_read;  // # bytes actually read.
}

static ssize_t my_write(struct file *file,
		const char *buff, size_t count, loff_t *ppos)
{
	int buff_idx = 0;
	int temp = ASCII_OFFSET; 

	printk(KERN_INFO "demo_miscdrv: In my_write()\n");

	// printk the right morsecode_codes[x]
	for (buff_idx = 0; buff_idx < count; buff_idx++) {
		char ch;
		// Get the character
		if (copy_from_user(&ch, &buff[buff_idx], sizeof(ch))) {
			return -EFAULT;
		}

		if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)){
			// enforce upper case only
			if (ch >= 97 && ch <= 122){
				ch = ch - 32; 			
			}
			temp = temp + ch;
			// Process the character
			printk(KERN_INFO " is %c (%x), temp is %d \n", ch, morsecode_codes[temp],temp);	
			temp = ASCII_OFFSET;
		}
		

		// Skip special characters:
		else {
			continue;
		}
	}



	// Return # bytes actually written.
	*ppos += count;
	return count;
}

/******************************************************
 * Misc support
 ******************************************************/
// Callbacks:  (structure defined in /linux/fs.h)
struct file_operations my_fops = {
	.owner    =  THIS_MODULE,
	.read     =  my_read,
	.write    =  my_write,
};

// Character Device info for the Kernel:
static struct miscdevice my_miscdevice = {
		.minor    = MISC_DYNAMIC_MINOR,         // Let the system assign one.
		.name     = MY_DEVICE_FILE,             // /dev/.... file.
		.fops     = &my_fops                    // Callback functions.
};


/******************************************************
 * Driver initialization and exit:
 ******************************************************/
static int __init my_init(void)
{
	int ret;
	printk(KERN_INFO "----> demo_misc driver init(): file /dev/%s.\n", MY_DEVICE_FILE);

	// Register as a misc driver:
	ret = misc_register(&my_miscdevice);

	initialize_data();

	return ret;
}

static void __exit my_exit(void)
{
	printk(KERN_INFO "<---- demo_misc driver exit().\n");

	// Unregister misc driver
	misc_deregister(&my_miscdevice);
}

module_init(my_init);
module_exit(my_exit);

MODULE_AUTHOR("Brian Fraser");
MODULE_DESCRIPTION("Demo driver to return some ascii data, and reverse a string to printk.");
MODULE_LICENSE("GPL");
