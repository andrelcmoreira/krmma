/**
 * \file
 * \brief  Implementation module's main file
 */
#include <linux/module.h>

#include "kermma_hooks.h"
#include "kermma_macros.h"
#include "kermma_cmd_itf.h"

static int __init kermma_init(void)
{
    int ret = kermma_register_cmd_itf(&THIS_MODULE->mkobj.kobj);

    if (!ret) {
        kermma_init_hook_events();
        kermma_log("module initialized!\n");
    }

    return ret;
}
module_init(kermma_init);

static void __exit kermma_exit(void)
{
    kermma_unregister_cmd_itf();
    kermma_clean_hook_events();
}
module_exit(kermma_exit);

MODULE_AUTHOR("André L. C. Moreira <alcm99@gmail.com>");
MODULE_LICENSE("GPL");
