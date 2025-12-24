## 8. Copying the binaries to an SD card (optional)

After the build completes, the bootloader, kernel and rootfs image files can be found in <TMPDIR>/deploy/images/beaglebone/.

### 8.1. Create SD card 2 Paritions

The meta-bbb/scripts directory has some helper scripts to format and copy the files to a microSD card.
mk2parts.sh

This script will partition an SD card with the minimal 2 partitions required for the boards.

Insert the microSD into your workstation and note where it shows up.

lsblk is convenient for finding the microSD card.

For example

    km@kernelmasters:~/bbb/meta-bbb$ lsblk
    NAME    MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
    sda       8:0    0 931.5G  0 disk
    |-sda1    8:1    0  93.1G  0 part /
    |-sda2    8:2    0  93.1G  0 part /home
    |-sda3    8:3    0  29.8G  0 part [SWAP]
    |-sda4    8:4    0     1K  0 part
    |-sda5    8:5    0   100G  0 part /oe5
    |-sda6    8:6    0   100G  0 part /oe6
    |-sda7    8:7    0   100G  0 part /oe7
    |-sda8    8:8    0   100G  0 part /oe8
    |-sda9    8:9    0   100G  0 part /oe9
    `-sda10   8:10   0 215.5G  0 part /oe10
    sdb       8:16   1   7.4G  0 disk
    |-sdb1    8:17   1    64M  0 part
    `-sdb2    8:18   1   7.3G  0 part

I would use sdb for the format and copy script parameters on this machine.

It doesn’t matter if some partitions from the SD card are mounted. The mk2parts.sh script will unmount them.

**BE CAREFUL with this script. It will format any disk on your workstation**

    ~$ cd ~/poky-zeus-bbb/meta-bbb/scripts
    ~/poky-zeus-bbb/meta-bbb/scripts$ sudo ./mk2parts.sh sdb

You only have to format the SD card once.

### 8.2. Copy MLO & u-boot.img in to SD Card first parition. 

**/media/card**

You will need to create a mount point on your workstation for the copy scripts to use.

    ~$ sudo mkdir /media/card

You only have to create this directory once.

**copy_boot.sh**

This script copies the bootloaders (MLO and u-boot) to the boot partition of the SD card.

The script also copies a uEnv.txt file to the boot partition if it finds one in either

    <TMPDIR>/deploy/images/beaglebone/

or in the local directory where the script is run from.

If you are just starting out, you might just want to do this

    ~/poky-zeus-bbb/meta-bbb/scripts$ cp uEnv.txt-example uEnv.txt

This copy_boot.sh script needs to know the TMPDIR to find the binaries. It looks for an environment variable called OETMP.

For instance, if I had this in the local.conf

    TMPDIR="../../build/tmp"


Then I would export this environment variable before running copy_boot.sh

    ~/poky-seus-bbb/meta-bbb/scripts$ export OETMP="../../build/tmp"

Then run the copy_boot.sh script passing the location of SD card

    ~$ sudo umount /dev/sdb1
    ~$ sudo umount /dev/sdb2
    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_boot.sh sdb

This script should run very fast.

### 8.3. Copy Root file system along with Kerel Image in to SD Card Second parition. 

**copy_rootfs.sh**

This script copies the zImage Linux kernel, the device tree binaries and the rest of the operating system to the root file system partition of the SD card.

The script accepts an optional command line argument for the image type, for example console or qt5. The default is console if no argument is provided.

The script also accepts a hostname argument if you want the host name to be something other then the default beaglebone.

Here’s an example of how you’d run copy_rootfs.sh

    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_rootfs.sh sdb console

or

    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_rootfs.sh sdb qt5 bbb

The copy_rootfs.sh script will take longer to run and depends a lot on the quality of your SD card. With a good Class 10 card it should take less then 30 seconds.

The copy scripts will NOT unmount partitions automatically. If an SD card partition is already mounted, the script will complain and abort. This is for safety, mine mostly, since I run these scripts many times a day on different machines and the SD cards show up in different places.

Here’s a realistic example session where I want to copy already built images to a second SD card that I just inserted.

    ~$ sudo umount /dev/sdb1
    ~$ sudo umount /dev/sdb2
    ~$ export OETMP="../../build/tmp"
    ~$ cd ~/poky-zeus-bbb/meta-bbb/scripts
    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_boot.sh sdb
    ~/poky-zeus-bbb/meta-bbb/scripts$ ./copy_rootfs.sh sdb console bbb2

Both copy_boot.sh and copy_rootfs.sh are simple scripts meant to be modified for custom use.
### 8.4. Summary

    cd /home/km/poky-zeus-bbb/meta-bbb/scripts
    sudo umount /dev/sdb1
    sudo ./mk2parts.sh sdb
    sudo mkdir /media/card
    cp uEnv.txt-example uEnv.txt
    export OETMP="../../build/tmp"
    sudo umount /dev/sdb1
    sudo umount /dev/sdb2
    ./copy_boot.sh sdb
    sudo umount /dev/sdb1
    ./copy_rootfs.sh sdb console

