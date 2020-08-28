/**
 * \file
 * \brief  Implementation of sysfs interface of module
 */
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>

// TODO: #include "kmma_hooks.h"
#include "kmma_sysfs.h"

static struct kobject kmma_kobj;

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
    if (!strcmp(attr->name, "target_module")) {
        struct module *mod = find_module(buf);

        // TODO: install module hooks

        if (mod) {
            pr_alert("kmma: installing memory hooks...\n");
            // TODO: install memory hooks
        }
    }

    return count;
}

static struct sysfs_ops fsops = {
    .store = write,
};

static struct attribute target_module_attr = {
    .name = "target_module",
    .mode = 0777,
};

static struct attribute *attrs[] = {
    &target_module_attr,
    NULL,
};

int __init kmma_register_sysfs(struct kobject *root)
{
    struct kobj_type *type = kzalloc(sizeof(struct kobj_type), GFP_KERNEL);

    if (!type) {
        return -ENOMEM;
    }

    type->sysfs_ops = &fsops;
    type->default_attrs = attrs;

    kobject_init(&kmma_kobj, type);
    kobject_add(&kmma_kobj, root, "cfg");

    return 0;
}

void kmma_unregister_sysfs(void)
{
    kobject_put(&kmma_kobj);
}