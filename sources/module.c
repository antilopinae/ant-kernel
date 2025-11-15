/*
* Linux kernel module
*/

#include <linux/kernel.h>
#include <linux/module.h>

#include "akl/logger.h"
#include "cpp_module.h"

static int __init module_load(void)
{
    kern_log("Loading C++ kernel module\n");

    init_cpp_subsystem_example();

    // call_constructors();

    pr_info("Loaded the kernel module.\n");
    return 0;
}

static void __exit module_unload(void)
{
    kern_log("Unloading C++ kernel module\n");

    release_cpp_subsystem_example();

    // call_destructors();
    pr_info("Unloaded the kernel module.\n");
}

module_init(module_load);
module_exit(module_unload);

MODULE_DESCRIPTION ("Linux kernel module with C++");
MODULE_VERSION ("0.1");
MODULE_AUTHOR ("Oleg Kutkov");
MODULE_LICENSE ("GPL");