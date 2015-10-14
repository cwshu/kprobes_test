Kprobe examples
---------------
usage
~~~~~
::

    # build
    make -C <kernel source dir> M=`pwd`
    # start
    insmod kprobe_sysopen.ko
    # end
    rmmod kprobe_sysopen
    # clean
    make clean -C <kernel source dir> M=`pwd`


