### Experiment 32: RTC framework

#### 32a. RTC Initalization framework

    km@KM-BBB:~$ ls -l /dev/rtc
    rtc   rtc0  rtc1  
    km@KM-BBB:~$ dmesg | grep rtc
    [    1.971308] hctosys: unable to open rtc device (rtc0)
    [   11.011539] omap_rtc 44e3e000.rtc: registered as rtc0
    [   12.333133] rtc-ds1307 1-0068: probe
    [   12.424087] rtc-ds1307 1-0068: registered as rtc1
    [   12.429733] i2c-core: driver [rtc-ds1307] registered
    
    km@KM-BBB:~$ lsmod | grep rtc
    rtc_ds1307             24576  0
    hwmon                  16384  1 rtc_ds1307
    rtc_omap               20480  1


<img src="images/i2c_rtc_init_framework_kernel.jpg">


#### 32b. RTC Operation framework (/dev/rtc1) using KGDB.

    Assign a brreakpoint in "ds1307_get_time" function and run the below application and run bt command and collet the log.
    
    $ ./time_get
    
    Current RTC Date/Time: 25-7-2020 11:48:03                                                                                                                                              
    ioctl(fd,RTC_RDTIME,&time);
    

<img src="images/i2c_rtc_op_framework_kernel.jpg">

    
    260.122014] drivers/rtc/rtc-dev.c:rtc_dev_ioctl:325
    [  260.127198] drivers/rtc/interface.c:rtc_read_time:117
    [  260.132667] drivers/rtc/interface.c:__rtc_read_time:90
    [  260.137951] drivers/rtc/rtc-ds1307.c:ds1307_get_time:416                                                                                                                            
    -----------------------------------------------------------------------
    [  260.143303] drivers/base/regmap/regmap.c:regmap_bulk_read:2722
    [  260.149247] drivers/base/regmap/regmap.c:regmap_raw_read:2514       
    ----------------------------------------------------------------------                                                                                                                
    [  260.155100] i2c i2c-1: master_xfer[0] W, addr=0x68, len=1
    [  260.155142] i2c i2c-1: master_xfer[1] R, addr=0x68, len=7
    [  260.155219] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_irq:848
    [  260.161509] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_common:808
    [  260.168086] omap_i2c 4802a000.i2c: addr: 0x0068, len: 1, flags: 0x0, stop: 0                                                                                                        
    [  260.168910] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0010)
    [  260.169231] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)                                                                                                                               
    [  260.191278] omap_i2c 4802a000.i2c: addr: 0x0068, len: 7, flags: 0x1, stop: 1                                                                                                        
    [  260.192159] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0008)
    [  260.192200] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)                                                                                                                               
    [  260.192444] rtc-ds1307 1-0068: read: 03 48 11 04 25 07 20
    [  260.192468] rtc-ds1307 1-0068: read secs=3, mins=48, hours=11, mday=25, mon=6, year=120, wday=3   
    
    
#### RTC Opeation framework (/dev/i2c-1)


    ./app/i2c-dev/i2c-dev-rtc.c:  read sec,min. hours from /dev/i2c-1
    
     int fd = open("/dev/i2c-1", O_RDWR);
    
            i2c_data.nmsgs = 2;
            i2c_data.msgs = msg;
    
            i2c_data.msgs[0].addr = 0x68;
            i2c_data.msgs[0].len = 1;
            i2c_data.msgs[0].flags = 0;
            i2c_data.msgs[0].buf = rtc_addr;
    
            i2c_data.msgs[1].addr = 0x68;
            i2c_data.msgs[1].len = 3;
            i2c_data.msgs[1].flags = I2C_M_RD;
            i2c_data.msgs[1].buf = rtc_data;
    
            if (ioctl(fd, I2C_RDWR, &i2c_data) < 0)
    
    ---------------------------------------------------------------------------------------
    
    
    run application
    $ ./i2c_rtc
    data = 57, 1, 19                                                                                                                                                                       
    
    $ dmesg
    ---------------------------------------------------------------------------------------
    [ 2590.042492] i2c i2c-1: ioctl, cmd=0x707, arg=0xbeea9be4                                                                                                                             
    	cmd -> I2C_RDWR
    [ 2590.042541] i2c i2c-1: master_xfer[0] W, addr=0x68, len=1                                                                                                                           
    [ 2590.042555] i2c i2c-1: master_xfer[1] R, addr=0x68, len=3   
    ---------------------------------------------------------------------------------
    [ 214.305040] omap_i2c 4802a000.i2c: addr: 0x0068, len: 1, flags: 0x200, stop: 0                                                                                                      
    [ 2590.042930] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0010)         
    		0x0010 -> 4th Bit Set (XRDY)                                                                                                                      
    [ 2590.043126] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)            
    		0x0004 -> 2nd bit set (ARDY)             
                                                                                                          
    [ 2590.043209] omap_i2c 4802a000.i2c: addr: 0x0068, len: 3, flags: 0x201, stop: 1                                                                                                      
    [ 2590.043641] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0008)           
    		0x0008 -> 3rd Bit Set (RRDY)                                                                                                                      
    [ 2590.043673] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)    
    		0x0004 -> 2nd bit set (ARDY)  



