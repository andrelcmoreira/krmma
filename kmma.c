#include <linux/module.h>
#include <linux/string.h>

static char *target_module = "";
module_param(target_module, charp, 0000);

static int target_is_loaded(void)
{
    struct list_head *cursor = NULL;

    list_for_each(cursor, &THIS_MODULE->list) {
        struct module *mod = container_of(cursor, struct module, list);

        if (!strcmp(target_module, mod->name))
            return 1;
    }

    return 0;
}

static int __init kmma_init(void)
{
    if (target_is_loaded()) {
        pr_alert("plese unload the target module '%s' in order to continue!\n", target_module);
        return -EAGAIN;
    }

    // TODO: setup sysfs
    // TODO: install hooks
    // TODO: load target module

    return 0;
}
module_init(kmma_init);

static void __exit kmma_exit(void)
{
}
module_exit(kmma_exit);

MODULE_AUTHOR("André L. C. Moreira <alcm99@gmail.com>");
MODULE_LICENSE("GPL");
