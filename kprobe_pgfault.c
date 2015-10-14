#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kprobes.h>

/* For each probe you need to allocate a kprobe structure */
static struct kprobe kp = {
    .symbol_name    = "handle_mm_fault",
    // .addr           =  (kprobe_opcode_t *)0xffffffff8105aa80,
};

/* kprobe pre_handler: called just before the probed instruction is executed */
static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    // printk(KERN_INFO "pre_handler: p->addr = 0x%p, ip = %lx,"
    //         " flags = 0x%lx\n",
    //     p->addr, regs->ip, regs->flags);

    printk(KERN_INFO "pre_handler: pid: %d, jiffies: %ld,"
            " p->addr = 0x%p, ip = %lx\n",
        current->tgid, jiffies, p->addr, regs->ip);

    dump_stack();
    /* A dump_stack() here will give a stack backtrace */
    return 0;
}

/*
 * fault_handler: this is called if an exception is generated for any
 * instruction within the pre- or post-handler, or when Kprobes
 * single-steps the probed instruction.
 */

static int __init kprobe_init(void)
{
    int ret;
    kp.pre_handler = handler_pre;
    // kp.post_handler = handler_post;
    // kp.fault_handler = handler_fault;

    ret = register_kprobe(&kp);
    if (ret < 0) {
        printk(KERN_INFO "register_kprobe failed, returned %d\n", ret);
        return ret;
    }
    printk(KERN_INFO "Planted kprobe at %p\n", kp.addr);
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
