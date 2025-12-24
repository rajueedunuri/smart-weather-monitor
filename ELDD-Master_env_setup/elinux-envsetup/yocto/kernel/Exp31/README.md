## Exp 31: Add “beagleboneblack-kernel.git” repository [Kernel Version 4.19.94] in to yocto project.

#### 1. Yocto Project Source code modification:
  
##### 1a. Without Patch [Manual modification]  

**Step1:Choose Kernel Version**
 
Enable PREFERRED_VERSION_linux-stable flag and modify kernel version to 4.19.94 in  meta-bbb/conf/local.conf.sample file and also build/conf/local.conf

**Step2: Repository details update in to bitbake file**

ADD “beagleboneblack-kernel.git” repository in meta layer in "meta-bbb/recipes-kernel/linux/linux-stable_4.19.bb" file.

     Repository Details:
     Branch: master
     Commit ID: 58ac7b864e15789f208b285202bbc31c91edd259
     URL:  https://github.com/kernelmasters/beagleboneblack-kernel.git      

**Step3: Kernel Extra version update in to defconfig file**

	meta-bbb/recipes-kernel/linux/linux-stable-4.19/beaglebone/defconfig

**Modifications to create a commit ID & Tag**

    $ cd ~/poku-zeus-bbb/
    $ git add meta-bbb/conf/local.conf.sample
    $ git add meta-bbb/recipes-kernel/linux/linux-stable_4.19.bb
    $ git commit "To add beagleboneblack-kernel repo in to yocto project"

	Tag: Exp4

##### 1b. With Patch 
The above source code modifications are there is the current folder in the form of patch.

	Patch Name:0001-To-add-beagleboneblack-kernel-repo-in-to-yocto-proje.patch 

Apply the patch with the below command.

	poky-zeusu-bbb$ git am 0001-To-add-beagleboneblack-kernel-repo-in-to-yocto-proje.patch

#### 2. Build Kernel source code using bitbake command

linux-stable is receipe in yocto project, so run the below command in build folder.

	build/$ bitbake linux-stable
	
yocto build system downloads beagleboneblack-kernel.git repository from Kernel Masters GITHUB, master branch and build kernel source code.

	kernel source code location: 
	/home/km/poky-zeus-bbb/build/tmp/work-shared/beaglebone/kernel-source


#### 3. Expected Results: 

Input event device file is not created in /dev/input folder. 
    
“evtest” application unable to read switch events from Linux user command prompt.