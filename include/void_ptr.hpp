/**
 * @file void_ptr.hpp
 * @brief A file that defines the void pointer and typecasting of `void*` for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
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
