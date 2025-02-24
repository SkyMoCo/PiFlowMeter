# Makefile for flowsensor

CC = gcc
CFLAGS = -Wall -Wextra -O2 -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LDLIBS = -lwiringPi
TARGET = flowmeter
SRCS = flowsensor.c

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET) $(SRCS) $(LDLIBS)

clean:
	rm -f $(TARGET)

.PHONY: all clean

