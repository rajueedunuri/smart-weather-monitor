
<!-- vim-markdown-toc GFM -->

* [Building U-boot specific task:](#building-u-boot-specific-task)
	* [To clean the image:](#to-clean-the-image)
	* [To download u-boot source code:](#to-download-u-boot-source-code)
	* [To apply patches to u-boot source code:](#to-apply-patches-to-u-boot-source-code)
	* [To build u-boot source code:](#to-build-u-boot-source-code)
	* [To add the image into deploy directory:](#to-add-the-image-into-deploy-directory)
* [Building U-boot all tasks:](#building-u-boot-all-tasks)

<!-- vim-markdown-toc -->

## Building U-boot specific task:

### To clean the image:

	$ bitbake -c clean u-boot

### To download u-boot source code:

	$ bitbake -c fetch u-boot

### To apply patches to u-boot source code:

	$ bitbake -c patch u-boot

### To build u-boot source code:

	$ bitbake -c compile u-boot

	Example directory where build is located: 
	/home/km/poky-zeus-bbb/build/tmp/work/beaglebone-poky-linux-gnueabi/u-boot/1_2019.07-r0

### To add the image into deploy directory:

	$ bitbake -c deploy u-boot
	Example directory where to deply u-boot:
	/home/km/poky-zeus-bbb/build/tmp/deploy/images/beaglebone/	

## Building U-boot all tasks:

	$ bitbake u-boot
