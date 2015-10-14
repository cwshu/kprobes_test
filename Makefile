# builds the kprobes example kernel modules;
# then to use one (as root):  insmod <module_name.ko>

obj-m += \
    kprobe_example2.o kprobe_pgfault.o kprobe_sysopen.o
