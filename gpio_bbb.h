/*
 *  gpio_bbb.h - the header file with the ioctl definitions.
 *
 */

#ifndef GPIO_BBB_H
#define GPIO_BBB_H

#include <linux/ioctl.h>

#define GPIO_INPUT 	 0x0001
#define GPIO_OUTPUT      0x0002
#define GPIO_PULLUP      0x0004
#define GPIO_PULLDOWN    0x0008
#define GPIO_SLOW        0x0010
#define GPIO_FAST        0x0020
#define GPIO_OPEN_DRAIN  0x0040
#define GPIO_OPEN_SOURCE 0x0080
#define GPIO_INIT_HIGH   0x0100
#define GPIO_INIT_LOW    0x0200
#define GPIO_REQUESTED   0x8000

#define GPIO_RISING      0x0001
#define GPIO_FALLING     0x0002
#define GPIO_LEVEL_HIGH  0x0004
#define GPIO_LEVEL_LOW   0x0008

#define GPIO_DATA(gpio, data) (((data) << 8) | (gpio))

/* 
 * The name of the device file 
 */
#define DEVICE_NAME "gpio_bbb"

/* 
 * The major IOCTL 'magic' number.
 */
#define MAJOR_NUM 100

#define IOCTL_PIN_MODE          _IOW(MAJOR_NUM, 0, unsigned long)
#define IOCTL_DIGITAL_READ      _IOW(MAJOR_NUM, 1, unsigned long)
#define IOCTL_DIGITAL_WRITE     _IOW(MAJOR_NUM, 2, unsigned long)
#define IOCTL_ATTACH_INTERRUPT  _IOW(MAJOR_NUM, 3, unsigned long)
#define IOCTL_DETACH_INTERRUPT  _IOW(MAJOR_NUM, 4, unsigned long)
#define IOCTL_ENABLE_INTERRUPT  _IOW(MAJOR_NUM, 5, unsigned long)
#define IOCTL_DISABLE_INTERRUPT _IOW(MAJOR_NUM, 6, unsigned long)
#define IOCTL_SET_DEBOUNCE      _IOW(MAJOR_NUM, 7, unsigned long)

#endif

