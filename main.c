#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/wait.h>


int my_function(void * argc)
{
    return 0;
}

static int __init add_wait_queue_init(void)
{
    wait_queue_head_t my_queue;
    int i = 20;
    printk(KERN_EMERG "%s %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, current->pid, current->__state);
    init_waitqueue_head(&my_queue);
    DECLARE_WAITQUEUE(wait, current);
    __set_current_state(TASK_INTERRUPTIBLE);
    while (i > 0) {
        printk(KERN_EMERG "%s %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, current->pid, current->__state);
        if (i == 10) {
            __set_current_state(TASK_RUNNING);
        }
        i--;
    }
    schedule();
    printk(KERN_EMERG "%s %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, current->pid, current->__state);
    return 0;
}

static void __exit add_wait_queue_exit(void)
{
    printk(KERN_EMERG "Goodbye add_wait_queue\n");
}

module_init(add_wait_queue_init);
module_exit(add_wait_queue_exit);
MODULE_LICENSE("GPL");