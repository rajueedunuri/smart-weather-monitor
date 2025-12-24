
<!-- vim-markdown-toc GFM -->

* [Lab Exp 33: Create a Yocto layer](#lab-exp-33-create-a-yocto-layer)
	* [Step 1: Create a new layer](#step-1-create-a-new-layer)
	* [Step 2: Integrate a layer to the build](#step-2-integrate-a-layer-to-the-build)
	* [Step 3: Add a recipe to the layer](#step-3-add-a-recipe-to-the-layer)
	* [Expected Results:](#expected-results)

<!-- vim-markdown-toc -->


## Lab Exp 33: Create a Yocto layer

Add a custom layer to the Yocto project for your project needs

- Create a new Yocto layer
- Interface this custom layer to the existing Yocto project
- Use applications from custom layers

Commands:

    $ bitbake-layers –h
    $ bitbake-layers show-layers


### Step 1: Create a new layer

This new layer was responsible for Kernel Masters Beagle Bone Black Expansion board support in Yocto.

    $ bitbake-layers create-layer --help
    $ cd ~/poky-zeus-bbb
    $ bitbake-layers create-layer meta-km-bbb

With the above commands, create a new Yocto layer named “meta-km-bbb” with a priority of 7.

Before using the new layer, we need to configure its generated configuration files. 

You can start with the README file which is not used in the build process but contains information related to layer maintenance. 

You can then check, and adapt if needed, the global layer configuration file located in the conf directory of your custom layer


### Step 2: Integrate a layer to the build

“build/conf/bblayers.conf” file which contains all the paths of the layers we use.
In this file add the full path to our newly created layer to the list of layers.

Validate the integration of the meta-km-bbb layer with:
$ bitbake-layers show-layers
and make sure you don’t have any warning from bitbake.

### Step 3: Add a recipe to the layer
You should instead always use a custom layer to add recipes or to customize the existing ones. 

    $ bitbake-layers show-recipes
    $ cd ~/poky-zeus-bbb
    $ mkdir -p meta-km-bbb/recipes-km-bbb-kernel/linux
    Create “linux-stable_%.bbappend” file inside linux folder and write the below content. 

    FILESEXTRAPATHS_prepend := "${THISDIR}/patches:"
    SRC_URI += "file://0001-Add-Volume-UP-DOWN-Switches.patch"

Create a “file” folder inside linux folder and copy patches in this folder.

    $ bitbake-layers show-recipes | grep km-bbb

    You can also find detailed information on available packages, their current version, dependencies or the contact information of the maintainer by visiting
    http://recipes.yoctoproject.org/
    $ bitbake –v linux-stable –c cleanall
    $ bitbake -v linux-stable


### Expected Results:

NOTE: linux-stable-4.19.94-r0 do_patch: Applying patch '0001-Setup-Kernel-Environment.patch' (../meta-bbb/recipes-kernel/linux/linux-stable-4.19/0001-Setup-Kernel-Environment.patch)

NOTE: linux-stable-4.19.94-r0 do_patch: Applying patch '0002-Mux-Config-in-DTS-LCD_DATA_13.GPIO0_9-LCD_DATA14.GPI.patch'
 (../meta-bbb/recipes-kernel/linux/linux-stable-4.19/0002-Mux-Config-in-DTS-LCD_DATA_13.GPIO0_9-LCD_DATA14.GPI.patch)

NOTE: linux-stable-4.19.94-r0 do_patch: Applying patch '0005-Enter-Switch-GPIO11-Raising-Edge-Interrupt-porting-o.patch' 
(../meta-km-bbb/recipes-km-bbb-kernel/linux/patches/0005-Enter-Switch-GPIO11-Raising-Edge-Interrupt-porting-o.patch)

Commit ID: “Create meta-km-bbb layer and also create recipes-bsp, recipes-kernel inside the layer”

The following packages build in console-image:

$ bitbake -DDD console-image

DEBUG: sorted providers for console-image are: ['/home/km/poky-zeus-bbb/meta-bbb/images/console-image.bb']
DEBUG: adding /home/km/poky-zeus-bbb/meta-bbb/images/console-image.bb to satisfy console-image
DEBUG: Added dependencies ['qemuwrapper-cross', 'depmodwrapper-cross', 'cross-localedef-native'] for /home/km/poky-zeus-bbb/meta-bbb/images/console-image.bb
DEBUG: Added runtime dependencies ['openssh', 'openssh-keygen', 'openssh-sftp-server', 'packagegroup-core-boot', 'term-prompt', 'tzdata', 'binutils', 'binutils-symlinks', 'coreutils', 'cpp', 'cpp-symlinks', 'diffutils', 'elfutils', 'elfutils-binutils', 'file', 'gcc', 'gcc-symlinks', 'g++', 'g++-symlinks', 'gdb', 'gettext', 'git', 'ldd', 'libstdc++', 'libstdc++-dev', 'libtool', 'ltrace', 'make', 'perl-modules', 'pkgconfig', 'python3-modules', 'strace', 'bzip2', 'curl', 'dosfstools', 'e2fsprogs-mke2fs', 'ethtool', 'fbset', 'findutils', 'grep', 'i2c-tools', 'ifupdown', 'iperf3', 'iproute2', 'iptables', 'less', 'lsof', 'netcat-openbsd', 'nmap', 'ntp', 'ntp-tickadj', 'parted', 'procps', 'rndaddtoentcnt', 'sysfsutils', 'tcpdump', 'util-linux', 'util-linux-blkid', 'unzip', 'wget', 'zip', 'kernel-modules', 'emmc-upgrader', 'firewall', 'serialecho', 'spiloop', 'bbgw-wireless', 'crda', 'iw', 'linux-firmware-wl12xx', 'linux-firmware-wl18xx', 'wpa-supplicant', 'checksec', 'ncrack', 'nikto', 'python3-scapy', 'wireguard-init', 'wireguard-tools', 'run-postinsts', 'opkg', 'base-passwd', 'shadow', 'base-passwd', 'shadow', 'locale-base-en-us'] for /home/km/poky-zeus-bbb/meta-bbb/images/console-image.bb


