### Porting DS1307 RTC I2C slave on KM-BBB expansion board 

#### Experiment 31: Add DS1307 I2C Slave device information in to Device Tree Source code

##### Step 1. ADD RTC slave Device in to DTS File:

        Add the below lines in km-bbb-am335x.dts file.
 
        &i2c1 {
            pinctrl-names = "default";
            //pinctrl-0 = <&i2c0_pins>;
            pinctrl-0 = <&i2c1_pins>;
    
            status = "okay";
            clock-frequency = <100000>;
    
            rtc1: ds1307@68 {
                    compatible = "dallas,ds1307";
                    reg = <0x68>;
                    #address-cells = <1>;
                    #size-cells = <1>;
            };

          Modified:  arch/arm/boot/dts/km-bbb-am335x.dts
 
##### Step 2. I2C Kernel Configuration Options:
 
         km@KernelMasters:~/KM_GITHUB/beagleboneblack-kernel$ grep RTC .config
         CONFIG_RTC_LIB=y
         CONFIG_RTC_CLASS=y
         CONFIG_RTC_HCTOSYS=y
         CONFIG_RTC_HCTOSYS_DEVICE="rtc0"
         CONFIG_RTC_SYSTOHC=y
         CONFIG_RTC_SYSTOHC_DEVICE="rtc0"
         # CONFIG_RTC_DEBUG is not set
         # RTC interfaces
         CONFIG_RTC_INTF_SYSFS=y
         CONFIG_RTC_INTF_PROC=y
         CONFIG_RTC_INTF_DEV=y
         CONFIG_RTC_DRV_DS1307=m
         CONFIG_RTC_DRV_TWL92330=y
         CONFIG_RTC_DRV_TWL4030=m
         CONFIG_RTC_DRV_PALMAS=m
         CONFIG_RTC_I2C_AND_SPI=y
         # on-CPU RTC drivers
         CONFIG_RTC_DRV_OMAP=m
         CONFIG_RTC_DRV_CPCAP=m
 
##### Step 3. Findout I2C Adapter & Client source code locations

	 Enable printks in probe begining & End.
 
         I2C Adapter Driver [i2c-omap.c] location:  drivers/i2c/busses/i2c-omap.c
         I2C Client Driver [rtc-ds1307.c] location: drivers/rtc/rtc-ds1307.c


##### Step 4: Verify RTC clinet driver initalization using probe method  

###### Case 1: DS1307 interface with BBB

Expected Results:

        rtc1 device file is created in dev folder.

        km@KM-BBB:~$ i2cdetect  -y -r 1 0x60 0x70
            0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
        00:                                                 
        10:                                                 
        20:                                                 
        30:                                                 
        40:                                                 
        50:                                                 
        60: -- -- -- -- -- -- -- -- UU -- -- -- -- -- -- -- 
        70: --


###### Case 2: DS1307 is not interface with BBB (slave not exist)

Expected Results:

        rtc1 device file is not created in dev folder.
        [   19.390277] rtc-ds1307 1-0068: probe
        [   19.390299] drivers/rtc/rtc-ds1307.c:ds1307_probe:1404
        [   20.898918] rtc-ds1307 1-0068: read error -16
        [   20.900038] rtc-ds1307: probe of 1-0068 failed with error -16
        [   20.924161] i2c-core: driver [rtc-ds1307] registered

        km@KM-BBB:~$ i2cdetect  -y -r 1 0x60 0x70
            0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
        00:                                                 
        10:                                                 
        20:                                                 
        30:                                                 
        40:                                                 
        50:                                                 
        60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- 
        70: --

##### 3. To Get RTC Data from user space app using i2c-dev [/dev/i2c-1] interface: (optional)

         app/i2c-dev/i2c-dev-rtc.c:   i2c-1
 
##### 4. To Set/Get time from user space app using rtc-dev [/dev/rtc1] interface:

         app/rtc-dev/time-set.c:
         app/rtc-dev/time-get.c:

