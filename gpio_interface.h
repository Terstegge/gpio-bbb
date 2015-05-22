#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include <cstdint>

/* Error handling is an implementation decision: A GPIO
   class on smaller microcontrollers might not perform
   any error handling, but an advanced platform like a
   linux-based board might throw exceptions...
*/

namespace GPIO {
  /* pin modes */
  const uint16_t  INPUT       = 0x0001;
  const uint16_t  OUTPUT      = 0x0002;
  const uint16_t  PULLUP      = 0x0004;
  const uint16_t  PULLDOWN    = 0x0008;
  const uint16_t  SLOW        = 0x0010;
  const uint16_t  FAST        = 0x0020;
  const uint16_t  OPEN_DRAIN  = 0x0040;
  const uint16_t  OPEN_SOURCE = 0x0080;
  const uint16_t  INIT_HIGH   = 0x0100;
  const uint16_t  INIT_LOW    = 0x0200;
  /* irq trigger */
  const uint16_t  RISING      = 0x0001;
  const uint16_t  FALLING     = 0x0002;
  const uint16_t  LEVEL_HIGH  = 0x0004;
  const uint16_t  LEVEL_LOW   = 0x0008;
}

class gpio_interface {

  public:
    /* Lifecycle methods */
    virtual void begin() = 0;
    virtual void end() = 0;

    /* Basic GPIO handling */
    virtual void pinMode      (uint8_t gpio, uint16_t mode) = 0;
    virtual bool digitalRead  (uint8_t gpio) = 0;
    virtual void digitalWrite (uint8_t gpio, bool value) = 0;

    /* Interrupt handling */
    virtual void attachInterrupt (uint8_t gpio, void (*)(uint8_t gpio), uint16_t mode) = 0;
    virtual void detachInterrupt (uint8_t gpio) = 0;
    virtual void enableInterrupt (uint8_t gpio) = 0;
    virtual void disableInterrupt(uint8_t gpio) = 0;

    /* Misc. functionality */      
    virtual void setDebounce (uint8_t gpio, uint16_t usdelay) = 0;

};

#endif


