#include "gpio_bbb_drv.h"
#include "gpio_bbb.h"
#include <fcntl.h>
#include <sys/ioctl.h>
#include <cstring>
#include <cerrno>
#include <string>
#include <iostream>

#define GPIO_DEV "/dev/gpio_bbb"

class gpio_exception : public std::exception {
  public:
    gpio_exception (std::string msg, int err) {
      _msg = msg + strerror(abs(err));
    }
    ~gpio_exception () throw() { }
    const char* what() const throw() {
      return _msg.c_str();
    }
  private:
    std::string _msg;
};

void gpio_bbb_drv::irq_handler() {
  std::cout << "Starting irq thread" << std::endl;
  while (true) {
    int gpio = read(_fd, NULL, 0);
    if (gpio < 0 || gpio >= GPIO_COUNT) break;
    usrHandler[gpio](gpio);
  }
  std::cout << "Stopping irq thread" << std::endl;
}

void gpio_bbb_drv::begin () {
  // Open the GPIO device
  _fd = open(GPIO_DEV, O_RDWR );
  if( _fd < 0 ) {
    throw gpio_exception("Cannot open "GPIO_DEV", ", errno);
  }
  // Start the irq thread
  irq_thread = std::thread([&](){ irq_handler();} );
}

void gpio_bbb_drv::end () {
  // Stop the irq thread
  write(_fd, NULL, 0);
  irq_thread.join();
  close(_fd);
}

void gpio_bbb_drv::pinMode (uint8_t gpio, uint16_t mode) {
  if (gpio >= GPIO_COUNT) {
    throw gpio_exception("GPIO number out of range, ", EINVAL);
  }
  int ret = ioctl(_fd, IOCTL_PIN_MODE, GPIO_DATA(gpio, mode));
  if (ret < 0) {
    throw gpio_exception("Error in pinMode, ", ret);
  }
}

bool gpio_bbb_drv::digitalRead (uint8_t gpio) {
  return ioctl(_fd, IOCTL_DIGITAL_READ, gpio);
}

void gpio_bbb_drv::digitalWrite (uint8_t gpio, bool value) {
  int ret = ioctl(_fd, IOCTL_DIGITAL_WRITE, GPIO_DATA(gpio, value));
  if (ret < 0) {
    throw gpio_exception("Error in digitalWrite, ", ret);
  }
}

void gpio_bbb_drv::attachInterrupt (uint8_t gpio, void (*f)(uint8_t gpio), uint16_t mode) {
  if (gpio >= GPIO_COUNT) {
    throw gpio_exception("GPIO number out of range, ", EINVAL);
  }
  int ret = ioctl(_fd, IOCTL_ATTACH_INTERRUPT, GPIO_DATA(gpio, mode));
  if (ret < 0) {
    throw gpio_exception("Error in attachInterrupt, ", ret);
  }
  usrHandler[gpio] = f;
  enableInterrupt(gpio);
}

void gpio_bbb_drv::detachInterrupt (uint8_t gpio) {
  disableInterrupt(gpio);
  usrHandler[gpio] = 0;
  int ret = ioctl(_fd, IOCTL_DETACH_INTERRUPT, gpio);
  if (ret < 0) {
    throw gpio_exception("Error in detachInterrupt, ", ret);
  }
}

void gpio_bbb_drv::enableInterrupt (uint8_t gpio) {
  int ret = ioctl(_fd, IOCTL_ENABLE_INTERRUPT, gpio);
  if (ret < 0) {
    throw gpio_exception("Error in enableInterrupt, ", ret);
  }
}

void gpio_bbb_drv::disableInterrupt(uint8_t gpio) {
  int ret = ioctl(_fd, IOCTL_DISABLE_INTERRUPT, gpio);
  if (ret < 0) {
    throw gpio_exception("Error in disableInterrupt, ", ret);
  }
}

void gpio_bbb_drv::setDebounce (uint8_t gpio, uint16_t usdelay) {
  int ret = ioctl(_fd, IOCTL_SET_DEBOUNCE, GPIO_DATA(gpio, usdelay));
  if (ret < 0) {
    throw gpio_exception("Error in setDebounce, ", ret);
  }
}

