/**
 * @file typefactory.hpp
 * @brief A file that defines useful functions for operations on data types for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "dataclass.hpp"


namespace dscpp {

class TypeFactory {
public:
    template< typename InheritingFunctionalCls, typename DT >
    static DT& getDT( const DataClass<InheritingFunctionalCls, DT> datacls ) {
        return *datacls;
    }
};

} // namespace dscpp
