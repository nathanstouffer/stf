# architecture

## priorities

1. correctness
2. maintainability
3. performance

## library

`stf` is a header-only template math library built primarily for graphics.
The library is split into a couple namespaces.

| namespace | description |
|-----------|-------------|
| `math` | contains basic math structures and operations (eg `vector`, `matrix`, spherical coordinates) |
| `geom` | contains geometric primitives (eg `segment`, `polyline`, and `polygon`) |
| `gfx` | contains graphics-related structures (eg `rgba`) |
| `cam` | contains camera-related structures (eg `camera` and `frustum`) |
| `spatial` | contains structures that sort data spatially (eg `interval_tree`) |
| `alg` | contains algorithms that operate on the `stf` structures (eg `intersect`) |

Because the entire library is templated, you are free to create objects with the number type of your choice.
As a convenience, `stf` takes advantage of `using` statements in [stf/stf.hpp](../code/src/stf/include/interface/stf/stf.hpp) to provide less verbose access to common types.
There is a slight awkwardness in that it twists the namespace `stf`, but the brevity is nice.

```C++
stff::vec2 point(0, 0);     // floats
stfd::vec2 point(0, 0);     // doubles
stfi::vec2 point(0, 0);     // integers
stfu::vec2 point(0, 0);     // unsigned integers
```

## building

`stf` uses [cmake](https://cmake.org/) to generate a build system of your choice.
GHA builds `stf` with a number of compilers on various operating systems.

## tests

Testing architecture falls into two categories: scaffolding and data.
Scaffolding defines what information is required for a test and the code to verify its correctness.
This structure allows a lot of consolidation when verifying a test.
The data for a test is defined in another file and calls the `verify` method for a particular test.

For a testing framework, `stf` uses [gtest](https://github.com/google/googletest.git).
Code coverage is reported, but the numbers are misleading because uninstantiated template code (which is certainly untested) is not incorporated in coverage computations.