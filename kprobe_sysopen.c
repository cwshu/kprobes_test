#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>
#include <asm/uaccess.h>

#define __KPROBE_EXAMPLE__
// #define __JPROBE_EXAMPLE__

/* For each probe you need to allocate a kprobe structure */
static struct kprobe kp;
static struct jprobe jp;

/* kprobe pre_handler: called just before the probed instruction is executed */
static int kp_sysopen_handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    if( strcmp(current->comm, "ls") == 0 ){
        const char __user *filename = (void *)regs->di;
        int flags = regs->si;
        umode_t mode = regs->dx;

        /*
        printk(KERN_INFO "pre_handler: pid: %d, comm: %s, jiffies: %ld,"
                " p->addr = 0x%p, ip = %lx\n",
            current->tgid, current->comm, jiffies, p->addr, regs->ip); */
        
        printk(KERN_INFO "pid: %d: open(\"%s\", ... )\n", current->tgid, filename);
        // dump_stack();
        /* A dump_stack() here will give a stack backtrace */
    }
    return 0;
}

static int jp_sysopen_handler(const char __user *filename, int flags, umode_t mode)
{
    if( strcmp(current->comm, "ls") == 0 ){
        printk(KERN_INFO "pid: %d: open(\"%s\", ... )\n", current->tgid, filename);
    }

    jprobe_return();
    return 0;
}

static int __init kprobe_init(void)
{
    int ret;
    /* kprobe */
#ifdef __KPROBE_EXAMPLE__
    kp.symbol_name = "sys_open";
    kp.pre_handler = kp_sysopen_handler_pre;
    // kp.post_handler = handler_post;
    // kp.fault_handler = handler_fault;

    ret = register_kprobe(&kp);
    if (ret < 0) {
        printk(KERN_INFO "register_kprobe failed, returned %d\n", ret);
        return ret;
    }
    printk(KERN_INFO "Planted kprobe at %p\n", kp.addr);
#endif 

#ifndef __KPROBE_EXAMPLE__
#ifdef __JPROBE_EXAMPLE__
    /* jprobe */
    /*
    jp.kp.symbol_name = "sys_open";
    jp.entry = jp_sysopen_handler;

    ret = register_jprobe(&jp);
    if (ret < 0) {
        printk(KERN_INFO "register_jprobe failed, returned %d\n", ret);
        return ret;
    }
    printk(KERN_INFO "Planted jprobe at %p\n", jp.kp.addr);
    */
#endif
#endif

    return 0;
}

static void __exit kprobe_exit(void)
{
    unregister_kprobe(&kp);
    printk(KERN_INFO "kprobe at %p unregistered\n", kp.addr);
}

module_init(kprobe_init)
module_exit(kprobe_exit)
MODULE_LICENSE("GPL");
