# stf

[![c++-version](https://img.shields.io/badge/C++-17-gray.svg?style=flat&logo=c%2B%2B&logoColor=white&labelColor=1575F9)](https://en.cppreference.com/w/cpp/17)
![build](https://github.com/nathanstouffer/stf/actions/workflows/build.yml/badge.svg)
[![codecov](https://codecov.io/gh/nathanstouffer/stf/graph/badge.svg?token=WLB5Z8XTYE)](https://codecov.io/gh/nathanstouffer/stf)

`stf` is a math library built primarily for graphics.

## Priorities

1. correctness
2. maintainability
3. performance

## Note

Unfortunately, the code coverage is a lie because the entire library is templated and an uninstantiated template (class or function) is not incoporated into coverage computations.
Any uninstantiated code is necessarily uncovered so the coverage is over-estimated.

## Attribution

Many thanks to the open-source software that enables this project.

- [cmake](https://cmake.org/)
- [googletest](https://github.com/google/googletest.git)
- [doxygen](https://www.doxygen.nl/)
- [doxygen-awesome-css](https://github.com/jothepro/doxygen-awesome-css)
