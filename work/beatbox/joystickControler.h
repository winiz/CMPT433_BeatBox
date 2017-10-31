#ifndef JOYSTICKCONTROLER_H
#define JOYSTICKCONTROLER_H

#define GPIO_EXPORT_PATH "/sys/class/gpio/export"
#define JOYSTICK_GPIO_VALUE_PATH_UP "/sys/class/gpio/gpio26/value"
#define JOYSTICK_GPIO_VALUE_PATH_RIGHT "/sys/class/gpio/gpio47/value"
#define JOYSTICK_GPIO_VALUE_PATH_DOWN "/sys/class/gpio/gpio46/value"
#define JOYSTICK_GPIO_VALUE_PATH_LEFT "/sys/class/gpio/gpio65/value"
#define JOYSTICK_GPIO_VALUE_PATH_IN "/sys/class/gpio/gpio27/value"

#define JOYSTICK_GPIO_VALUE_UP 26
#define JOYSTICK_GPIO_VALUE_RIGHT 47
#define JOYSTICK_GPIO_VALUE_DOWN 46
#define JOYSTICK_GPIO_VALUE_LEFT 65
#define JOYSTICK_GPIO_VALUE_IN 27

#define MIN_VOL 0
#define MAX_VOL 100

void joystickControler_init(void);
_Bool checkIfPressed(char *fileName);
void joystickControler_cleanup(void);
void busyWait(void);

#endif