/**
 * \brief  This file contains the implementation of hooks
 */
#include <linux/kprobes.h>
#include <linux/string.h>

#include "kermma_cmd_itf.h"
#include "kermma_hooks.h"
#include "kermma_macros.h"

/**
 * \brief  Post handler implementation for module loading
 * \param  probe Kretprobe instance
 * \param  regs Registers associated with the call
 * \return TODO
 */
static int load_module_post(struct kretprobe_instance *probe, struct pt_regs *regs)
{
    int ret = regs_return_value(regs);

    kermma_debug("%s called!\n", __func__);

    if (!ret) {
        kermma_log("ret value: %d\n", ret);
        // TODO: install memory hooks
    }

    probe->rp->handler = NULL;

    return 0;
}

/**
 * \brief  Pre handler implementation for module loading
 * \param  probe Kretprobe instance
 * \param  regs Registers associated with the call
 * \return TODO
 */
static int load_module_pre(struct kretprobe_instance *probe, struct pt_regs *regs)
{
    struct module *mod = NULL;

    kermma_debug("%s called!\n", __func__);

    mod = (struct module *)regs_get_kernel_argument(regs, 0);
    if (mod && !strcmp("foo", mod->name)) {
        kermma_log("target module: %s loaded\n", mod->name);

        /* the post handler is set only for the target module */
        probe->rp->handler = load_module_post;
    }

    return 0;
}

/**
 * \brief  Post handler implementation for module unloading
 * \param  probe Kretprobe instance
 * \param  regs Registers associated with the call
 * \return TODO
 */
static int unload_module_post(struct kretprobe_instance *probe, struct pt_regs *regs)
{
    kermma_debug("%s called!\n", __func__);

    // TODO: uninstall memory hooks

    probe->rp->handler = NULL;

    return 0;
}

/**
 * \brief  Pre handler implementation for module unloading
 * \param  probe Kretprobe instance
 * \param  regs Registers associated with the call
 * \return TODO
 */
static int unload_module_pre(struct kretprobe_instance *probe, struct pt_regs *regs)
{
    struct module *mod = NULL;

    kermma_debug("%s\n", __func__);

    mod = (struct module *)regs_get_kernel_argument(regs, 0);
    if (!strcmp("foo", mod->name)) {
        kermma_log("target module %s unloaded\n", mod->name);

        /* the post handler is set only for the target module */
        probe->rp->handler = unload_module_post;
    }

    return 0;
}

enum Hooks {
    LOAD_MODULE_HOOK,
    UNLOAD_MODULE_HOOK
};

static struct kretprobe hooks[] = {
    [LOAD_MODULE_HOOK] = {
        .entry_handler = load_module_pre,
        .handler = NULL,
        .kp = {
            .symbol_name = "do_init_module"
        }
    },
    [UNLOAD_MODULE_HOOK] = {
        .entry_handler = unload_module_pre,
        .handler = NULL,
        .kp = {
            .symbol_name = "free_module"
        }
    },
};

int register_module_hooks(const char *module)
{
    int ret =
        register_kretprobe(&hooks[LOAD_MODULE_HOOK]) |
        register_kretprobe(&hooks[UNLOAD_MODULE_HOOK]);

    kermma_log("registering hooks for module %s\n", module);

    return ret;
}

int unregister_module_hooks(const char *module)
{
    unregister_kretprobe(&hooks[LOAD_MODULE_HOOK]);
    unregister_kretprobe(&hooks[UNLOAD_MODULE_HOOK]);

    kermma_log("unregistering hooks for module %s\n", module);

    return 0;
}

void kermma_init_hook_events(void)
{
    add_cmd_handler(SCAN_MODULE_CMD, register_module_hooks);
    add_cmd_handler(STOP_SCANNING_CMD, unregister_module_hooks);
}

void kermma_clean_hook_events(void)
{
    del_cmd_handler(register_module_hooks);
    del_cmd_handler(unregister_module_hooks);
}
