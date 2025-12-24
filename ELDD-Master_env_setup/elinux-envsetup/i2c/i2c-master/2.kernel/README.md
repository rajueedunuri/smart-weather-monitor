### Developing I2C Master Driver in Kernel Space

Kernel Level
- Add I2C Master driver platform data in to Device tree source code
- Integrating platform (I2C Master) driver and slave driver with framework.
- Check Probe and initialization functions both Master and slave drivers.
- Registering I2C master/adapter and slave drivers.



#### Experiment 30: Prepare I2C Framework in Kernel space [Understand Linux I2C subsystem]

##### Step 1: Study 

- Understood Linux I2C Terminology.
- Linux I2C Sub system Architecture.
- I2C Comm protocol basics. AM3358 I2C Controller functional block diagram and register programming model.

##### Step 2: Identify the source code. 

        drivers/i2c/i2c-dev.c
        drivers/i2c/i2c-core-base.c
        drivers/i2c/busses/i2c-omap.c

##### Step 3: Setup Debug environment

	Write printf (“%s:%s:%d\n”,__FILE__,__func__,__LINE__) function in the above source  files, build the source code.
	otherwise apply "patch/0001-I2C-Adapter-framework.patch" patch in master branch.

##### Step 4: Framework implementation

##### 4a: I2C Initalization Framework (Bottom to top):

<img src="images/i2c_master_init_framework_kernel.jpg">

        1. get the platform data or device data from board specifile source code or device tree.
        reg = <0x4802a000 0x1000>;
        interrupts = <71>;

        2. Interrupt registration  (request_irq)
        r = devm_request_irq(&pdev->dev, dev->irq, omap_i2c_omap1_isr, IRQF_NO_SUSPEND, pdev->name, dev);
        $ cat /proc/interrupts
        87:         23      INTC  71  4802a000.i2c

        3. memory mapped I/O allocation (ioremap)
        dev->base = devm_ioremap_resource(&pdev->dev, mem);
        $ cat /proc/iomem
        4802a000-4802afff : /ocp/i2c@4802a000

        4. i2c_add_adpater() 

	"i2c_algorithm" strutcure initalization for communicate i2c-core.c file i.e., high level layer.
        static const struct i2c_algorithm omap_i2c_algo = {
        .master_xfer    = omap_i2c_xfer,
        .functionality  = omap_i2c_func,
        };

 **Expected Results:**

        verify i2c physical addres
        $ cat /proc/iomem
        4802a000-4802afff : /ocp/i2c@4802a000

        verify i2c interrupt 
        $ cat /proc/interrupts
        87:         23      INTC  71  4802a000.i2c

        verify i2c device file
        $ ls -l /dev/i2c-*


** Initalization log File**

        ***********************************************************************************
        ******************************* i2c-0 Probe Begin *********************************
        [    0.332486] drivers/i2c/busses/i2c-omap.c:omap_i2c_probe:1421
        ***********************************************************************************

        [    0.332726] drivers/i2c/busses/i2c-omap.c:omap_i2c_init:375
        [    0.332856] drivers/i2c/busses/i2c-omap.c:__omap_i2c_init:294
        [    0.333635] drivers/i2c/i2c-core-base.c:i2c_add_adapter:1408
        [    0.333667] drivers/i2c/i2c-core-base.c:__i2c_add_numbered_adapter:1377
        [    0.333724] drivers/i2c/i2c-core-base.c:i2c_register_adapter:1273
        [    0.333747] drivers/i2c/busses/i2c-omap.c:omap_i2c_func:882
        [    0.334025] drivers/i2c/i2c-core-base.c:i2c_device_match:109
        [    0.334062] drivers/i2c/i2c-core-base.c:i2c_device_match:109
        [    0.334082] drivers/i2c/i2c-core-base.c:i2c_device_match:109
        [    0.334101] drivers/i2c/i2c-core-base.c:i2c_device_match:109
        [    0.334120] drivers/i2c/i2c-core-base.c:i2c_device_match:109
        [    0.334138] drivers/i2c/i2c-core-base.c:i2c_device_match:109
        [    0.334717] drivers/i2c/i2c-core-base.c:i2c_init_recovery:269
        [    0.334816] drivers/i2c/i2c-core-base.c:i2c_detect:2251
        [    0.334897] drivers/i2c/i2c-core-base.c:i2c_detect:2251
        [    0.334917] drivers/i2c/i2c-core-base.c:i2c_detect:2251
        [    0.334936] drivers/i2c/i2c-core-base.c:i2c_detect:2251
        [    0.334955] drivers/i2c/i2c-core-base.c:i2c_detect:2251
        [    0.334973] drivers/i2c/i2c-core-base.c:i2c_detect:2251
        [    0.334999] omap_i2c 4802a000.i2c: bus 1 rev0.11 at 100 kHz

        ***********************************************************************************
        ******************************* i2c-0 Probe END ***********************************
        [    0.335058] drivers/i2c/busses/i2c-omap.c:omap_i2c_probe:1572
        ***********************************************************************************



