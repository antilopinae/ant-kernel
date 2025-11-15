# AKL - Ant C++ Kernel Library

### Style code in C++ in linux kernel mode while you are writing kernel module with this library

#### You can Not use references

We do not use references in our code!
Because BPF sanitizer can not pass our code with refs
If you want to use reference in public methods, use pointers!

#### You can Not use templates in the usual sense

You can not do this in kernel module C++:

```cpp
// It was failed by verifier while loading kernel module via `insmod`
akl::some_struct<int> atom1 = akl::some_struct<int>{.value_ = 3};

// It was failed by verifier while loading kernel module via `insmod`
auto atom2 = akl::some_class<int>{14};

// It was failed by verifier while loading kernel module via `insmod`
akl::some_class<int> atom3;
akl::some_class<int> atom4{2};
akl::some_class<int> atom5 = {3};

// It was failed by verifier while loading kernel module via `insmod`
auto atom6 = atom5;
```
(But you can use all of these types to construct a class or struct without template substitution)


Because BPF verifier will say something like this about `<` and `>``:
```
[11142.874462] BPF: [24] STRUCT atomic_impl<int, true>
[11142.874467] BPF: size=4 vlen=1
[11142.874468] BPF:
[11142.874469] BPF: Invalid name
[11142.874469] BPF:
[11142.874470] failed to validate module [cpp_kernel] BTF: -22
[11205.309407] BPF: [18] STRUCT atomic_impl<int, true>
[11205.309412] BPF: size=4 vlen=1
[11205.309412] BPF:
[11205.309413] BPF: Invalid name
[11205.309414] BPF:
[11205.309415] failed to validate module [cpp_kernel] BTF: -22
```

```cpp
// It was okay
akl::some_class_int_ atom6 = {7};
```

#### But You can use templates

I write simple python script in `ant-cmake/scripts/extract_templates_from_ko.py`
which is used for rewrite symbols `<` and `>` with `_` in ELF part.

So, I also add it to my cmake function `add_cpp_kernel_module` to do it in compile time.

With it, my BPF verifier shut up and now I can use templates in my code with some limitations:

You need to specify every template class in cmake variable:

As example in akl:

```cmake
set(AKL_TEMPLATE_NAMES
        "atomic"
        "atomic_impl"
        CACHE INTERNAL "Ant kernel lib template names in cpp code" FORCE
)
```

and then pass them to my function:

```cmake
# Func to add target and then build C++ module
add_cpp_kernel_module(
        # target 'cpp_kernel' to build kernel module
        MODULE_NAME cpp_kernel_module

        # dir where module src are
        MODULE_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}

        # list with src of module (.c and .cpp)
        MODULE_SRC ${CPP_KERNEL_MODULE_SRC}

        # list with include directories of module
        MODULE_INCLUDE_DIRS
        include/
        some_other_dirs/
        ${AKL_INCLUDE_DIRS}

        # list with names classes which used template substitution
        MODULE_TEMPLATE_NAMES
        ${AKL_TEMPLATE_NAMES}
        my_new_template_class_name
        unique_ptr
        shared_ptr
        # and others
)
```

#### You can Not use parentheses in constructors

```cpp
// It was failed to compile in linux kernel mode
akl::some_class_int not_atom(2);
```

Also you can do:

```cpp

```

You can do this:

```cpp

```

You can do this:

```cpp

```



