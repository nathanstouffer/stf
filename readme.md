# stf

[![c++-version](https://img.shields.io/badge/C++-17-gray.svg?style=flat&logo=c%2B%2B&logoColor=white&labelColor=1575F9)](https://en.cppreference.com/w/cpp/17)
![build](https://github.com/nathanstouffer/stf/actions/workflows/build.yml/badge.svg)
[![codecov](https://codecov.io/gh/nathanstouffer/stf/graph/badge.svg?token=WLB5Z8XTYE)](https://codecov.io/gh/nathanstouffer/stf)


`stf` is a templated math library built primarily for graphics.

## Notes

* At this time, code coverage is not completely accurate because any uninstantiated template (class or function) is not incorporated into coverage computations.
Any uninstantiated code is necessarily uncovered.
As the entire library is templated, this means coverage is possibly **vastly** over-estimated.