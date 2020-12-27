/**
 * \file
 * \brief  Implementation module's main file
 */
#include <linux/module.h>

#include "kermma_macros.h"
#include "kermma_sysfs.h"

static int __init kermma_init(void)
{
    int ret = kermma_register_sysfs(&THIS_MODULE->mkobj.kobj);

    if (!ret) {
        kermma_log("module initialized!\n");
    }

    return ret;
}
module_init(kermma_init);

static void __exit kermma_exit(void)
{
    kermma_unregister_sysfs();
}
module_exit(kermma_exit);

MODULE_AUTHOR("André L. C. Moreira <alcm99@gmail.com>");
MODULE_LICENSE("GPL");
