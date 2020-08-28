/**
 * \file
 * \brief  Definition of the sysfs interface of module
 */
#ifndef KERMMA_SYSFS_H_
#define KERMMA_SYSFS_H_

struct kobject;

/**
 * \brief  Register the sysfs interface of module
 * \param  Module's root kobject
 * \return 0 in success; otherwise -ENOMEM
 */
int __init kermma_register_sysfs(struct kobject *self);

/**
 * \brief  Unregister the sysfs interface
 */
void kermma_unregister_sysfs(void);

#endif  // KERMMA_SYSFS_H_
