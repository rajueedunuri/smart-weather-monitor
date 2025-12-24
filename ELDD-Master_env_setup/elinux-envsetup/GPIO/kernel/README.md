<!-- vim-markdown-toc GFM -->

* [GPIO @ Kernel Lab Experiments](#gpio--kernel-lab-experiments)
	* [Communicate with Hardware @ Linux command prompt (Exp's 20 & 21)](#communicate-with-hardware--linux-command-prompt-exps-20--21)
		* [Exp 20: Control GPIO pins from sys file system entry @ user space](#exp-20-control-gpio-pins-from-sys-file-system-entry--user-space)
		* [Exp 21: Monitoring Mux Configuration and GPIO pins using debug file system.](#exp-21-monitoring-mux-configuration-and-gpio-pins-using-debug-file-system)
	* [Mux Configuration of GPIO [LED, Buzzer & Switch] in device tree source code (Exp's 22 & 23)](#mux-configuration-of-gpio-led-buzzer--switch-in-device-tree-source-code-exps-22--23)
		* [Exp 22: LED,Buzzer & Switch Mux configuration in u-boot.](#exp-22-ledbuzzer--switch-mux-configuration-in-u-boot)
		* [Exp 23: Mux Configuration of GPIO in device tree source code.](#exp-23-mux-configuration-of-gpio-in-device-tree-source-code)
	* [GPIO Test Modules (Exp's 24 & 25)](#gpio-test-modules-exps-24--25)
		* [Exp 24: Write hello world module program and compile with ARM cross toolchain and transfer the binary file to target board using SD Card (or) scp.](#exp-24-write-hello-world-module-program-and-compile-with-arm-cross-toolchain-and-transfer-the-binary-file-to-target-board-using-sd-card-or-scp)
		* [Exp 25: GPIO Device driver Test cases.](#exp-25-gpio-device-driver-test-cases)

<!-- vim-markdown-toc -->

##  GPIO @ Kernel Lab Experiments

### Communicate with Hardware @ Linux command prompt (Exp's 20 & 21)

#### Exp 20: Control GPIO pins from sys file system entry @ user space

	1. Enter gpio class in sysfs file system,
	$ cd /sys/class/gpio
	2. Enter root login,
	/sys/class/gpio/$ sudo su
	3. Export pin 10,
	/sys/class/gpio/# echo 10 > export
	4. Enter gpio10 folder,
	/sys/class/gpio/# cd gpio10
	5. Change pin direction to output,
	/sys/class/gpio/gpio10/# echo out > direction
	6. LED ON,
	/sys/class/gpio/gpio10/# echo 1 > value
	7. LED OFF,
	/sys/class/gpio/gpio10/# echo 0 > value
	8. Unexport pin 10,
	/sys/class/gpio/gpio10/# cd ..
	/sys/class/gpio/# echo 10 > unexport

#### Exp 21: Monitoring Mux Configuration and GPIO pins using debug file system.

	1. Enter root login,
	$ sudo su
	2. To read 128 GPIO pins status,
	# cat /sys/kernel/debug/gpio
	3. To read Mux configuration of each pin,
	# cat /sys/kernel/debug/pinctrl/44e10800.pinmux-pinctrl-single/pins


### Mux Configuration of GPIO [LED, Buzzer & Switch] in device tree source code (Exp's 22 & 23)

#### Exp 22: LED,Buzzer & Switch Mux configuration in u-boot.

	Case 1: Enable LED, BUZZER, and Switch MUX configuration in u-boot source code.
	We have enabled Mux, already in “Experiments 9 to 11” inside u-boot repository.

	Expected Results: LED, BUZZER and Switch devices should work properly in Linux command prompt.

	Case 2: Disable LED, BUZZER, and Switch MUX configuration in u-boot source code. (switch to master
	branch)
	Once you switch to master branch inside u-boot repository, MUX is disabled.
	Expected Results: LED, BUZZER and Switch devices don’t work in Linux command prompt.


#### Exp 23: Mux Configuration of GPIO in device tree source code.

	Enable LED, Buzzer and Switch MUX configuration in device tree source code.

	Source files:
	arch/arm/boot/dts/km-bbb-am335x.dts

	Tag name: Exp17
	Commit Message: “Mux Config in DTS: LCD_DATA_13.GPIO0_9, LCD_DATA14.GPIO0_10 & LCD_DATA_15.GPIO0_11”
	Expected Results: LED, BUZZER and Switch devices should work properly in Linux command prompt.

	41                         AM33XX_IOPAD(0x8d4, MUX_MODE7)    /* lcd_data13.gpio0_9 (BUZZER) */
	42                         AM33XX_IOPAD(0x8d8, MUX_MODE7)    /* lcd_data14.gpio0_10(RED LED) */
	43                         AM33XX_IOPAD(0x8dc, MUX_MODE7 | PIN_INPUT | PIN_INPUT_PULLDOWN )    /* lcd_data15.gpio0_11 (ENTER SWITCH) */


### GPIO Test Modules (Exp's 24 & 25)

#### Exp 24: Write hello world module program and compile with ARM cross toolchain and transfer the binary file to target board using SD Card (or) scp. 

	Finally load the module in KM-BBB expansion board and verify the results.

#### Exp 25: GPIO Device driver Test cases.

	To test GPIO device controller operations such as input, output and interrupt we can use module programming technique. 
	These programs can be referred to as GPIO Test modules.

	Source files:
	gpio-output.c
	gpio-input.c
	gpio-interrupt.c

	Process:
	Cross compile the modules and transfer images (.ko files) to target board. Then load each module.

	Test GPIO input/output/interrupt to read/write to the GPIO pins using cat/echo commands.
	Unload the module.


### GPIO Framework in Kernel space (Experiment 26)

#### 26.1: Prepare GPIO Initalization framework:

    Disable CONFIG_LEDS_GPIO configuration option to avoid continuous print messages.

**case 1:** 

- Add printk's in init & exit functions and also add begin & end of probe function in  `drivers/gpio/gpio-omap.c`.
- Run `km-bbb-kernel-build.sh` script and generate images.
- Install kernel images in to target board using mmc (or) tftp (or) scp.
- Reboot target board and run dmesg command and verfiy printk results in kernel log. 
	
**Expected Results:**
- probe invokes 4 times becuase am3358 contains 4 gpio controllers.

**case 2:**

- Modify gpio1,2,3 compatiable name to `test-omap` in `arch/arm/boot/dts/am33xx.dtsi` file.
- Run below command to build device tree source code. 
  `$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- dtbs`
- copy km-bbb-am335x.dtb file in to target board in /boot/dtbs/`uname -r`/
- Reboot target board and run dmesg and verify printk results in kernel log.

**Expected Results:**
- probe invokes only 1 time because am3358 soc contains 4 gpio controllers but in dtsi file name matches only GPIO0.

<img src="images/GPIO_Initalization_Framework.jpg">

#### 26.2: Prepare GPIO Operation framework:

- Enable printks in each and every function in `drivers/gpio/gpiolib.c` and `drivers/gpio/gpio-omap.c` files.
- Run `km-bbb-kernel-build.sh` script and generate images.
- Install kernel images in to target board using mmc (or) tftp (or) scp.
- Run `cat value` command in `/sys/class/gpio10` folder and run dmesg command and verfiy printk results in kernel log. 

<img src="images/GPIO_Operation_Framework.jpg">

