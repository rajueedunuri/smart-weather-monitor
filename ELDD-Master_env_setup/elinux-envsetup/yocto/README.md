# Yocto Project

## Poky

The Yocto project provides a reference build system for embedded Linux, called Poky, which has the BitBake and OpenEmbedded-Core (OE-Core) projects at its base. 

The purpose of Poky is to build the components needed for an embedded Linux product, namely:
- A bootloader image
- A Linux kernel image
- A root filesystem image
- Toolchains and software development kits (SDKs) for application development

With these, the Yocto project covers the needs of both system and application When the Yocto project is used as an integration environment for bootloaders kernel, and user space applications, we refer to it as system development.

The Yocto project makes a new release every six months. The latest release at the time of this writing is Yocto 3.3 “HARDKNOTT” 

We are using Yocto 3.0.4 “Zeus”

Read Yocto Reference manuals from the below Repo.

```sh
cd ~/KM_GITHUB
$ git clone https://github.com/kernelmasters/yocto.git
```

| Linux Build System | yocto Project Build System |
| ------ | ------ |
| make | bitbake |
| Makefile | recipe |

Beagle bone black configuration file mentioned here: 
    ~/poky-zeus-bbb/meta-yocto-bsp/conf/machine/beaglebone-yocto.conf

