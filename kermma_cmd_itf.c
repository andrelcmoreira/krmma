/**
 * \file
 * \brief  Implementation of the sysfs interface of module
 */
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/string.h>

#include "kermma_cmd_itf.h"
#include "kermma_macros.h"

static const char *const sysfs_cmds[] = {
    [SCAN_MODULE_CMD] = "scan_module",
    [STOP_SCANNING_CMD] = "stop_scanning"
};

struct kermma_cmd_handler_t {
    char *cmd_name;
    kermma_callback_t cb;
    struct list_head list;
};

static struct kermma_cmd_handler_t *handlers = NULL;
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
    struct kermma_cmd_handler_t *curr = NULL;

    list_for_each_entry(curr, &handlers->list, list) {
        if (!strcmp(curr->cmd_name, attr->name)) {
            char param[count];
            int ret = 0;

            /* removing '\n' from parameter */
            memcpy(param, buf, count - 1);
            param[count - 1] = '\0';

            ret = curr->cb(param);
            if (ret) {
                kermma_log("fail to handle the command %s\n", attr->name);
            }

            break;
        }
    }

    return count;
}

static struct sysfs_ops fsops = {
    .store = write,
};

static struct attribute scan_module_attr = {
    .name = "scan_module",//sysfs_cmds[SCAN_MODULE_CMD],
    .mode = 0777,
};

static struct attribute stop_scanning_attr = {
    .name = "stop_scanning",//sysfs_cmds[STOP_SCANNING_CMD],
    .mode = 0777,
};

static struct attribute *attrs[] = {
    &scan_module_attr,
    &stop_scanning_attr,
    NULL,
};

int __init kermma_register_cmd_itf(struct kobject *root)
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

    handlers = kzalloc(
        sizeof(struct kermma_cmd_handler_t),
        GFP_KERNEL
    );

    if (!handlers) {
        kermma_debug("failed to allocate memory for cmd handlers\n");
        return -ENOMEM;
    }

    INIT_LIST_HEAD(&handlers->list);

    return 0;
}

void kermma_unregister_cmd_itf(void)
{
    struct kermma_cmd_handler_t *curr = NULL, *tmp = NULL;

    list_for_each_entry_safe(curr, tmp, &handlers->list, list) {
        list_del(&curr->list);
        kfree(curr->cmd_name);
        kfree(curr);
    }

    kobject_put(&kermma_kobj);
    kfree(handlers);
}

void kermma_add_cmd_handler(enum kermma_command cmd, kermma_callback_t cb)
{
    struct kermma_cmd_handler_t *handler = NULL;

    handler = kmalloc(
        sizeof(struct kermma_cmd_handler_t),
        GFP_KERNEL
    );

    if (handler) {
        handler->cmd_name = kmalloc(
            strlen(sysfs_cmds[cmd]),
            GFP_KERNEL
        );

        if (handler->cmd_name) {
            memcpy(handler->cmd_name, sysfs_cmds[cmd], strlen(sysfs_cmds[cmd]));
            handler->cb = cb;

            list_add_tail(&handler->list, &handlers->list);
        }

        kermma_debug("adding handler for command %s\n", sysfs_cmds[cmd]);
    }
}

void kermma_del_cmd_handler(kermma_callback_t cb)
{
    struct kermma_cmd_handler_t *curr = NULL, *tmp = NULL;

    list_for_each_entry_safe(curr, tmp, &handlers->list, list) {
        if (curr->cb == cb) {
            kermma_debug("removing handler for command %s\n", curr->cmd_name);

            list_del(&curr->list);
            kfree(curr->cmd_name);
            kfree(curr);
        }
    }
}
