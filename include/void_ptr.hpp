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
#include "dictionary.h"
}


namespace dscpp {

template< typename VS >
VS& castFromVoid( void* vars_struct );

dsc::_dictionary_* castToDictionary( void* vars_struct );


class VoidStruct {
public:
    void* vars;

    template< typename VS >
    VS& vars() {
        return dscpp::castFromVoid( this->vars );
    }
};


} // namespace dscpp
