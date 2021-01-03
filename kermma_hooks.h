/**
 * \brief  This file contains all definitions of hooks
 */
#ifndef KMMA_HOOKS_H_
#define KMMA_HOOKS_H_

/**
 * \brief  Register the module hooks for a specific module
 * \param  module Module's name
 */
int register_module_hooks(const char *module);

/**
 * \brief  Unregister the module hooks
 * \param  module Module's name
 */
int unregister_module_hooks(const char *module);

void kermma_init_hook_events(void);

void kermma_clean_hook_events(void);

#endif  // KMMA_HOOKS_H_
