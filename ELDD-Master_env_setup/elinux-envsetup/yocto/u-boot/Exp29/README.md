
<!-- vim-markdown-toc GFM -->

* [Exp 29: Add “beagleboneblack-uboot.git” repository [U-boot version 2019.04] in to yocto project.](#exp-29-add-beagleboneblack-ubootgit-repository-u-boot-version-201904-in-to-yocto-project)
		* [1. Yocto Project Source code modification:](#1-yocto-project-source-code-modification)
			* [1a. Without Patch [Manual modification]](#1a-without-patch-manual-modification)
			* [1b. With Patch](#1b-with-patch)
		* [2. Build U-boot source code using bitbake command](#2-build-u-boot-source-code-using-bitbake-command)
		* [3. Expected Results:](#3-expected-results)

<!-- vim-markdown-toc -->

## Exp 29: Add “beagleboneblack-uboot.git” repository [U-boot version 2019.04] in to yocto project.

#### 1. Yocto Project Source code modification:
  
##### 1a. Without Patch [Manual modification]  

ADD “beagleboneblack-uboot.git” repository in meta layer in "meta/recipes-bsp/u-boot/u-boot-common.inc" file.
 
     Repository Details:
     Branch: master
     Commit ID: c3929a23a38d0aaa46e1fabd50c9486de41452e3
     URL:  https://github.com/kernelmasters/beagleboneblack-uboot.git
     
Disable Patch file in meta-bbb layer in "meta-bbb/recipes-bsp/u-boot/u-boot_%.bbappend" file.

**Modifications to create a commit ID & Tag**

    $ cd ~/poku-zeus-bbb/
    $ git add meta/recipes-bsp/u-boot/u-boot-common.inc
    $ git add meta-bbb/recipes-bsp/u-boot/u-boot_%.bbappend
    $ git commit "To add KM-BBB “beagleboneblack-uboot” repo in to yocto project"

##### 1b. With Patch 
The above source code modifications are there is the current folder in the form of patch.

    Patch Name: 0001-To-add-KM-BBB-beagleboneblack-uboot-repo-in-to-yocto.patch

Apply the patch with the below command otherwise modify the source code manually.

  	poky-zeusu-bbb$ git am 0001-To-add-KM-BBB-beagleboneblack-uboot-repo-in-to-yocto.patch


#### 2. Build U-boot source code using bitbake command

u-boot is receipe in yocto project, so run the below command in build folder.

	build/$ bitbake u-boot
	
yocto build system downloads beagleboneblack-uboot.git repository from Kernel Masters GITHUB, master branch and commit message is "Switch, LED Mux configurations disabled in u-boot source code" and build u-boot source code.

	u-boot configuration file information locate in the below file:
	~/poky-zeus-bbb/meta-yocto-bsp/conf/machine/beaglebone-yocto.conf

#### 3. Expected Results: 

“gpio input 11” & “gpio output 10” commands are not working in u-boot command prompt.
