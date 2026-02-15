AUTOMAKE_OPTIONS = foreign

include_HEADERS = lcd.h gpio.h

bin_PROGRAMS = helloworld

helloworld_SOURCES = \
    HelloWorld.c \
    lcd.c \
    gpio.c

# Add extra flags WITHOUT overriding Yocto's CFLAGS
AM_CFLAGS = -Wall -pedantic

