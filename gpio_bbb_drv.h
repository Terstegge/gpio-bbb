#ifndef GPIO_BBB_DRV_H
#define GPIO_BBB_DRV_H

#include "gpio_interface.h"
#include <thread>

#define GPIO_COUNT 128

class gpio_bbb_drv : public gpio_interface {

  public:
    gpio_bbb_drv() : _fd(0) { }

    /* Lifecycle methods */
    void begin();
    void end();

    /* Basic GPIO handling */
    void pinMode      (uint8_t gpio, uint16_t mode);
    bool digitalRead  (uint8_t gpio);
    void digitalWrite (uint8_t gpio, bool value);

    /* Interrupt handling */
    void attachInterrupt (uint8_t gpio, void (*)(uint8_t gpio), uint16_t mode);
    void detachInterrupt (uint8_t gpio);
    void enableInterrupt (uint8_t gpio);
    void disableInterrupt(uint8_t gpio);

    /* Misc. functionality */      
    void setDebounce (uint8_t gpio, uint16_t usdelay);

  private:
    void        irq_handler();
    std::thread irq_thread;
    void (*usrHandler[GPIO_COUNT])(uint8_t irq);

    int  _fd;
};

#endif

