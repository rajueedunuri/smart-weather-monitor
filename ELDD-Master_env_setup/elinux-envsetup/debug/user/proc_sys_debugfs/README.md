
proc,sys & debug file systems are called Virtual File System [VFS].

User can not organize files in VFS.  does't create a file/directory in VFS.

procfs: [/proc]
---------------
proc file system contains overall system information.

	Example: 
		$ cat /proc/interrupts
		$ cat /proc/iomem
		$ cat /proc/cpuinfo
		$ cat /proc/meminfo


sysfs:[/sys]
------------
sys file system provide device hireachy information and also to get device information or to control the device.

	Example:
		$ cd /sys/class/gpio

debugfs: [/sys/kernel/debug]
----------------------------
	
	Example:
		$ cat /sys/kernel/debug/gpio [shows gpio controller information]



