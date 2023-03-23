#include <linux/module.h>
#include <linux/sched.h>
#include <linux/list.h>
#include <linux/kthread.h>
#include <linux/wait.h>
#include <linux/sched/signal.h>


int my_function(void * argc)
{
    return 0;
}

static int __init add_wait_queue_init(void)
{
    wait_queue_head_t my_queue;
    int i = 2000;
    schedule();
    schedule();
    printk(KERN_EMERG "%s %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, current->pid, current->__state);
    init_waitqueue_head(&my_queue);
    DECLARE_WAITQUEUE(wait, current);
    add_wait_queue(&my_queue, &wait);
    // schedule();
    // __set_current_state(TASK_UNINTERRUPTIBLE);
    // while(1) {
    //     //printk(KERN_EMERG "%s %d i %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, i, current->pid, current->__state);
    //     if (signal_pending(current)){
    //         break;
    //     }
    // }
    // __set_current_state(TASK_INTERRUPTIBLE);
    while (i > 0) {
        printk(KERN_EMERG "%s %d i %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, i, current->pid, current->__state);
        if (i == 10) {
            __set_current_state(TASK_INTERRUPTIBLE);
            printk(KERN_EMERG "%s %d i %d current pid %d state 0x%04x\n", __FUNCTION__, __LINE__, i, current->pid, current->__state);
        }
        schedule();
        // if (i == 100) {
        //     schedule();
        // }
        i--;
    }
    // schedule();
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