##### 4b: I2C Operation Framework (Top to Bottom)


        By default i2c-1 is disable in DTS file. apply the below patch in "km-bbb-am335x.dts" file and enable i2c-1.

        km@KM-BBB:~$ ls -l /dev/i2c-*
        crw-rw---- 1 root i2c 89, 0 Jul 27 06:42 /dev/i2c-0

        +	i2c1_pins: pinmux_i2c1_pins {
        +                pinctrl-single,pins = <
        +                         AM33XX_PADCONF(AM335X_PIN_SPI0_CS0, PIN_INPUT_PULLUP, MUX_MODE2)        /* spi0_cs0.i2c0_scl */
        +                         AM33XX_PADCONF(AM335X_PIN_SPI0_D1, PIN_INPUT_PULLUP, MUX_MODE2)        /* spi0_d1.i2c0_sda */
        +                 >;
        +         };
        +
        +};
        +
        +&i2c1 {
        +         pinctrl-names = "default";
        +         pinctrl-0 = <&i2c1_pins>;
        +
        +         status = "okay";
        +         clock-frequency = <100000>;
        +         symlink = "bone/i2c/0";
        };`


        Expected results after applying the above patch is, 

        km@KM-BBB:~$ ls -l /dev/i2c-*
        crw-rw---- 1 root i2c 89, 0 Jul 27 06:42 /dev/i2c-0
        crw-rw---- 1 root i2c 89, 1 Jul 27 06:42 /dev/i2c-1
       

<img src="images/i2c_master_op_framework_kernel.jpg">


        $ sudo ./i2c-app r 0 1 

        open("/dev/i2c-1",   );

        336.323262] drivers/i2c/i2c-dev.c:i2cdev_open:621
        [  336.328037] drivers/i2c/i2c-core-base.c:i2c_get_adapter:2347

        ioctl(fd,I2C_FUNCS,&funcs);

        [  336.336854] drivers/i2c/i2c-dev.c:i2cdev_ioctl:429
        [  336.342028] i2c i2c-1: ioctl, cmd=0x705, arg=0x22058

        ioctl(fd,I2C_SLAVE,&funcs);

        [  336.342044] drivers/i2c/busses/i2c-omap.c:omap_i2c_func:882
        [  336.352865] drivers/i2c/i2c-dev.c:i2cdev_ioctl:429
        [  336.357729] i2c i2c-1: ioctl, cmd=0x703, arg=0x68

        ioctl(fd,I2C_SMBUS,&funcs);

        [  336.357754] drivers/i2c/i2c-dev.c:i2cdev_ioctl:429
        [  336.362860] i2c i2c-1: ioctl, cmd=0x720, arg=0xbeeb3c20

        [  336.362877] drivers/i2c/i2c-dev.c:i2cdev_ioctl_smbus:347
        [  336.368228] drivers/i2c/i2c-core-base.c:i2c_adapter_depth:981
        [  336.374120] drivers/i2c/i2c-core-base.c:__i2c_transfer:1958
        [  336.379802] drivers/i2c/i2c-core-base.c:i2c_check_for_quirks:1890

        ------------------------------------------------------------------------------------

        [  336.385937] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_irq:864
        [  336.391961] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_common:822

        [  336.398240] drivers/i2c/busses/i2c-omap.c:__omap_i2c_init:294
        [  336.404113] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_msg:687

        <S> [<SA> <0>] <ACK -> XRDY> <WorD_ADD- 0x00> <ACK-ARDY> <S> [<SA> <1>] <ACK->RRDY> <SEC DATA> <ACK->RRDY> <P> 

        ACK -> 0x0010 ; 0001 0000
        ACK -> 0x0004 ; 0000 0100
        ACK -> 0x0008 ; 0000 1000 

        ******************************************************************************************
        Master Tx - Slave Rx
        [  336.410142] omap_i2c 4802a000.i2c: addr: 0x0068, len: 1, flags: 0x0, stop: 0
        [  336.410165] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr:11042c_isr:1104
        193 [  336.500683] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr_thread:1257
        194 [  336.506910] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_data:1122
        195 [  336.513123] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0008)
        196 [  336.513137] drivers/i2c/busses/i2c-omap.c:omap_i2c_receive_data:1042
        197 [  336.519585] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)
        198 [  336.531841] drivers/i2c/i2c-dev.c:i2cdev_release:652
        199 [  336.540394] drivers/i2c/i2c-core-base.c:i2c_put_adapter:2368

        [  336.415925] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr_thread:1257
        [  336.422237] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_data:1122
        [  336.428373] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0010)
        [  336.428386] drivers/i2c/busses/i2c-omap.c:omap_i2c_transmit_data:1066
        [  336.435057] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr:1104
        [  336.440864] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr_thread:1257
        [  336.447087] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_data:1122
        [  336.453286] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)
        [  336.488308] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_msg:687

        **********************************************************************************************
        Mater Rx - Slave TX
        [  336.494615] omap_i2c 4802a000.i2c: addr: 0x0068, len: 1, flags: 0x1, stop: 1
        [  336.494833] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr:1104
        [  336.500683] drivers/i2c/busses/i2c-omap.c:omap_i2c_isr_thread:1257
        [  336.506910] drivers/i2c/busses/i2c-omap.c:omap_i2c_xfer_data:1122
        [  336.513123] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0008)
        [  336.513137] drivers/i2c/busses/i2c-omap.c:omap_i2c_receive_data:1042
        [  336.519585] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)
        [  336.531841] drivers/i2c/i2c-dev.c:i2cdev_release:652
        [  336.540394] drivers/i2c/i2c-core-base.c:i2c_put_adapter:2368

        ************************************************************************************************

        ~ # ./i2c_app  r 00 1

        I2C_DEBUG_CORE
        [   79.832136] i2c i2c-1: ioctl, cmd=0x705, arg=0x8ccdc
        [   79.832198] i2c i2c-1: ioctl, cmd=0x703, arg=0x68
        [   79.832251] i2c i2c-1: ioctl, cmd=0x720, arg=0xbeeaabdc
        I2C_DEBUG_ALGO
        [   79.832301] i2c i2c-1: master_xfer[0] W, addr=0x68, len=1
        [   79.832336] i2c i2c-1: master_xfer[1] R, addr=0x68, len=1
        I2C_DEBUG_BUS
        [   79.832473] omap_i2c 4802a000.i2c: addr: 0x0068, len: 1, flags: 0x0, stop: 0
        [   79.832665] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0010)
        0x0010  -- XRDY
        [   79.832925] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)
        0x0004  -- ARDY
        [   79.833091] omap_i2c 4802a000.i2c: addr: 0x0068, len: 1, flags: 0x1, stop: 1
        [   79.833369] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0008)
        0x0008 --  RRDY
        [   79.833406] omap_i2c 4802a000.i2c: IRQ (ISR = 0x0004)
        0x0004  -- ARDY