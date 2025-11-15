# AKL - Ant C++ Kernel Library

### Style code

We do not use references in our code!
Because BTF sanitizer can not pass our code with refs
If you want to use reference in public methods, use pointers!

You can do this in kernel module C++:

```cpp
akl::some_struct<int> atom1 = akl::some_struct<int>{.value_ = 3};

auto atom2 = akl::some_class<int>{14};

akl::some_class<int> atom3;
akl::some_class<int> atom4{2};
akl::some_class<int> atom5 = {3};

auto atom6 = atom5;
```

! But not this:

```cpp
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



