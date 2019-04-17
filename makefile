GCC := arm-linux-gnueabihf-gcc
OUTPUT := gpioBtn
SOURCES := $(wildcard *.c)
CCFLAGS := -Wall

all: 
	$(GCC) -o $(OUTPUT) $(CCFLAGS) $(SOURCES)

clean:
	rm $(OUTPUT)
	

 
