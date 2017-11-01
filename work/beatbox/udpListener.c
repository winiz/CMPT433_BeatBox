// udpListener.c
#include "udpListener.h"
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>			// for strncmp()
#include <unistd.h>			// for close()
#include <pthread.h>
#include <stdbool.h>

#define UDP_PORT 12345
#define MAX_RECEIVE_MESSAGE_LENGTH 1024
#define REPLY_BUFFER_SIZE (1500)
#define VALUES_PER_LINE 4

#define COMMAND_HELP        "help"
#define COMMAND_COUNT       "count"
#define COMMAND_GET_LENGTH  "get length"
#define COMMAND_GET_ARRAY   "get array"
#define COMMAND_GET         "get"
#define COMMAND_STOP        "stop"

static pthread_t s_threadId;
static char replyBuffer[REPLY_BUFFER_SIZE];

// Header
static void *udpListeningThread(void *args);
static void processUDPCommand(char* udpCommand, int socketDescriptor, struct sockaddr_in *pSin);
//static int secondWordToInt(char *string);
//static void concatValuesToString(char *targetBuffer, int data[], int indexStart, int indexEnd);

void UdpListener_startListening(void)
{
	pthread_create(&s_threadId, NULL, &udpListeningThread, NULL);
}

void UdpListener_cleanup(void)
{
	pthread_join(s_threadId, NULL);
}

/*
 *	On the host:
 *		> netcat -u 192.168.0.171 12345
 *		(Change the IP address to your board)
 *
 *	On the host, type in a command and press enter:
 *		help<Enter>
 *
 */



static void *udpListeningThread(void *args)
{
	// Buffer to hold packet data:
	char message[MAX_RECEIVE_MESSAGE_LENGTH];

	// Address
	struct sockaddr_in sin;
	unsigned int sin_len;						// May change.
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);	// Host to Network long
	sin.sin_port = htons(UDP_PORT);				// Host to Network short

	// Create the socket for UDP
	int socket_descriptor = socket(PF_INET, SOCK_DGRAM, 0);

	// Bind the socket to the port that we specify
	bind(socket_descriptor, (struct sockaddr*) &sin, sizeof(sin));

	while (1) {
		// Get the data (blocking)
		// Will change sin (the address) to be the address of the client.
		sin_len = sizeof(sin);
		int bytesRx = recvfrom(socket_descriptor, message, MAX_RECEIVE_MESSAGE_LENGTH, 0,
				(struct sockaddr *) &sin, &sin_len);

		// Make it null terminated (so string functions work):
		message[bytesRx] = 0;
		//printf("Message received (%d bytes): \n\n'%s'\n", bytesRx, message);

		processUDPCommand(message, socket_descriptor, &sin);

		// Transmit a reply (if desired):
		if (strnlen(replyBuffer, REPLY_BUFFER_SIZE) > 0) {
			sin_len = sizeof(sin);
			sendto( socket_descriptor,
				replyBuffer, strnlen(replyBuffer, REPLY_BUFFER_SIZE),
				0,
				(struct sockaddr *) &sin, sin_len);
		}
	}

	// Close socket on shut-down
	close(socket_descriptor);
	return NULL;
}

_Bool isUdpThisCommand(char* udpMessage, const char* command)
{
	return strncmp(udpMessage, command, strlen(command)) == 0;
}


static void processUDPCommand(char* udpCommand, int socketDescriptor, struct sockaddr_in *pSin)
{
	//TODO
}

//static int secondWordToInt(char *string)
//{
//	// Default to a 1 if nothing.
//	int value = 1;
//	sscanf(string, "%*s%d", &value);
//	return value;
//}
//
//static void concatValuesToString(char *targetBuffer, int data[], int indexStart, int indexEnd)
//{
//	const int TMP_STR_MAX_LEN = 20;
//	const int PRIMES_PER_LINE = 10;
//	char newNumStr[TMP_STR_MAX_LEN];
//	int count = 0;
//	for (int i = indexStart; i <= indexEnd; i++) {
//		// Handle line feeds:
//		if (count != 0 && count % PRIMES_PER_LINE == 0) {
//			strncat(targetBuffer, "\n", REPLY_BUFFER_SIZE - strlen(targetBuffer) - 1);
//		}
//		count ++;
//
//		sprintf(newNumStr, "%d, ", data[i]);
//		strncat(targetBuffer, newNumStr, REPLY_BUFFER_SIZE - strlen(targetBuffer) - 1);
//	}
//	// End with a \n
//	strncat(targetBuffer, "\n", REPLY_BUFFER_SIZE - strlen(targetBuffer) - 1);
//}


