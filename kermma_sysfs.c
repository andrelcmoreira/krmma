/**
 * \file
 * \brief  Implementation of the sysfs interface of module
 */
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "kmma_hooks.h"
#include "kermma_sysfs.h"
#include "kermma_macros.h"

static struct kobject kermma_kobj;

/**
 * \brief  Write routine for sysfs interface
 * \param  kobj  Kobject related to operation
 * \param  attr  Attribute name
 * \param  buf   Buffer containing the data
 * \param  count Size of buffer
 * \return Number of written bytes
 */
static ssize_t write(struct kobject *kobj, struct attribute *attr, const char *buf, size_t count)
{
    if (!strcmp(attr->name, "scan_module")) {
        char mod_name[count];
        int ret = 0;

        memcpy(mod_name, buf, count - 1);
        mod_name[count-1] = '\0';

        ret = register_module_hooks(mod_name);

        switch (ret) {
        case -ENOMEM:
            kermma_alert("failed to allocate memory for the context\n");
            break;
        case -EINVAL:
            kermma_alert("bad module name\n");
            break;
        case -EBUSY:
            kermma_alert("already exist a scanning in progress\n");
            break;
        case -EAGAIN:
            kermma_alert("the target module ir already loaded, please unload it\n");
            break;
        }
    } else {
        unregister_module_hooks(buf);
    }

    return count;
}

static struct sysfs_ops fsops = {
    .store = write,
};

static struct attribute scan_module_attr = {
    .name = "scan_module",
    .mode = 0777,
};

static struct attribute stop_scanning_attr = {
    .name = "stop_scanning",
    .mode = 0777,
};

static struct attribute *attrs[] = {
    &scan_module_attr,
    &stop_scanning_attr,
    NULL,
};

int __init kermma_register_sysfs(struct kobject *root)
{
    struct kobj_type *type = kzalloc(sizeof(struct kobj_type), GFP_KERNEL);

    if (!type) {
        kermma_debug("failed to allocate memory for kobj_type\n");
        return -ENOMEM;
    }

    type->sysfs_ops = &fsops;
    type->default_attrs = attrs;

    kobject_init(&kermma_kobj, type);
    kobject_add(&kermma_kobj, root, "config");

    return 0;
}

void kermma_unregister_sysfs(void)
{
    unregister_module_hooks("");
    kobject_put(&kermma_kobj);
}
