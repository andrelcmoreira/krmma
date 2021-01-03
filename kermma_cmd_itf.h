/**
 * \file
 * \brief  Definition of the sysfs interface of module
 */
#ifndef KERMMA_CMD_ITF_H_
#define KERMMA_CMD_ITF_H_

struct kobject;

typedef int (*kermma_callback_t)(const char *);

enum kermma_command {
    SCAN_MODULE_CMD,
    STOP_SCANNING_CMD
};

/**
 * \brief  Register the command interface of module
 * \param  Module's root kobject
 * \return 0 in success; otherwise -ENOMEM
 */
int __init kermma_register_cmd_itf(struct kobject *self);

/**
 * \brief  Unregister the command interface
 */
void kermma_unregister_cmd_itf(void);

void add_cmd_handler(enum kermma_command cmd, kermma_callback_t cb);
void del_cmd_handler(kermma_callback_t cb);

#endif  // KERMMA_CMD_ITF_H_
