
<!-- vim-markdown-toc GFM -->

* [Experiment 5: Setup U-boot development environment for KM-BBB customization](#experiment-5-setup-u-boot-development-environment-for-km-bbb-customization)
	* [Step 1.Create a branch (one branch sufficent for whole course)](#step-1create-a-branch-one-branch-sufficent-for-whole-course)
	* [Step 2: Build x-loader & u-boot source code:](#step-2-build-x-loader--u-boot-source-code)
	* [Step 3: Install MLO & u-boot images:](#step-3-install-mlo--u-boot-images)
	* [Step 4: Expected Results:](#step-4-expected-results)
		* [Step 5: Add source code modification and create a new commit ID in uboot git repository.](#step-5-add-source-code-modification-and-create-a-new-commit-id-in-uboot-git-repository)
* [Communicating with Hardware @ u-boot command prompt (Exp 6)](#communicating-with-hardware--u-boot-command-prompt-exp-6)
	* [Exp 6: Read sys boot pin status](#exp-6-read-sys-boot-pin-status)
* [Mux Configuration @ u-boot command prompt (Exp's 7 & 8)](#mux-configuration--u-boot-command-prompt-exps-7--8)
	* [Exp 7: MUX configuration of RED LED (GPIO: output) to Output device](#exp-7-mux-configuration-of-red-led-gpio-output-to-output-device)
	* [Exp 8: Mux configuration of +ve level (or) -ve level Switch (GPIO: Input) to input device](#exp-8-mux-configuration-of-ve-level-or--ve-level-switch-gpio-input-to-input-device)
* [Mux Configuration of GPIO [LED, Buzzer & Switch] in u-boot source code (Exp's 9 to 11)](#mux-configuration-of-gpio-led-buzzer--switch-in-u-boot-source-code-exps-9-to-11)
	* [Exp 9: Mux configuration of RED LED](#exp-9-mux-configuration-of-red-led)
	* [Exp 10: Mux configuration of Enter Switch](#exp-10-mux-configuration-of-enter-switch)
	* [Exp 11: Mux configuration of Buzzer](#exp-11-mux-configuration-of-buzzer)
* [GPIO Operations (Control RED LED & Read Enter Switch) from u-boot command prompt using mm & md (Exp's 12,13 & 14)](#gpio-operations-control-red-led--read-enter-switch-from-u-boot-command-prompt-using-mm--md-exps-1213--14)
	* [Exp 12: RED LED ON.](#exp-12-red-led-on)
	* [Exp 13: RED LED OFF](#exp-13-red-led-off)
	* [Exp 14: Read Enter Switch](#exp-14-read-enter-switch)
* [GPIO Device Driver framework in u-boot source code (Exp's 15 to 16)](#gpio-device-driver-framework-in-u-boot-source-code-exps-15-to-16)
	* [Exp 15: Prepare GPIO Device Driver framework (source code flow) [gpio set 10]](#exp-15-prepare-gpio-device-driver-framework-source-code-flow-gpio-set-10)
	* [Exp 16: GPIO framework [gpio input 11]](#exp-16-gpio-framework-gpio-input-11)
* [U-boot customization (Exp's 17,18,19)](#u-boot-customization-exps-171819)
	* [Exp 17: REAL ASSIGNMENT](#exp-17-real-assignment)
	* [Exp 18: REAL ASSIGNMENT](#exp-18-real-assignment)
	* [Exp 19: REAL ASSIGNMENT](#exp-19-real-assignment)

<!-- vim-markdown-toc -->

## Experiment 5: Setup U-boot development environment for KM-BBB customization

Download u-boot & kernel source code, build the source code and install the images on KM-BBB
Expansion board.

### Step 1.Create a branch (one branch sufficent for whole course)

	Create a branch "<KMID>-<your name>-km-bbb-boot" in u-boot source code and customize the
	below things in this branch:

	a. Modify extra version is “km-bbb-uboot” in Makefile
	b. Boot delay to 28 sec (CONFIG_BOOTDELAY=28)
		$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
		Main menu -> (28) delay in seconds before automatically booting

	c. Name of the command prompt to <Your name> in uboot configuration file.
	(CONFIG_SYS_PROMPT="Kishore=> ")
		$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig
		Main emnu -> command line interface -> () Shell Prompt

### Step 2: Build x-loader & u-boot source code:

	$ ./km-bbb-uboot-build.sh

### Step 3: Install MLO & u-boot images:

	3a: Flash images on SD card
		$ sudo ./km-bbb-uboot-install.sh --mmc  /dev/sdb
	3b: Flash images on eMMC( onboard memory) using Network that is SCP
		$ sudo ./km-bbb-uboot-install.sh --scp
	Run the below script in target board
	$ cd install
	$ ./km-bbb-install-bl-mmc.sh 	

### Step 4: Expected Results:

	After boot verify the time stamp of images, time stamp should be same as your image build time and date.  
	And also verify u-boot image name, boot delay and command prompt name.

#### Step 5: Add source code modification and create a new commit ID in uboot git repository.    
	After testing,
	Tag name: Exp5
	Commit Message: Exp5: Setup U-boot Environment


Reference:
https://kernelmasters.org/blog/2020/07/06/setup-embedded-linux-development-environment/


## Communicating with Hardware @ u-boot command prompt (Exp 6)

### Exp 6: Read sys boot pin status

	Find out PA of control status reg:
	PA of Control Status Reg = BA of Control Module (memory mapping chapter) + OA of Control status reg (control module chapter)
				 = 0x44E10000 + 0x40 
				 = 0x44E10040
	=> md 0x44E10040

**Expected Results:**

		0040033c -> 11100 -> booting from eMMC -> sys boot sw OFF
		00400338 -> 11000 -> booting from SDcard -> sys boot sw ON

## Mux Configuration @ u-boot command prompt (Exp's 7 & 8) 

### Exp 7: MUX configuration of RED LED (GPIO: output) to Output device

	Physical Address of LCD_DATA14 REGISTER = 
	Base address of Control module (pg. NO 179) + Offset address of LCD_DATA14 REGISTER (Pg. No: 1371)
	=  0x44E1 0000 + 0x0000 08D8  = 0x44E1 08D8 

**Expected Results**

	Kishore=> md.b 0x44E108D8 1
	44e108d8: 00                                                 .
	Kishore=> mm.b 0x44E108D8
	44e108d8: 00 ? 07
	44e108d9: 00 ? q
	Kishore=> mm.b 0x44E108D8
	44e108d8: 07 ? q


### Exp 8: Mux configuration of +ve level (or) -ve level Switch (GPIO: Input) to input device

	Physical Address of LCD_DATA15 REGISTER = = 0x44E1 0000 + 0x0000 08DC = 0x44E108DC 

	Case 1: +ve Level Switch (Pull Down) (ON = 1 ; OFF = 0)
		0010 0111  => 27H (Pull Down - Mux Mode 7)

	GPIO0_11 => Enter Switch 
	
	Case 2: -ve Level Switch (Pull Up) (ON = 0 ; OFF = 1)

	0011 0111  => 37H (Pull up - Mux Mode 7)

Results: 
	=> gpio input 11

## Mux Configuration of GPIO [LED, Buzzer & Switch] in u-boot source code (Exp's 9 to 11)

### Exp 9: Mux configuration of RED LED

	Select LCD_DATA14 pin functionality to enable GPIO0_10 to RED LED

	Source code files:
	board/ti/am335x/mux.c

	34         {OFFSET(lcd_data14), (MODE(7))},             /* lcd_data14.gpio0_10 */ // By default disable USER LED


	After build & testing,

	Tag name: Exp9
	Commit Message: Select LCD_DATA14 pin functionality to enable GPIO0_10 to RED LED

### Exp 10: Mux configuration of Enter Switch

	Select LCD_DATA15 pin functionality to enable GPIO0_11 to enter switch and configure to +ve Level Switch.
	Enable Pull down and Rx Active in pad register.

	Source code files:
	board/ti/am335x/mux.c

	After build & testing,
	Tag name: Exp10
	Commit Message: Select LCD_DATA15 pin functionality to enable GPIO0_11 to enter switch.

### Exp 11: Mux configuration of Buzzer

	Enable GPIO0_9 functionality to work like Buzzer, in LCD_DATA13 mux configuration.

	Source code files:
	board/ti/am335x/mux.c
	After build & testing,

	Tag name: Exp11
	Commit Message: Select LCD_DATA13 pin functionality to enable GPIO0_9 to Buzzer

## GPIO Operations (Control RED LED & Read Enter Switch) from u-boot command prompt using mm & md (Exp's 12,13 & 14) 

### Exp 12: RED LED ON.

	BA of GPIO0_Base Address: 0x44E07000

	PA of GPIO0_OE Register:  0x44E07134
	PA of GPIO0_DATAIN Register: 0x44E07138
	PA of GPIO0_DATAOUT Register: 0x44E0713C
	PA of GPIO0_CLEARDATAOUT Register: 0x44E07190
	PA of GPIO0_SETDATAOUT Register: 0x44E07194

	Writing a 1 to a bit in the GPIO_SETDATAOUT register sets to 1 the corresponding bit in the GPIO_DATAOUT register

	- Set 10th bit in GPIO0_SETDATAOUT to blink LED.
	  01(10th bit)00 0000 0000  (0x0000 0400)

	KM=> mm 0x44E07194
	44e07194: 00000000 ? 00000400
	44e07198: 00000000 ? q

	- Clear 10th bit in GPIO0_OE to set output direction
	  1111 1111 10(10th bit)11 1111 1111 (0xFFFF FBFF)

### Exp 13: RED LED OFF

	Writing a 1 to a bit in the GPIO_CLEARDATAOUT register clears to 0 the corresponding bit in the GPIO_DATAOUT register;

	- Set 10th bit in GPIO0_CLEARDATAOUT to blink LED.

	KM=> mm 0x44E07190
	44e07190: 00000400 ? 00000400
	44e07194: 00000000 ? q

	- Clear 10th bit in GPIO0_OE to set output direction

### Exp 14: Read Enter Switch

	- Check 11th bit in GPIO0_DATAIN to read switch status.
	
	Switch not press, 
	KM=> md.l 0x44E07138 1
	44e07138: 0c000000                               ....

	Switch press,
	KM=> md.l 0x44E07138 1
	44e07138: 0c000800

## GPIO Device Driver framework in u-boot source code (Exp's 15 to 16)

### Exp 15: Prepare GPIO Device Driver framework (source code flow) [gpio set 10]

	Write printf (“%s:%s:%d\n”,__FILE__,__func__,__LINE__) function in the below files, build the
	source code and test “gpio set 10” in u-boot command prompt.

	Source files:
	cmd/gpio.c (CONFIG_CMD_GPIO=y)
	command line interface -> device access commands -> gpio

	drivers/gpio/gpio-uclass.c (CONFIG_DM_GPIO=y)
	Device Drivers -> GPIO Support -> Enable Driver Model for GPIO drivers
	
	drivers/gpio/omap_gpio.c (CONFIG_OMAP_GPIO=y)
	Device Drivers -> GPIO Support -> TI OMAP GPIO drivers


	After build & testing,
	Tag name: Exp15
	Commit Message: Prepare GPIO framework - “gpio set 10”

### Exp 16: GPIO framework [gpio input 11]

	Write printf (“%s:%s:%d\n”,__FILE__,__func__,__LINE__) function in the below files, build the
	source code and test “gpio input 11” in u-boot command prompt.

	Source files:
	cmd/gpio.c
	drivers/gpio/gpio-uclass.c
	drivers/gpio/omap_gpio.c

	After build & testing,
	Tag name: Exp16
	Commit Message: Prepare GPIO framework - “gpio input 11”

## U-boot customization (Exp's 17,18,19)

### Exp 17: REAL ASSIGNMENT
	Add blink option to gpio u-boot command and make it blink every 100 msec delay up to user press Ctrl+C.
	Syntax: gpio <input|set|clear|toggle|blink> <pin>
	Example: gpio blink <pin>

	Source files:
	cmd/gpio.c

	After build & testing,
	Tag name: Exp17
	Commit Message: u-boot customization: Add blink option to gpio u-boot command

### Exp 18: REAL ASSIGNMENT

	Implement blink command in u-boot command prompt. Blink command to control GPIO pin every 100msec delay up to user press Ctrl+C.

	Syntax: blink <pin>
	Example: blink 10

	Source files:
	cmd/blink.c
	cmd/Makefile

	After build & testing,
	Tag name: Exp18
	Commit Message: u-boot customization – Add blink command in u-boot command prompt

### Exp 19: REAL ASSIGNMENT

	How reset command works?

	Source files:
	arch/arm/lib/reset.c,
	arch/arm/mach-omap2/reset.c,
	writel(PRM_RSTCTRL_RESET, PRM_RSTCTRL);
	TRM document Page no: 1340
	8.1.13.5.1 PRM_RSTCTRL Register (offset = 0h) [reset = 0h]
