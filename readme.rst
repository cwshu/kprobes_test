Kprobe examples
---------------
Warning: This project may crash your system (kernel panic).

It's a experimental repo for testing kprobe feature in linux kernel.
Because the author is a newbie in kernel development, please be careful for code.

prepare
~~~~~~~
1. check kernel support of kprobe, loadable kernel module

   - CONFIG_KPROBES=y, CONFIG_MODULES=y, CONFIG_MODULE_UNLOAD=y
   ::

     # examples for viewing config
     # archlinux, or other distro with config in procfs
     zcat /proc/config.gz | grep CONFIG_KPROBES
     # ubuntu
     cat /boot/config-`uname -r` | grep CONFIG_KPROBES

2. install kernel headers, use your system's package management::

   # examples
   # linux 4.1.x in manjaro
   pacman -S core/linux41-headers # headers in linux 4.1.x
   # linux 3.16.0 in ubuntu
   apt-get install linux-headers-3.16.0-30

usage
~~~~~
::

    # we can use /lib/modules/`uname -r`/build to replace <kernel source dir> in building external kernel module.

    # build
    make -C <kernel source dir> M=`pwd`
    # start
    insmod kprobe_sysopen.ko
    # end
    rmmod kprobe_sysopen
    # clean
    make clean -C <kernel source dir> M=`pwd`

use our own kernel source [not finish]
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. download kernel source
2. use current config file::

   cd <kernel source dir>
   zcat /proc/config.gz > .config # use current config, depend on linux distro
   make oldconfig # check config mistake, more to read `make help` in linux kernel dir
   make modules_prepare # make prepare script, prepare for build external module

3. Module.symvers?

ref: http://lxr.free-electrons.com/source/Documentation/kbuild/modules.txt
