/**
 * \file
 * \brief  Implementation module's main file
 */
#include <linux/module.h>

#include "kmma_sysfs.h"

static int __init kmma_init(void)
{
    int ret = kmma_register_sysfs(&THIS_MODULE->mkobj.kobj);

    if (!ret) {
        pr_alert("kmma: module initialized\n");
    }

    return ret;
}
module_init(kmma_init);

static void __exit kmma_exit(void)
{
    kmma_unregister_sysfs();
}
module_exit(kmma_exit);

MODULE_AUTHOR("André L. C. Moreira <alcm99@gmail.com>");
MODULE_LICENSE("GPL");
