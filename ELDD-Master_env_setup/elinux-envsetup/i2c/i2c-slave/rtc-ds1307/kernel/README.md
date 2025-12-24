
### Linux RTC Subsystem Framework

#### RTC Device operation - To read RTC date & time

 	--------------------[ RTC App ] ------------------------------------------------
	
	ioctl(fd,RTC_RDTIME,&tm);

    --------------------[ RTC App -> RTC HDD (RTC-DEV - Character Device Driver) ]----
  	
	drivers/rtc/rtc-dev.c:rtc_dev_ioctl():327 
	drivers/rtc/interface.c:rtc_read_time():120 
	drivers/rtc/interface.c:__rtc_read_time():96

    struct rtc_class_ops {
            int (*ioctl)(struct device *, unsigned int, unsigned long);
            int (*read_time)(struct device *, struct rtc_time *);
            int (*set_time)(struct device *, struct rtc_time *);
            int (*read_alarm)(struct device *, struct rtc_wkalrm *);
            int (*set_alarm)(struct device *, struct rtc_wkalrm *);
            int (*proc)(struct device *, struct seq_file *);
            int (*set_mmss64)(struct device *, time64_t secs);
            int (*set_mmss)(struct device *, unsigned long secs);
            int (*read_callback)(struct device *, int data);
            int (*alarm_irq_enable)(struct device *, unsigned int enabled);
            int (*read_offset)(struct device *, long *offset);
            int (*set_offset)(struct device *, long offset);
            int (*power_off_program)(struct device *dev);
    };

 	drivers/rtc/interface.c 
	96           err = rtc->ops->read_time(rtc->dev.parent, tm);

    --------------------[ RTC HDD -> RTC LDD (I2C Slave/Client Driver) ]---------------

	rtc-ds1307.c:ds1307_get_time():418 -> 
	drivers/base/regmap/regmap.c:regmap_bulk_read():2727 -> 
	drivers/base/regmap/regmap.c:regmap_raw_read():2546 -> 
	drivers/base/regmap/regmap.c:_regmap_raw_read(): 2400

     --------------------[ RTC LDD -> I2C REGMAP ]---------------------------------------

     static struct regmap_bus regmap_i2c = {
         .write = regmap_i2c_write,
         .gather_write = regmap_i2c_gather_write,
         .read = regmap_i2c_read,
         .reg_format_endian_default = REGMAP_ENDIAN_BIG,
         .val_format_endian_default = REGMAP_ENDIAN_BIG,
     };
	drivers/base/regmap/regmap-i2c.c:regmap_i2c_read():195

	 --------------------[ I2C REGMAP -> I2C CORE ]-----------------------------------------
     
	drivers/i2c/i2c-core-base.c:i2c_transfer():2056
	drivers/i2c/i2c-core-base.c: __i2c_transfer:1986
	1986                         ret = adap->algo->master_xfer(adap, msgs, num);

     --------------------[ I2C CORE -> I2C Master/Adapter Driver ]---------------------------

	drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_common():832
	drivers/i2c/busses/i2c-omap.c:omap_i2c_wait_for_bb:525
	drivers/i2c/busses/i2c-omap.c:omap_i2c_read_reg:525



### Assign a breakpoint in omap_i2c_read_reg() function and run rtc test application. 

	#0  omap_i2c_read_reg (reg=<optimized out>, omap=<optimized out>) at drivers/i2c/busses/i2c-omap.c:525
	#1  omap_i2c_wait_for_bb (omap=0xde166040) at drivers/i2c/busses/i2c-omap.c:525
	#2  0xc07007f4 in omap_i2c_xfer_common (adap=<optimized out>, msgs=0xdb2efd3c, num=2, polling=false) at drivers/i2c/busses/i2c-omap.c:832
	#3  0xc06fab88 in __i2c_transfer (adap=0xde1660a0, msgs=0xdb2efd3c, num=2)
    at drivers/i2c/i2c-core-base.c:1986
	#4  0xc06faf40 in i2c_transfer (adap=0xde1660a0, msgs=0xdb2efd3c, num=2)
    at drivers/i2c/i2c-core-base.c:2056
	#5  0xc062c1d8 in regmap_i2c_read (context=<optimized out>, reg=<optimized out>, 
    reg_size=<optimized out>, val=<optimized out>, val_size=<optimized out>)
    at drivers/base/regmap/regmap-i2c.c:195
	#6  0xc062766c in _regmap_raw_read (map=0xde166040, reg=3709703168, val=<optimized out>, 
    val_len=3909378999) at drivers/base/regmap/regmap.c:2400
	#7  0xc0627a44 in regmap_raw_read (map=0xdd1d9400, reg=0, val=0xdb2efe2d, val_len=7)
    at drivers/base/regmap/regmap.c:2546
	#8  0xc0627cc0 in regmap_bulk_read (map=0xdd1d9400, reg=0, val=0xdb2efe2d, val_count=<optimized out>)
    at drivers/base/regmap/regmap.c:2727
	#9  0xbf070210 in ?? ()

