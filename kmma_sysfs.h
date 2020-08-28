/**
 * \file
 * \brief  Definition of the sysfs interface of module
 */
#ifndef KMMA_SYSFS_H_
#define KMMA_SYSFS_H_

struct kobject;
struct attribute;

/**
 * \brief  Register the sysfs interface of module
 * \param  Module's root kobject
 * \return 0 in success; otherwise -ENOMEM
 */
int __init kmma_register_sysfs(struct kobject *self);

/**
 * \brief  Unregister the sysfs interface
 */
void kmma_unregister_sysfs(void);

#endif  // KMMA_SYSFS_H_
