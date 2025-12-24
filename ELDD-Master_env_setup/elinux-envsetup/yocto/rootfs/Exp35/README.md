
<!-- vim-markdown-toc GFM -->

* [Lab Exp 35: Add a custom application](#lab-exp-35-add-a-custom-application)
	* [Step 1: Setup and organization](#step-1-setup-and-organization)
	* [Step 2: About helloworld application](#step-2-about-helloworld-application)
	* [Step 3: Write the common recipe](#step-3-write-the-common-recipe)
	* [Step 4: Write the version specific recipe](#step-4-write-the-version-specific-recipe)
		* [Step 5: Testing and troubleshooting](#step-5-testing-and-troubleshooting)
		* [Step 6: Update the rootfs](#step-6-update-the-rootfs)
		* [Step 7: Copy rootfs image in to target board & Test](#step-7-copy-rootfs-image-in-to-target-board--test)

<!-- vim-markdown-toc -->

## Lab Exp 35: Add a custom application

Add a new recipe to support a required custom application

Example: Hello World Application


### Step 1: Setup and organization

In this lab we will add a recipe handling the “helloworld” application. 
Create a “recipes-helloworld” directory under meta-km-bbb layer.
Create a “helloworld” sub directory for application under “recipes-helloworld” directory.

    $ mkdir -p  meta-km-bbb/recipes-helloworld/helloworld

A recipe for an application is usually divided into a version specific bb file and a common one.
Try to follow this logic and separate the configuration variables accordingly.
Tip: it is possible to include a file into a recipe with the keyword require.

The IMAGE_INSTALL variable controls the packages included into the output image.
You can add packages (IMAGE_INSTALL += “helloworld”) to be built by editing the below any one of the configuration file.

    Local configuration file:   (not recommended) 
    build/conf/local.conf. 
    image configuration file:
    meta-bbb/images/console-image.bb


### Step 2: About helloworld application

The helloworld application is print “hello world” to the monochrome LCD. 

Uses autotools build system. 

First try to find the project homepage, download the sources and have a first look: license,
Makefile, requirements…

    Source Code URL: https://github.com/kernelmasters/yocto-helloworld.git


### Step 3: Write the common recipe

Create an appropriate common file, ending in .inc (helloworld.inc)
In this file add the common configuration variables: source URI, description…

    DESCRIPTION = "Example Hello, World application for Yocto build."
    SRCREV = "fba6d4539310ced763e3a1c24ce9c4459b2fc8fa"
    SRC_URI = "git://github.com/kernelmasters/yocto-helloworld.git"

### Step 4: Write the version specific recipe

Create a file that respects the Yocto nomenclature: ${PN}_${PV}.bb (helloworld_1.0.bb)
Add the required common configuration variables: archive checksum, license file checksum,
package revision…

    Generate LICENSE
    $ md5sum LICENSE 
    b2424aed282074c27f97c20dcbf25df3  LICENSE


    require helloworld.inc
    SECTION = "helloworld"
    DEPENDS = ""
    LICENSE = "MIT"
    LIC_FILES_CHKSUM = "file://LICENSE;md5=b2424aed282074c27f97c20dcbf25df3"
    FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}-${PV}:"
    S = "${WORKDIR}/git"
    inherit autotools

#### Step 5: Testing and troubleshooting
You can check the whole packaging process is working fine by explicitly running the build task on the “helloworld” recipe:

    $ bitbake helloworld

Try to make the recipe on your own. Also eliminate the warnings related to your recipe: some configuration variables are not mandatory but it is a very good practice to define them all.

If you hang on a problem, check the following points:
• The common recipe is included in the version specific one
• The checksum and the URI are valid
• The dependencies are explicitly defined
• The internal state has changed, clean the working directory:

    $ bitbake -c cleanall helloworld

Tip: BitBake has command line flags to increase its verbosity and activate debug outputs. Also, remember that you need to cross-compile “helloworld” for ARM! Maybe, you will have to configure your recipe to resolve some mistakes done in the application’s Makefile (which is often the case).

A bitbake variable permits to add some Makefile’s options, you should look for it.

#### Step 6: Update the rootfs 

Now that you’ve compiled the “helloworld” application, generate a new rootfs image.

    $ bitbake console-image. 

    ~/poky-zeus-bbb/build$ cat tmp/deploy/images/beaglebone/console-image-beaglebone-20210604200624.rootfs.manifest | grep helloworld
    helloworld cortexa8hf-neon 1.0-r0

#### Step 7: Copy rootfs image in to target board & Test


    $ sudo ./km-bbb-yocto-install.sh --mmc /dev/sdb console


Access the board command line through SSH. You should be able to launch the “hellowrold” program. Now, it’s time to play!

    root@beaglebone:~# helloworld
    GPIO pin:44 has export done
    GPIO pin:45 has export done
    GPIO pin:46 has export done
    GPIO pin:47 has export done
    GPIO pin:86 has export done
    GPIO pin:87 has export done
    GPIO pin:88 has export done

Tag: 
Commit ID: “Add a ‘helloworld’ custom package in to rootfs”

