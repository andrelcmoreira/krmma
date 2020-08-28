/**
 * \file
 * \brief  Definition of sysfs interface of module
 */
#ifndef KMMA_SYSFS_H_
#define KMMA_SYSFS_H_

struct kobject;
struct attribute;

/**
 * \brief  Register sysfs interface
 * \param  Module's root kobject
 * \return 0 in success; otherwise -ENOMEM
 */
int __init kmma_register_sysfs(struct kobject *self);

/**
 * \brief  Unregister sysfs interface
 */
void kmma_unregister_sysfs(void);

#endif  // KMMA_SYSFS_H_
