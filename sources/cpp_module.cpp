#ifdef __KERNEL_MODULE__
#include <linux/kernel.h>
#include <linux/module.h>

/* Also needed to define NULL as simple 0. It's Ok by standard. */
#define NULL 0
#else
#include <cstddef>

#endif

#include "akl/atomic.hpp"
#include "akl/logger.h"
#include "akl/sync.h"
#include "cpp_module.h"

class foo {
public:
    foo()
        : a(0) {
        akl_kern_log("C++ class constructor\n");
    }

    ~foo() {
        akl_kern_log("C++ class destructor\n");
    }

    /* "Normal" virtual function */
    // virtual void set_data(int data) {
    //     kern_log("Don't call me!\n");
    // };

    /* Pure virtual function */
    // virtual int get_data() =0;

protected:
    int a;
};

/* Class bar is inheritor of the class foo
 * Overloading implementation of the class methods
 */
class bar : public foo {
public:
    /* Virtual destructor is required */
    ~bar() {}

    void set_data(int data) {
        akl_kern_log(">> set_data %d\n", data);
        a = data;
    }

    int get_data() {
        return a;
    }
};

static bar* bar_instance = NULL;

static int v = 10;

/* This functions can be called from the C code */
void init_cpp_subsystem_example(void) {
    akl_kern_log("Init C++ subsystem\n");

    akl_kern_log("akl CAS test start\n");

    bool ok = akl_sync_bool_compare_and_swap(&v, 10, 20);
    akl_kern_log("CAS returned: %d\n", ok);
    akl_kern_log("New value: %d\n", v);

    ok = akl_sync_bool_compare_and_swap(&v, 10, 30);
    akl_kern_log("CAS returned: %d\n", ok);
    akl_kern_log("Value after failed CAS: %d\n", v);

    int a = 3;

    akl::atomic_int_ atom = akl::atomic_int_{12};

    atom.exchange(1);
    akl_kern_log("Test atom 1: %d\n", static_cast<int>(atom.value));

    atom.dec();
    atom.dec_ret_last();
    atom.inc();
    atom.inc_ret_last();
    atom.operator++();
    atom.operator--();
    atom.operator+=(5);
    atom.operator-=(5);

    akl_kern_log("Test atom 1: %d\n", static_cast<int>(atom.value));

    bar_instance = new bar;

    if (!bar_instance) {
        akl_kern_log("Failed to allocate bar class\n");
        return;
    }

    bar_instance->set_data(42);

    akl_kern_log("Getting data from bar: %d\n", bar_instance->get_data());
}

void release_cpp_subsystem_example(void) {
    akl_kern_log("Release C++ subsystem\n");

    if (bar_instance) {
        delete bar_instance;
    }
}
