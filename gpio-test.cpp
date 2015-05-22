#include "gpio_bbb_drv.h"
#include <iostream>
using namespace std;

// This example demonstrates the use of a irq-handler in
// user space: The GPIO-53 (LED USR0 -> 'heartbeat') is
// used for generating interrupts, which are then mirrored
// on a second LED on GPIO-68

#define USR0    53
#define RED_LED 68

gpio_bbb_drv gpio;

void handler(uint8_t pin) {
  gpio.digitalWrite( RED_LED , gpio.digitalRead(pin) );
  gpio.enableInterrupt(pin);
}

int main() {
  gpio.begin();

  // Note: On already requested GPIOs (using overlays or
  // sys-fs exports, the only thing we may do is switch on
  // the receiver with GPIO::INPUT...
  gpio.pinMode( USR0,    GPIO::INPUT);
  gpio.pinMode( RED_LED, GPIO::OUTPUT);

  gpio.attachInterrupt( 53, handler, GPIO::RISING | GPIO::FALLING);
  
  sleep(10);

  gpio.detachInterrupt( 53);

  gpio.end();
}

