<!-- vim-markdown-toc GFM -->

* [1. KDB & KGDB](#1-kdb--kgdb)
	* [1.1. KDB- Kernel Debugger:](#11-kdb--kernel-debugger)
	* [1.2. KGDB- Kernel GNU Debugger:](#12-kgdb--kernel-gnu-debugger)
* [2.Setup Kernel Debug Environment for KDB & KGDB](#2setup-kernel-debug-environment-for-kdb--kgdb)
	* [Step 1: Enable KGDB/KDB options](#step-1-enable-kgdbkdb-options)
	* [Step 2: Kernel configuration & build](#step-2-kernel-configuration--build)
	* [Step 3: Kernel Installation](#step-3-kernel-installation)
	* [Step 4: Setup kernel bootargs in u-boot](#step-4-setup-kernel-bootargs-in-u-boot)
* [3. KDB Testing](#3-kdb-testing)
	* [3.1. Case 1: User Entering a Kernel Debugger [KDB/KGDB]:](#31-case-1-user-entering-a-kernel-debugger-kdbkgdb)
	* [3.2. Case 2: Whenever Kernel panic is occurs by default Enter KDB prompt.](#32-case-2-whenever-kernel-panic-is-occurs-by-default-enter-kdb-prompt)
* [4. KGDB Debugging (source level debugging):](#4-kgdb-debugging-source-level-debugging)
	* [4.1. Step 1: Connect target board remote using ssh.](#41-step-1-connect-target-board-remote-using-ssh)
	* [4.2. Step 2: Switch KDB to KGDB](#42-step-2-switch-kdb-to-kgdb)
	* [4.3. Step 3: Remote Debugging with GDB](#43-step-3-remote-debugging-with-gdb)
	* [4.4. Step 4: Read gpio pin value from sysfs.](#44-step-4-read-gpio-pin-value-from-sysfs)

<!-- vim-markdown-toc -->


## 1. KDB & KGDB 

### 1.1. KDB- Kernel Debugger:
	
	•	Kdb is an instruction-level debugger used for debugging kernel code and device drivers. 
	•	Before you can use it, you need to enable configuration options your kernel sources with kdb support and recompile the kernel. 

### 1.2. KGDB- Kernel GNU Debugger:

	•	Kgdb is a source-level debugger.
	•	It is easier to use than kdb because you don't have to spend time correlating assembly code with your sources. 
	•	However it's more difficult to set up because an additional machine is needed to front-end the debugging.
	•	gdb runs on the host machine, while the kgdb-patched kernel runs on the target hardware. 
	•	The host and the target are connected via a serial null-modem cable.


## 2.Setup Kernel Debug Environment for KDB & KGDB

### Step 1: Enable KGDB/KDB options
	
	$ make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- menuconfig

	CONFIG_DEBUG_INFO: Compiles the kernel with debug symbols (-g option)
	CONFIG_DEBUG_INFO=y
	---> Kernel Hacking
		-- > Compile-time checks and compiler options
			-- > Compile the kernel with debug info
			
	CONFIG_KGDB: enables support for KGDB
	CONFIG_KGDB=y
	---> Kernel Hacking
		---> KGDB: Kernel Debugger
		
	CONFIG_KGDB_SERIAL_CONSOLE: Enables KGDB communication I/O driver over the serial port
	CONFIG_KGDB_SERIAL_CONSOLE=y
	---> Kernel Hacking
		---> KGDB: Kernel Debugger
			---> KGDB: use kgdb over the serial console

	CONFIG_KGDB_KDB=y
	---> Kernel Hacking
		---> KGDB: Kernel Debugger
			---> KGDB_KDB: include kdb frontend for kgdb
			
	CONFIG_KDB_KEYBOARD=y
	---> Kernel Hacking
		---> KGDB: Kernel Debugger
			---> KGDB_KDB: include kdb frontend for kgdb

	CONFIG_FRAME_POINTER: Helps to produce more reliable stack traces

	CONFIG_MAGIC_SYSRQ: Enables magic sysrq key functionality to put the kernel in debug mode
	---> Kernel Hacking
		---> KGDB: Magic SysRq key
		
	CONFIG_DEBUG_RODATA_TEST not set
		---> Kernel Hacking
			---> Memory Debugging
				---> Testcase for the marking rodata read-only (disable this option)

	CONFIG_STRICT_KERNEL_RWX is not set

### Step 2: Kernel configuration & build 

	$ ./km-bbb-kernel-build.sh	   

### Step 3: Kernel Installation

	$ ./km-bbb-kernel-install.sh

### Step 4: Setup kernel bootargs in u-boot

	Boot any one of the mode MMC0, MMC1 & TFTP.

	setenv bootargs console=tty0 console=${console} root=/dev/mmcblk1p1 rootfstype=${mmcrootfstype} ${cmdline}; root=/dev/mmcblk1p1 console=ttyO0,115200n8 rodata=off nokaslr kgdb=ttyO0,115200 kgdboc=ttyO0,115200n8 kgdbwait rootwait;

	Kernel Address Space Randomization (KASLR)


## 3. KDB Testing

	Choose KDB/KGDB Enabled Kernel at bootloader: 
	Power on the board, choose "Boot with KGDB/KDB" option in "KM boot menu" at u-boot prompt. Bydefault kernel enter to KDB mode.
	Kernel assign a break point after serial initialization and wait for user input.

	kdb> help (list of kdb commands)
	kdb> go (continue kernel boot process)

	Login as user until you see prompt. 

	Entering a Kernel Debugger:

### 3.1. Case 1: User Entering a Kernel Debugger [KDB/KGDB]:

	Enter supervisor mode.
	$ sudo su
	assign a break point to kernel. 
	$ echo g > /proc/sysrq-trigger

	Kernel enter to kdgb break point and shows kdb prompt.
	kdb> 


### 3.2. Case 2: Whenever Kernel panic is occurs by default Enter KDB prompt.

	kdb commands

	[0]kdb> help
	Command         Usage                Description
	----------------------------------------------------------
	md              <vaddr>             Display Memory Contents, also mdWcN, e.g1
	mdr             <vaddr> <bytes>     Display Raw Memory
	mdp             <paddr> <bytes>     Display Physical Memory
	mds             <vaddr>             Display Memory Symbolically
	mm              <vaddr> <contents>  Modify Memory Contents
	go              [<vaddr>]           Continue Execution
	rd                                  Display Registers
	rm              <reg> <contents>    Modify Registers
	ef              <vaddr>             Display exception frame
	bt              [<vaddr>]           Stack traceback
	btp             <pid>               Display stack for process <pid>
	bta             [D|R|S|T|C|Z|E|U|I|M|A]
										Backtrace all processes matching state fg
	btc                                 Backtrace current process on each cpu
	btt             <vaddr>             Backtrace process given its struct task s
	env                                 Show environment variables
	set                                 Set environment variables
	help                                Display Help Message
	?                                   Display Help Message
	cpu             <cpunum>            Switch to new cpu
	kgdb                                Enter kgdb mode
	ps              [<flags>|A]         Display active task list
	pid             <pidnum>            Switch to another task
	reboot                              Reboot the machine immediately
	lsmod                               List loaded kernel modules
	sr              <key>               Magic SysRq key
	dmesg           [lines]             Display syslog buffer
	defcmd          name "usage" "help" Define a set of commands, down to endefcd
	kill            <-signal> <pid>     Send a signal to a process
	summary                             Summarize the system
	per_cpu         <sym> [<bytes>] [<cpu>]
										Display per_cpu variables
	grephelp                            Display help on | grep
	bp              [<vaddr>]           Set/Display breakpoints
	bl              [<vaddr>]           Display breakpoints
	bc              <bpnum>             Clear Breakpoint
	be              <bpnum>             Enable Breakpoint
	bd              <bpnum>             Disable Breakpoint
	ss                                  Single Step
	dumpcommon                          Common kdb debugging
	dumpall                             First line debugging
	dumpcpu                             Same as dumpall but only tasks on cpus
	ftdump          [skip_#lines] [cpu] Dump ftrace log




## 4. KGDB Debugging (source level debugging):

	Whenever kernel crash, panic occurs by default enter in to KDB prompt. Switch from KDB to KGDB.

### 4.1. Step 1: Connect target board remote using ssh.

	Run the below command in host machine and connect target board remote. Provide target board user name and IP address to the below command.
	$ ssh <user_name>@<IP_Address> 
	Once remote login target board and run the below command to assign a break point to the kernel.
	$ sudo su
	=># echo g > /proc/sysrq-trigger


### 4.2. Step 2: Switch KDB to KGDB

	Enter kgdb command in kdb prompt. 

	kdb> kgdb <ENTER>
		You will now see "Entering please attach debugger or use $D#44 or $3#33"
	Close serial port terminal (minicom or teraterm) and open terminal in host machine.
	Assuming serial port device name is ttyUSB0


### 4.3. Step 3: Remote Debugging with GDB

	Bydefault normal user doesn't have permission, need to enable permissions to /dev/ttyUSB0:
	$ sudo adduser $USER dialout 
	$ sudo reboot

	$arm-linux-gnueabihf-gdb vmlinn (this command shows gdb prompt it is called KGDB because image name is “vmlinux”)
		(gdb) set serial baud 115200
		(gdb) target remote /dev/ttyUSB0
		(gdb) bt (shows back trace of kgdb_breakpoint())
		(gdb) b omap_gpio_get
		(gdb) c (continue)

### 4.4. Step 4: Read gpio pin value from sysfs.

	$ cd /sys/class/gpio/gpio9
	$ cat value
		Than you will see the gdb prompt with break point triggered
