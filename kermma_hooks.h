/**
 * \brief  This file contains all definitions of hooks
 */
#ifndef KMMA_HOOKS_H_
#define KMMA_HOOKS_H_

/**
 * \brief  Register the module hooks for a specific module
 * \param  module Module's name
 */
void register_module_hooks(const char *module);

/**
 * \brief  Unregister the module hooks
 * \param  module Module's name
 */
void unregister_module_hooks(const char *module);

/**
 * \brief  Verify if already exist module hooks for a given module
 * \param  module Module's name
 */
int has_module_hooks(const char *module);

#endif  // KMMA_HOOKS_H_
