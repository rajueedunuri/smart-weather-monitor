## GPIO PROJECT (/dev/input/event0)

#### Project 1: Enter Switch (Raising Edge Interrupt) porting on KM_BBB target board (AM335x Controller)
    
    Subsystem names: “Input Sub system” & “GPIO sub system” in Kernel.
    
    Tag name: gpioproj1
    Commit Message: “Enter Switch (GPIO11: Raising Edge Interrupt) porting on KM-BBB target board”
    
    HDD: 1st sub system: general – Input - RTC – V4L - ALSA
    LDD: 2nd sub system: Device controller – GPIO – I2C – RGB – I2S/I2C
    
    @ U-boot Level - Troubleshooting:
    Step 1: Add GPIO Key Mux configuration in u-boot source code.
    Step 2: Test GPIO Key functionality using gpio command at u-boot command prompt
    
    @ Kernel Level:
    Step 3: Enable GPIO keys driver and interrupt in Device tree source code.
    arch/arm/boot/dts/km-bbb-am335x.dts
    
    Step 4: Enable GPIO Key driver as module in kernel configuration file and cross compile.
    
#### Project 2:  REAL PROJECT  (/dev/input/event0)

    UP & Down Switches (Falling Edge Interrupt) porting on KM_BBB target board (AM335x Controller).
    Subsystem names: “Input Sub system” & “GPIO sub system” in Kernel.
    
    Tag name: gpioproj2
    Commit Message: “UP & Down Switches (Falling Edge Interrupt) porting on KM_BBB target board”
