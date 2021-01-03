#include "kermma_cmd_handler.h"

#include <linux/list.h>
#include <stddef.h>

//struct kermma_cmd_handler_t {
//    char *cmd_name;
//    kermma_callback_t cb;
//    struct list_head list;
//};
//
//static kermma_cmd_handler_t *handlers = NULL; // TODO: INIT_LIST_HEAD(&(handlers->list));
//
//kermma_callback_t find_cmd_handler(const char *cmd)
//{
//    struct kermma_cmd_handler_t *curr = NULL;
//
//    list_for_each_entry(curr, &handlers->list, list) {
//        if (!strcmp(curr->cmd_name, cmd)) {
//            kermma_debug("handler found for command %s\n", cmd);
//            return curr->cb;
//        }
//    }
//
//    return NULL;
//}

void kermma_add_cmd_handler(const char *cmd, kermma_callback_t cb)
{
    struct kermma_cmd_handler_t *handler = NULL;

    handler = kmalloc(
        GFP_KERNEL,
        sizeof(struct kermma_cmd_handler_t)
    );

    if (handler) {
        handler->cmd_name = kmalloc(GFP_KERNEL, strlen(cmd));

        if (handler->cmd_name) {
            memcpy(handler->cmd_name, cmd, strlen(cmd));
            handler->cb = handler;

            list_add_tail(&handler->list, &handlers->list);
        }
    }

    kermma_debug("adding handler for command %s\n", cmd);
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
