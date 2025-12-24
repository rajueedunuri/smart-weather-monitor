### Kernel Space Debugging Techniques - Lab Assignments

#### Experiment 22 : Kernel Panic
    
    cross compile panic module and Load in to kernel and collect oops message. 
    
    Analyze oops message and copy oops message in text file, findout which line in source code creare a painc using addr2line and gdb.
    


#### Experiment 23 : Kprobe

    Add "omap_gpio_get" fucntion in krrobe structure and croos compile module and load in to kernel. 
    
    Read gpio pin from sysfs file system then "omap_gpio_get" fucntion invoke.
    
        $ sudo su
        # cd /sys/class/gpio
        # cat value
        
    Run dmesg command and collect the pre handler, post handler and stack trace output.

