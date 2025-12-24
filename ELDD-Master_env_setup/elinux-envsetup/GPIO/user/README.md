
## GPIO @ User space: REAL ASSIGNMENT

### Lab Exp 27: gpio command in Linux command prompt

    Implement your own version of gpio command in Linux that works same as u-boot command prompt.
    Example: $ gpio <set|clear|toggle> <pin>
    
    $ gpio set 10
    
    1. echo 10 > export
    
    void gpio_export(int pin)
    {
    fd = open (“/sys/class/gpio/export”, O_WRONLY)
    Write (fd, pin ,1024);
    Close(fd);
    }
    
    
    2. echo out > direction
    
    void gpio_direction(int pin, char *buff)
    {
    char buf[50];
    sprintf(buf, “/sys/class/gpio/gpio%d/direction”,pin)
    fd = Open (buf, O_WRONLY)
    Write (fd, buff,1024);
    Close(fd);
    }
    
    
    3. echo 1 > value
    
    fd = Open (“/sys/class/gpio/gpio10/value”, O_WRONLY)
    Write (fd,1,1024);
    Close(fd);
    
    4. echo 10 > unexport
    
    void gpio_export(int pin)
    {
    fd = Open (“/sys/class/gpio/unexport”, O_WRONLY)
    Write (fd, pin,1024);
    Close(fd);
    }
