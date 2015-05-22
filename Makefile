CPPFLAGS += -std=c++0x -Wall
obj-m    += gpio_bbb.o

all:	gpio-test
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
	
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	rm -f *~ *.o
	
gpio-test: gpio-test.o gpio_bbb_drv.o
	g++ -o gpio-test $^ -pthread
