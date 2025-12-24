## I2C Utility

    I2C Utility is an userspace driver useful to troubleshooting or diagnostics Linux I2C Subsystem.

### How to cross build I2C Utility

    $ arm-linux-gnueabihf-gcc i2c-app.c smbus.c -I include/ -o i2c-app

### How to test I2C Utility

    $ ./i2c-app.c <r/w> <word-adress> [length]