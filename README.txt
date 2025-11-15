# AKL - Ant C++ Kernel Library

### Style code in C++ in linux kernel mode while you are writing kernel module with this library

#### Not use references

We do not use references in our code!
Because BTF sanitizer can not pass our code with refs
If you want to use reference in public methods, use pointers!

#### Not use templates in the usual sense

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

Because BTF verifier will say something like this about `<` and `>``:
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

But you can use all of these types to construct a class or struct without template substitution.

#### Not use parentheses in constructors

```cpp
// It was failed to compile in linux kernel mode
akl::some_class<int> not_atom(2);
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



