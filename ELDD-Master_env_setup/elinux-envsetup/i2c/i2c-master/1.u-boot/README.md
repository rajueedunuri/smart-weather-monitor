
### Developing I2C Master Drivers in u-boot Space

#### U-boot Level
	- Add I2C Mux/Pad Configuration in board specific mux file.
	- Scan I2C Slave device using I2C command in prompt.
	- Test basic communication with slave device using I2C command in u-boot command prompt.

#### Lab Exp 1: Enable I2C1 Mux Configuration in u-boot source code

	Source files:
		board/ti/am335x/mux.c
	 
	22 +static struct module_pin_mux i2c1_pin_mux[] = {
	23 +       {OFFSET(spi0_d1), (MODE(2) | RXACTIVE |
	24 +                       PULLUDEN | SLEWCTRL)}, /* I2C_DATA */
	25 +       {OFFSET(spi0_cs0), (MODE(2) | RXACTIVE |
	26 +                       PULLUDEN | SLEWCTRL)}, /* I2C_SCLK */
	27 +       {-1},
	28 +};
	29 +
	30 +void enable_i2c1_pin_mux(void)
	31 +{
	32 +        configure_module_pin_mux(i2c1_pin_mux);
	33 +}
	34 +
	35  void km_bbb_mux(void)
	36  {
	37          configure_module_pin_mux(mmc0_pin_mux);
	38          configure_module_pin_mux(mmc1_pin_mux);
	39          configure_module_pin_mux(lcd_pin_mux);
	40           configure_module_pin_mux(mii1_pin_mux);
	41 +         configure_module_pin_mux(i2c1_pin_mux);
	42  }

	Commit ID: "Enable I2C1 Mux"
	
#### Lab Exp 2: Understood u-boot I2C Commands.

	Kishore=> i2c
	i2c - I2C sub-system

	Usage:
	i2c bus [muxtype:muxaddr:muxchannel] - show I2C bus info
	i2c crc32 chip address[.0, .1, .2] count - compute CRC32 checksum
	i2c dev [dev] - show or set current I2C bus
	i2c loop chip address[.0, .1, .2] [# of objects] - looping read of device
	i2c md chip address[.0, .1, .2] [# of objects] - read from I2C device
	i2c mm chip address[.0, .1, .2] - write to I2C device (auto-incrementing)
	i2c mw chip address[.0, .1, .2] value [count] - write to I2C device (fill)
	i2c nm chip address[.0, .1, .2] - write to I2C device (constant address)
	i2c probe [address] - test for and show device(s) on the I2C bus
	i2c read chip address[.0, .1, .2] length memaddress - read to memory
	i2c write memaddress chip address[.0, .1, .2] length [-s] - write memory
			to I2C; the -s option selects bulk write in a single transaction
	i2c reset - re-init the I2C Controller
	i2c speed [speed] - show or set I2C bus speed

	Example: 
		=> i2c dev 1 (select I2C-1 Device Controller)
		=> i2c probe (I2C-1 Scan list of slave devices)


#### Lab Exp 3: Prepare I2C Framework in u-boot source code

##### Step1: Study I2C basics & Study OMAP I2C Controller block diagram, specifications & register programming model.
		
AM3358 manual and RTC datasheets are located in docs folder.

##### Step2: Identify I2C Driver Source code in u-boot

search I2C keywords in uboot configuration files.

	```# I2C support
	#
	# CONFIG_DM_I2C is not set
	# CONFIG_DM_I2C_COMPAT is not set
	# CONFIG_SYS_I2C_DW is not set
	# CONFIG_SYS_I2C_IMX_LPI2C is not set
	# CONFIG_SYS_I2C_MXC is not set
	CONFIG_SYS_I2C_OMAP24XX=y
	CONFIG_SYS_OMAP24_I2C_SLAVE=1
	CONFIG_SYS_OMAP24_I2C_SPEED=100000
	CONFIG_SYS_I2C_BUS_MAX=3

	cmd/i2c.c
	drivers/i2c/omap24xx_i2c.c```  

##### Step3: Setup Debug Enviornment
	
Basic Debugging Mechanisum is prints. 
Enable printf() statement inside each and every function.
Write printf (“%s:%s:%d\n”,__FILE__,__func__,__LINE__) function in the below files, build the source code. 

cmd/i2c.c
drivers/i2c/omap24xx_i2c.c

Commit Message:   Prepare I2C framework - “i2c probe”

##### Step 4: Prepare I2C Initalization framework

drivers/i2c/omap24xx_i2c.c  (Line no 839 to 1000: W/o DM I2C Initialization)
U_BOOT_I2C_ADAP_COMPLETE(omap24_1, omap24_i2c_init, omap24_i2c_probe, omap24_i2c_read, omap24_i2c_write, omap24_i2c_setspeed, CONFIG_SYS_OMAP24_I2C_SPEED1, CONFIG_SYS_OMAP24_I2C_SLAVE1,1)

##### Step 5: Prepare I2C Operation framework

Run "i2c probe" command in u-boot command prompt and collect the logs.


Kishore=> i2c probe 0x68                                                                                                                                                        

 Valid chip addresses:drivers/i2c/i2c_core.c:i2c_probe:275                                                                                                                       
 drivers/i2c/omap24xx_i2c.c:omap24_i2c_probe:936                                                                                                                                 
 drivers/i2c/omap24xx_i2c.c:__omap24_i2c_probe:486                                                                                                                               
 Device Found chip:104                                                                                                                                                           


