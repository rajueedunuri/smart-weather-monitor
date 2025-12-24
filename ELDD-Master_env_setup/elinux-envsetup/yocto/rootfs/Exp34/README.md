
<!-- vim-markdown-toc GFM -->

* [Lab Exp 34: Add an existing application](#lab-exp-34-add-an-existing-application)
	* [Step 1: check yocto support.](#step-1-check-yocto-support)
	* [Step 2: Add an “evtest” package in to configuration file](#step-2-add-an-evtest-package-in-to-configuration-file)
	* [Step 3: Add an “evtest” binary in to the rootfs image](#step-3-add-an-evtest-binary-in-to-the-rootfs-image)
		* [3a: First build “evtest” package & then build console-image](#3a-first-build-evtest-package--then-build-console-image)
		* [3b. Build console-image only](#3b-build-console-image-only)
	* [Step 4: Verify “evtest” package](#step-4-verify-evtest-package)
	* [Step 5: Expected Results](#step-5-expected-results)

<!-- vim-markdown-toc -->


## Lab Exp 34: Add an existing application

Example: “evtest” application


### Step 1: check yocto support.

Find out “evtest” package in yocto repo. 

    ~/poky-zeus-bbb$ find meta* | grep evtest
    meta-openembedded/meta-oe/recipes-test/evtest
    meta-openembedded/meta-oe/recipes-test/evtest/evtest_1.34.bb
    meta-openembedded/meta-oe/recipes-test/evtest/evtest
    meta-openembedded/meta-oe/recipes-test/evtest/evtest/add_missing_limits_h_include.patch

The above messages shows evtest application is part of openembedded layer. 
But by default “evtest” application is not a part of console-image. 
The below command doesn’t build “evtest” application in console-image 

    ~/poky-zeus-bbb/build$ bitbake -v console-image

And also check in manifest file in output folder.

    $ cat ~/poky-zeus-bbb/build/tmp/deploy/images/beaglebone/console-image-beaglebone-*.rootfs.manifest | grep evtest 

Next step we need to add “evtest” application in console-image.

### Step 2: Add an “evtest” package in to configuration file

The IMAGE_INSTALL variable controls the packages included into the output image.
To illustrate this, add the “evtest” to the list of enabled packages.
You can add packages (IMAGE_INSTALL += “evtest”) to be built by editing the below any one of the configuration file.

    Local configuration file:   (not recommended) 
    build/conf/local.conf. 

    image configuration file:
    meta-bbb/images/console-image.bb


    IMAGE_INSTALL += " \
        emmc-upgrader \
        firewall \
        ${DEV_EXTRAS} \
        ${WIFI} \
        ${SECURITY_TOOLS} \
        ${WIREGUARD} \
        evtest \
    "

	
### Step 3: Add an “evtest” binary in to the rootfs image

Two ways are possible to add evtest binary in to rootfs iamge.

#### 3a: First build “evtest” package & then build console-image

    $ bitbake evtest 

Start a shell with the “evtest” environment set up for development/debugging. (Optional)

    $ bitbake evtest -c devshell

Finally you add in console-image

    $ bitbake -v console-image

#### 3b. Build console-image only

This command identifies evtest application, first build evtest application then build console-image. 

    $ bitbake -v console-image

### Step 4: Verify “evtest” package

    ~/poky-zeus-bbb/build$ cat tmp/deploy/images/beaglebone/console-image-beaglebone-20210604183836.rootfs.manifest | grep evtest
    evtest cortexa8hf-neon 1.34-r0

    manifest file syntax:
    <Package-name> <arch-name> <package-version>

### Step 5: Expected Results

Copy rootfs image in to target board. 

    $ sudo ./km-bbb-yocto-install.sh --mmc /dev/sdb console

    Test “”evtest” package on target board, application runs properly.
    root@beaglebone:~# evtest
    No device specified, trying to scan all of /dev/input/event*
    Available devices:
    /dev/input/event0:      gpio-keys
    Select the device event number [0-0]: 0
    Input driver version is 1.0.1
    Input device ID: bus 0x19 vendor 0x1 product 0x1 version 0x100
    Input device name: "gpio-keys"
    Supported events:
    Event type 0 (EV_SYN)
    Event type 1 (EV_KEY)
        Event code 28 (KEY_ENTER)
    Key repeat handling:
    Repeat type 20 (EV_REP)
        Repeat code 0 (REP_DELAY)
        Value    250
        Repeat code 1 (REP_PERIOD)
        Value     33
    Properties:
    Testing ... (interrupt to exit)
    Event: time 1622869843.388934, type 1 (EV_KEY), code 28 (KEY_ENTER), value 1
    Event: time 1622869843.388934, -------------- SYN_REPORT ------------
    Event: time 1622869843.600816, type 1 (EV_KEY), code 28 (KEY_ENTER), value 0
    Event: time 1622869843.600816, -------------- SYN_REPORT ------------
    Event: time 1622869843.889188, type 1 (EV_KEY), code 28 (KEY_ENTER), value 1
    Event: time 1622869843.889188, -------------- SYN_REPORT ------------
    Event: time 1622869844.051879, type 1 (EV_KEY), code 28 (KEY_ENTER), value 0

    Tag: 

