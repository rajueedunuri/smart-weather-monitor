#include<linux/module.h>
#include<linux/version.h>
#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/kprobes.h>
#include<linux/sched.h>
#include<linux/thread_info.h>
#include<linux/kallsyms.h>

static unsigned int counter = 0;

int Pre_Handler(struct kprobe *p, struct pt_regs *regs){
	printk("Pre_Handler: counter=%u tpid=%d\n",counter++,current->tgid);
	return 0;
}

void Post_Handler(struct kprobe *p, struct pt_regs *regs, unsigned long flags){
	printk("Post_Handler: counter=%u\n",counter++);
}

static struct kprobe kp;

int myinit(void)
{
	printk("module inserted\n ");
	printk("current process ID:%d\n",current->pid);
	kp.pre_handler = Pre_Handler;
	printk("current Thread ID:%d\n",current->tgid);
	kp.post_handler = Post_Handler;
	kp.addr = (kprobe_opcode_t*) kallsyms_lookup_name("_set_gpio_direction");
	//kp.addr = (kprobe_opcode_t *)0xc0546f10;
	register_kprobe(&kp);
	return 0;
}

void myexit(void)
{
unregister_kprobe(&kp);
printk("module removed\n ");
}

module_init(myinit);
module_exit(myexit);
MODULE_AUTHOR("test");
MODULE_DESCRIPTION("KPROBE MODULE");
MODULE_LICENSE("GPL");

