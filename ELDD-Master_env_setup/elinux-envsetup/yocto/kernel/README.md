
<!-- vim-markdown-toc GFM -->

* [Building Kernel specific task:](#building-kernel-specific-task)
	* [To clean the image:](#to-clean-the-image)
	* [To download linux-stable source code:](#to-download-linux-stable-source-code)
	* [To apply patches to linux-stable source code:](#to-apply-patches-to-linux-stable-source-code)
	* [To build linux-stable source code:](#to-build-linux-stable-source-code)
	* [To add the image into deploy directory:](#to-add-the-image-into-deploy-directory)
* [Building kernel  all tasks with one command:](#building-kernel--all-tasks-with-one-command)

<!-- vim-markdown-toc -->

## Building Kernel specific task:

### To clean the image:

	$ bitbake -c clean linux-stable

### To download linux-stable source code:

	$ bitbake -c fetch linux-stable

	Example directory where to download source code 
	/home/km/poky-zeus-bbb/build/tmp/work/beaglebone-poky-linux-gnueabi/linux-stable/5.6.19-r0/git
	/home/km/poky-zeus-bbb/build/tmp/work-shared/beaglebone/kernel-source

### To apply patches to linux-stable source code:

	$ bitbake -c patch linux-stable

### To build linux-stable source code:

	$ bitbake -c compile linux-stable

	Example directory where build output is located: 
	/home/km/poky-zeus-bbb/build/tmp/work/beaglebone-poky-linux-gnueabi/linux-stable/5.6.19-r0/build

### To add the image into deploy directory:
	$ bitbake -c deploy linux-stable

	Example directory where to deploy images:
	/home/km/poky-zeus-bbb/build/tmp/deploy/images/beaglebone

## Building kernel  all tasks with one command:

	$ bitbake linux-stable
