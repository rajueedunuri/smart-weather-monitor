## bitbake commands

https://elinux.org/Bitbake_Cheat_Sheet

##### the below command shows list the pre-defined Yocto images in all meta files, run the following command from your poky directory

    $ cd poky-zeus-bbb
    $ find . -type f -path '*images/*' -name '*.bb'
    $ bitbake-layers show-recipes "*image*"

##### list of tasks

    $ bitbake <image-name>  -c "listtasks"

    do_build                       Default task for a recipe - depends on all other normal tasks required to 'build' a recipe
    do_build_without_rm_work       
    do_checkuri                    Validates the SRC_URI value
    do_clean                       Removes all output files for a target
    do_cleanall                    Removes all output files, shared state cache, and downloaded source files for a target
    do_cleansstate                 Removes all output files and shared state cache for a target
    do_compile                     Compiles the source in the compilation directory
    do_configure                   Configures the source by enabling and disabling any build-time and configuration options for the software being built
    do_devpyshell                  Starts an interactive Python shell for development/debugging
    do_devshell                    Starts a shell with the environment set up for development/debugging
    do_fetch                       Fetches the source code
    do_image                       
    do_image_complete              
    do_image_complete_setscene      (setscene version)
    do_image_ext4                  
    do_image_qa                    
    do_image_qa_setscene            (setscene version)
    do_image_tar                   
    do_install                     Copies files from the compilation directory to a holding area
    do_listtasks                   Lists all defined tasks for a target
    do_package                     Analyzes the content of the holding area and splits it into subsets based on available packages and files
    do_package_qa_setscene         Runs QA checks on packaged files (setscene version)
    do_package_setscene            Analyzes the content of the holding area and splits it into subsets based on available packages and files (setscene version)
    do_package_write_ipk_setscene  Creates the actual IPK packages and places them in the Package Feed area (setscene version)
    do_packagedata                 Creates package metadata used by the build system to generate the final packages
    do_packagedata_setscene        Creates package metadata used by the build system to generate the final packages (setscene version)
    do_patch                       Locates patch files and applies them to the source code
    do_populate_lic                Writes license information for the recipe that is collected later when the image is constructed
    do_populate_lic_deploy         
    do_populate_lic_setscene       Writes license information for the recipe that is collected later when the image is constructed (setscene version)
    do_populate_sdk                Creates the file and directory structure for an installable SDK
    do_populate_sdk_ext            
    do_populate_sysroot_setscene   Copies a subset of files installed by do_install into the sysroot in order to make them available to other recipes (setscene version)
    do_prepare_recipe_sysroot      
    do_rm_work                     Removes work files after the build system has finished with them
    do_rm_work_all                 Top-level task for removing work files after the build system has finished with them
    do_rootfs                      Creates the root filesystem (file and directory structure) for an image
    do_rootfs_wicenv               
    do_sdk_depends                 
    do_unpack                      Unpacks the source code into a working directory

##### bitbake version
    
    $ bitbake --version

##### Execute particular task

    $ bitbake -c compile <package_name> (do_compile - Compiles the source in the compilation directory)
    $ bitbake -c clean <package_name> (do_clean - Removes all output files for a target)
    $ bitbake -c clean -f <package_name> (do_clean - Removes all output files for a target with force)
    $ bitbake -c cleanall -f <package_name> (do_cleanall - Removes all output files, shared state cache, and downloaded source files for a target)
    $ bitbake -c cleansstate <package name> (do_cleansstate - Removes all output files and shared state cache for a target)

##### You can get a list of locally available packages and their current version with:

    $ bitbake -s

##### Build particular package (do_patch, do_metadata, do_compile)

    $ bitbake <package name>

##### Build package source level 
"devshell" a convenient way to try with some source or inpackage level changes and tryout. 
It does open a new shell at the package location. Where you can give the commands locally. As simple as make.

    $ bitbake <package name> -c devshell

##### You can just simply fetch the source code, no other tasks are going to be executed

    $ bitbake -c fetch -f <package_name>

#### Yocto maintains packages information in a form of manifest file located in 

    /tmp/deploy/images/<"machine_image">/<"image_name">.manifest.

##### You can easily list all the targets/recipes (.bb files) in your workspace doing:

    $ bitbake-layers show-recipes

##### If you want only the recipes for your image, do:

    $ bitbake-layers show-recipes "<image_name>"
