
<!-- vim-markdown-toc GFM -->

* [Exp 30:  Apply u-boot patches in to “beagleboneblack-uboot.git” repository using yocto build system](#exp-30--apply-u-boot-patches-in-to-beagleboneblack-ubootgit-repository-using-yocto-build-system)
	* [1. u-boot patch file:](#1-u-boot-patch-file)
	* [2. Yocto Project Source code modification:](#2-yocto-project-source-code-modification)
		* [2a. Without Patch [Manual modification]](#2a-without-patch-manual-modification)
		* [2b. With Patch](#2b-with-patch)
	* [3. Build U-boot source code using bitbake command](#3-build-u-boot-source-code-using-bitbake-command)
	* [3. Expected Results:](#3-expected-results)

<!-- vim-markdown-toc -->

### Exp 30:  Apply u-boot patches in to “beagleboneblack-uboot.git” repository using yocto build system
 
#### 1. u-boot patch file:

Enable LED, Switch mux configuration in u-boot source code and create patches.
This patch file is located in to the current folder u-boot-patch folder.
	
	Patch Name: 0001-Enable-GPIO9-Buz-10-LED-11-SW-Mux.patch

#### 2. Yocto Project Source code modification:

##### 2a. Without Patch [Manual modification]  

Copy u-boot patch file "0001-Enable-GPIO9-Buz-10-LED-11-SW-Mux.patch" in to "meta-bbb/recipes-bsp/u-boot/files" folder. 

And also update this patch file information in to "u-boot_%.bbappend" file.
    
	meta-bbb/recipes-bsp/u-boot/u-boot_%.bbappend
                                files/
                                      0001-Enable-GPIO9-Buz-10-LED-11-SW-Mux.patch

**Modifications to create a commit ID & Tag**

    $ cd ~/poku-zeus-bbb/
    $ git add meta-bbb/recipes-bsp/u-boot/u-boot_%.bbappend
    $ git add meta-bbb/recipes-bsp/u-boot/files/0001-Enable-GPIO9-Buz-10-LED-11-SW-Mux.patch
    $ git commit "Apply KM-BBB “beagleboneblack-uboot” patches in to yocto project"
    
    Tag: Exp3

##### 2b. With Patch 
The above yocto source code modifications are comes with the below patch file.

	Patch Name: 0001-To-apply-KM-BBB-beagleboneblack-uboot-patches-in-to-.patch

Apply patch with the below command.

  	poky-zeusu-bbb$ git am 0001-To-add-KM-BBB-beagleboneblack-uboot-repo-in-to-yocto.patch

#### 3. Build U-boot source code using bitbake command

u-boot is receipe in yocto project, so run the below command in build folder.

	build/$ bitbake u-boot
	
yocto build system downloads beagleboneblack-uboot.git repository from Kernel Masters GITHUB, master branch and iapply the patch and build u-boot source code.


#### 3. Expected Results: 

 “gpio input 11” & “gpio output 10” commands are working in u-boot command prompt.
