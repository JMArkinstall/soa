# soa
Structs of Arrays implementation in C++.

To build the example:
```
cd build; cmake .. && make
```

There are two ways of storing a block of records in memory. The most common in C++
is the AoS (Array of Structs) approach, whereby one defines a struct which serves as
a record, and then a collection of such structs can be created.

For example:

```
struct example_struct{
    int a, b;
    double c;
}
template<typename<class...> class container_t;
struct example_struct_aos{
    container_t<example_struct> collection;
}
```

This suffices for many use-cases of collections - particularly when one wishes to
access multiple struct variables on each iteration. As all of the struct values are
collected from memory at once, this storage method is effective.
```
    for(example_struct& s : collection){
        c += a - b;
    }
```

The other storage method is an SoA (Struct of Arrays). Rather than storing members
sequentially in memory, the values of each member are stored sequentially. In other words,
the result is effectively:
```
template<template<class...> class container_t>
struct example_struct_soa{
    container_t<int> a, b;
    container_t<double> c;
}
```

This is beneficial when members are rarely used at the same time:
```
    int previous_c = 1.;
    for(double& c : collection.c){
        c = (c + previous_c) / 2;
        previous_c = c;
    }
```

Until reflection hits the C++ standard, there is no completely effortless way of creating
an SoA container from a struct, and there are a variety of approaches used to mitigate this.
My implementation requires the struct to extend an soa::converable object (which merely defines some types),
passing the required element types through template parameters. It also requires the struct to
provide a cast to a tuple, and to provide a construction from a tuple. A future development
may be to encompass such functionality in a helper struct.

When the struct has the above, it can be used as a template argument to an SoA, along with
a container type. The SoA can then be iterated efficiently by column, or slower by a (const) struct.
The SoA achieves this by storing containers in a tuple.

The compiled code is small (~ the same size as the equivalent code using AoS)
and outperforms AoS implementations for column-based access. Below is a chart from quick-bench.com, 
which demonstrates the performance gains from using the SoA approach on a 12-element struct (two ints, 10 longs),
iterating only through a single column using this library. The performance gains are noticable:
modifying every value in a single column has a 13.8% performance boost vs looping through a std::array of 20000 structs.

![Benchmark: this implementation vs a typical AoS implementation](https://raw.githubusercontent.com/JMArkinstall/soa/master/stats/performance_vs_aos.png)


This started as an example of what can currently be done during a [discussion](https://groups.google.com/a/isocpp.org/forum/?utm_medium=email&utm_source=footer#!msg/std-proposals/nmpy2WYWkWg/-WguCIUgDQAJ)
on the C++ proposals group. I wasn't aware of other implementations at the time, but I'm reasonably proud of
this approach, particularly in how effectively it gets optimised under -O1.

See the examples directory for a quick-and-easy demonstration.
