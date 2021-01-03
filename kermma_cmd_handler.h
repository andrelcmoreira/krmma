#ifndef KERMMA_CMD_HANDLER_H_
#define KERMMA_CMD_HANDLER_H_

enum kermma_command {
    SCAN_MODULE_CMD,
    STOP_SCANNING_CMD
};

typedef int (*kermma_callback_t)(const void *);

//kermma_callback_t find_cmd_handler(const char *cmd);

void add_cmd_handler(enum kermma_command cmd, kermma_callback_t cb);
void del_cmd_handler(kermma_callback_t cb);

#endif  // KERMMA_CMD_HANDLER_H_
