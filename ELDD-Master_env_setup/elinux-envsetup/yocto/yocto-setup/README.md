
<!-- vim-markdown-toc GFM -->

* [Lab Exp 28: Setup yocto](#lab-exp-28-setup-yocto)
	* [1. Setup Yocto Build Environment](#1-setup-yocto-build-environment)
		* [1.1. Yocto Configuration](#11-yocto-configuration)
		* [1.2. Version Information](#12-version-information)
		* [1.3. Ubuntu Setup](#13-ubuntu-setup)
	* [2. Download Zeus 3.0.3 yocto source code](#2-download-zeus-303-yocto-source-code)
	* [3. Initialize the build directory](#3-initialize-the-build-directory)
	* [4. Customize the configuration files - Edit local config files](#4-customize-the-configuration-files---edit-local-config-files)
		* [4.1. Customize Variables](#41-customize-variables)
			* [4.1.1. TMPDIR](#411-tmpdir)
			* [4.1.2. DL_DIR](#412-dl_dir)
			* [4.1.3. SSTATE_DIR](#413-sstate_dir)
		* [4.2. ROOT PASSWORD](#42-root-password)
	* [5. Types of yocto images](#5-types-of-yocto-images)
		* [5.1. console-image](#51-console-image)
		* [5.2. qt5-image](#52-qt5-image)
		* [5.3. Installer-image](#53-installer-image)
	* [6. Build Console Image](#6-build-console-image)
	* [7. How to install yocto images](#7-how-to-install-yocto-images)
		* [7.1. Format SD card and create single partition](#71-format-sd-card-and-create-single-partition)
		* [7.2. Copy console image in to sd card](#72-copy-console-image-in-to-sd-card)
	* [8. Booting from the SD card](#8-booting-from-the-sd-card)
	* [9.  ERROR 1](#9--error-1)

<!-- vim-markdown-toc -->

# Lab Exp 28: Setup yocto

	Setup Embedded Linux Developemnt environment with Yocto project using Beaglebone black hardware.

	Yocto is a set of tools for building a custom embedded Linux distribution. The systems are usually targeted at particular applications like commercial products.

## 1. Setup Yocto Build Environment

### 1.1. Yocto Configuration
Yocto uses **meta-layers** to define the configuration for a system build. Within each meta-layer are recipes, classes and configuration files that support the primary python build tool, **bitbake**.

The meta-bbb layer generates some basic systems with packages that support C, C++, Qt5, Perl and Python development, the languages and tools we commonly use. Other languages are supported.

We use this layer as a template when starting new BeagleBone projects. And We create a new layer "meta-km-bbb" for **KM-BBB Expansion board.**


### 1.2. Version Information
- Yocto Version: Zeus 3.0.3
- Bitbake Version: 1.44
- u-boot version: 2019
- Kernel Version: 4.19.94

### 1.3. Ubuntu Setup
- Ubuntu version 18.04 supports.
- Multi core processor recommanded
- RAM size min. 4GB recommanded.
- Install Kernel Masters OS 2.0 from the below link:

 https://kernelmasters.org/blog/2020/05/17/download-install-kernel-masters-customized-linux/
 
The below packages installed in Ubuntu 18.04

         $ sudo apt install libncurses5-dev python python3-distutils texinfo gawk wget git-core diffstat unzip texinfo gcc-multilib build-essential chrpath socat cpio python3 python3-pip python3-pexpect xz-utils debianutils iputils-ping python3-git python3-jinja2 libegl1-mesa libsdl1.2-dev pylint3 xterm

For all versions of Ubuntu, you should change the default Ubuntu shell from dash to bash by running this command from a shell.

         $ sudo dpkg-reconfigure dash
 
 Choose **NO** to dash when prompted.
## 2. Download Zeus 3.0.3 yocto source code

 - Enter Home Directory

         $ cd ~

 - Clone poky-zeus-bbb repo

        ~$ git clone https://github.com/kernelmasters/poky-zeus-bbb.git

## 3. Initialize the build directory
 - Enter poky repo folder

       ~$ cd poky-zeus-bbb

 - Initialize the build directory

       ~/poky-zeus-bbb$ source oe-init-build-env

After Initalization of build directory, current working directory is build.

## 4. Customize the configuration files - Edit local config files
      BBB configuration files replace with default configuration files

      ~$ cp ~/poky-zeus-bbb/meta-bbb/conf/local.conf.sample ~/poky-zeus-bbb/build/conf/local.conf
      ~$ cp ~/poky-zeus-bbb/meta-bbb/conf/bblayers.conf.sample ~/poky-zeus-bbb/build/conf/bblayers.conf

### 4.1. Customize Variables

The variables you may want to customize are the following:

    TMPDIR
    DL_DIR
    SSTATE_DIR

The defaults for all of these work fine. Adjustments are optional.

#### 4.1.1. TMPDIR

This is where temporary build files and the final build binaries will end up. Expect to use at least 35GB. You probably want at least 50GB available.
The default location is in the build directory, in this example ~/bbb/build/tmp.
If you specify an alternate location as I do in the example conf file make sure the directory is writable by the user running the build.

#### 4.1.2. DL_DIR

This is where the downloaded source files will be stored. You can share this among configurations and build files so I created a general location for this outside the project directory. Make sure the build user has write permission to the directory you decide on.
The default location is in the build directory, ~/bbb/build/sources.

#### 4.1.3. SSTATE_DIR

This is another Yocto build directory that can get pretty big, greater then 5GB. I often put this somewhere else other then my home directory as well.
The default location is in the build directory, ~/bbb/build/sstate-cache.

### 4.2. ROOT PASSWORD

There is only one login user by default, root.

The default password is set to **km** by these two lines in the local.conf file

    INHERIT += "extrausers"
    EXTRA_USERS_PARAMS = "usermod -P km root; "

These two lines force a password change on first login

    INHERIT += "chageusers"
    CHAGE_USERS_PARAMS = "chage -d0 root; "

You can comment them out if you do not want that behavior.

## 5. Types of yocto images

You need to source the Yocto environment into your shell before you can use bitbake. The oe-init-build-env will not overwrite your customized conf files.

    ~$ source ~/poky-zeus-bbb/oe-init-build-env 

    ### Shell environment set up for builds. ###

    You can now run 'bitbake <target>'

    Common targets are:
          core-image-minimal
          core-image-sato
          meta-toolchain
          meta-ide-support

    You can also run generated qemu images with a command like 'runqemu qemux86'

    Other commonly useful commands are:
         - 'devtool' and 'recipetool' handle common recipe tasks
         - 'bitbake-layers' handles common layer tasks
        - 'oe-pkgdata-util' handles common target package tasks

    ~/bbb/build$

 I don’t use any of the Common targets, but instead use my own custom image recipes.

There are a few custom images available in the meta-bbb layer. The recipes for the images can be found in meta-bbb/images/

          core-image-minimal
          core-image-sato
          meta-toolchain
          meta-ide-support

You should add your own custom images to this same directory.

### 5.1. console-image

A basic console developer image. See the recipe meta-bbb/images/console-image.bb for specifics, but some of the installed programs are

    gcc/g++ and associated build tools
    git
    ssh/scp server and client
    python3 with a number of modules

The console-image has a line

    inherit core-image

which is poky-dunfell/meta/classes/core-image.bbclass and pulls in some required base packages. This is useful to know if you create your own image recipe.

### 5.2. qt5-image

This image includes the console-image and adds Qt5 runtime libraries.

### 5.3. Installer-image

This is a minimal image meant only to run from an SD card and whose only purpose is to perform an eMMC installation.

## 6. Build Console Image

To build the console-image run the following command

    ~/poky-zeus-bbb/build$ bitbake console-image

You may occasionally run into build errors related to packages that either failed to download or sometimes out of order builds. The easy solution is to clean the failed package and rerun the build again.

For instance if the build for zip failed for some reason, I would run this

~/bbb/build$ bitbake -c cleansstate zip
~/bbb/build$ bitbake zip

And then continue with the full build.

    ~/poky-zeus-bbb/build$ bitbake console-image

The cleansstate command (with two s’s) works for image recipes as well.

The image files won’t get deleted from the TMPDIR until the next time you build

## 7. How to install yocto images 
 
### 7.1. Format SD card and create single partition

	$ cd /home/km/poky-zeus-bbb/meta-bbb/scripts
	$ sudo ./mk1parts.sh --mmc /dev/sdx

### 7.2. Copy console image in to sd card

	$ cd /home/km/poky-zeus-bbb/meta-bbb/scripts
	$ sudo ./km-bbb-yocto-install.sh <--mmc /dev/sdx> <--image console>

## 8. Booting from the SD card

The default behavior of the beaglebone is to boot from the eMMC first if it finds a bootloader there.

Holding the S2 switch down when the bootloader starts will cause the BBB to try booting from the SD card first. The S2 switch is above the SD card holder.

If you are using a cape, the S2 switch is usually inaccessible or at least awkward to reach. From the back of the board a temporary jump of P8.43 to ground when the bootloader starts will do the same thing as holding the S2 switch.


## 9.  ERROR 1

 checking for python3... python3
 
 checking version of python3... 3.6.9, ok
 
 configure: error:
   *** These critical programs are missing or too old: GNU ld
   
   *** Check the INSTALL file for required versions.

**Solution:** 
Enable bash shell using the below command

    $ sudo dpkg-reconfigure dash

