# LibDataScienceC++

##### An intuitive and highly usable API backend for data science and data design with C/C++

###### v0.1.4-pre

This library aims to be simple, but highly usable backend this provides an front-end to usability of data
that is in a not ever preliminary predictable format and causes an intuitive behaviour to design of own
structs and class members with the C multi-language castability and transformable backend.

The library aims to design open datatypes as one dependency of a dataclass and a front-end class with member
functions that uses it. In furthermode it designs a `DataClass< InheritingClass, DataType >` class, that posterior
to API-design unites the datatype backend with the usability of a class that thus is using the datatype without
having the dependency overhead/bottleneck that a datatype needs to be designed for only one usability member functions
class or otherway round, because inheritance unites then datatype with functionability in on independent designable
deriving base class as base for all design patterns and is-a/is-of polymorphistic type designs, thus furthermore letting
datatype and functionality-class still left independent reusable for data designers, for example for moe is-united-a-dataclass
unitions.

* How to use it is documented lower on this page.

* TODO: Usability example(s).
* TODO: More documentation and README.

#### Currently supported features

*

## Building

You can simply build this with:

```
 % cd /path/to/clone/in
 % git clone https://github.com/onepointerT/libdscpp.git
 % mkdir libdscpp/build # or some other build directory
 % cd libdscpp/build
 % cmake .. # You may add CMake options here (see below)
 % make
```

#### CMake options

Additionally to the default options CMake currently offers the following options (can be specified with `-DOPTION=ON` or before `add_subdirectory( libdscpp )` with the CMake `set()` command.):

* `DSCPP_SHARED`: Enables building a shared library `libdscpp.so`. Not using this option builds a static `libdscpp.a` by default.
* `DSCPP_DISABLE_VERSION_PROMPT`: Disable the initial version and URL prompt.
* `DSCPP_DESTDIR`: Where are the files installed to. Defaults to `CMAKE_INSTALL_PREFIX` (`/usr` on UNIX and `c:/Program Files` on WIN32)
* `DSCPP_HEADER_INSTALL_DIR`: Can be set to control, where headers are installed. Defaults to `DSCPP_DESTDIR/include/libdscpp`.
* `DSCPP_LIB_INSTALL_DIR`: Can be set to control where the library is installed. Defaults to `DSCPP_DESTDIR/lib`.
* `DSCPP_INSTALL_LIBS`: Enables targets for installation of library files. Because it is useful not to install the library (e.g. when used as submodule of a project) this defaults to off. If enabled, it installs all headers to `DSCPP_HEADER_INSTALL_DIR` and the library to `DSCPP_LIB_INSTALL_DIR`
* `BUILD_DSCPP_TEST`: Build a simple main runtime that demonstrates current features of libdscpp.

#### Compiler options / Config variables

You can define the following with your g++-compiler by `-DOPTION=1` or cmake's `add_definitions( -D$OPTION=1 )` function:

*

#### Requirements

* cmake>=3.0
* a c++ compiler (tested for gcc)
* doxygen (optional for building the [html documentation](https://doc.0ptr.de/libdscpp/))

## Use with CMake

The included `LibDSCPPConfig.cmake` module enables you to use `find_package(LibDSCPP >= 1.6)` in CMake:

* `LIBDSCPP_INCLUDE_DIR`: The directory, where the headers are located in `libdscpp/` (usually `/usr/include`)
* `LIBDSCPP_LIBRARY`: The static library you can link into your program. It's only useful, if you use `stdlog`
* `LIBDSCPP_VERSION_STRING`: The current version of libdscpp.

## License

This library is free software; you can redistribute it and/or modify it under the terms of the AFL and the MIT licenses.

* Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>

## Usage
