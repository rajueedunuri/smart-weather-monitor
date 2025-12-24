### Exp 32:  Apply Kernel patches in to “beagleboneblack-kernel.git” repository using yocto build system
 
#### 1. kernel patch file:

Enable LED, Switch mux configuration and enable enter switch device in device tree source code and modifcations are created in two patches.

This patch files are located in to the current folder kernel-patch folder.
	
	Patch Files:
	0001-Mux-Config-in-DTS-LCD_DATA_13.GPIO0_9-LCD_DATA14.GPI.patch
	0002-GPIO-Project-Enter-Switch-GPIO11-Raising-Edge-Interr.patch

#### 2. Yocto Project Source code modification:

##### 2a. Without Patch [Manual modification]  

Copy above kernel patch files in to " meta-bbb/recipes-kernel/linux/linux-stable-4.19/files" folder. 

	meta-bbb/recipes-kernel/linux/linux-stable-4.19/
							0001-Mux-Config-in-DTS-LCD_DATA_13.GPIO0_9-LCD_DATA14.GPI.patch
							0002-GPIO-Project-Enter-Switch-GPIO11-Raising-Edge-Interr.patch

And also update this patch file information in to "meta-bbb/recipes-kernel/linux/linux-stable_4.19.bb" file.
    
**Modifications to create a commit ID & Tag**

	$ cd ~/poku-zeus-bbb/
	$ git add meta-bbb/recipes-kernel/linux/linux-stable_4.19.bb
	$ git add meta-bbb/recipes-kernel/linux/linux-stable-4.19/0001-Mux-Config-in-DTS-LCD_DATA_13.GPIO0_9-LCD_DATA14.GPI.patch
	$ git add meta-bbb/recipes-kernel/linux/linux-stable-4.19/0002-GPIO-Project-Enter-Switch-GPIO11-Raising-Edge-Interr.patch
	$ git commit "Apply kernel patches in to beagleboneblack-kernel repo"
    
    	Tag: Exp5

##### 2b. With Patch 
The above yocto source code modifications are comes with the below patch file.

	Patch Name: 0001-To-apply-patches-in-to-beaglebone-kernel-repo.patch

Apply patch with the below command.

  	poky-zeusu-bbb$ git am 0001-To-apply-patches-in-to-beaglebone-kernel-repo.patch

#### 3. Build Kernel source code using bitbake command

u-boot is receipe in yocto project, so run the below command in build folder.

	build/$ bitbake linux-stable
	
yocto build system downloads beagleboneblack-kernel.git repository from Kernel Masters GITHUB, master branch and apply the patch and build kernel source code.


#### 4. Expected Results: 

Input event device file is created in /dev/input folder. 

“evtest” application properly read switch events from Linux user command prompt.
