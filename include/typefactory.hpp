/**
 * @file ds.hpp
 * @brief A file that defines *.ds dictionaries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibIniC++: A C++/C library for *.ds files and dictionaries.
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
