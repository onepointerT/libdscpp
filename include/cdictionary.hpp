/**
 * @file cdictionary.hpp
 * @brief A file that defines dictionaries from `dictionary.h` of `libdsC` for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {
#include "dictionary.h"
#include "dictionary_element.h"
}

namespace dscpp { class Dictionary; }


namespace dsc {


class DictionaryC
    :   public dscpp::Dictionary
    ,   public _dictionary_
{
public:
    DictionaryC( const struct _dictionary_* cdict );

    bool update( const struct _dictionary_* cdict );
    bool update( const struct _dictionary_element_* cdict_elem );

    DictionaryC& operator<<( const struct _dictionary_* cdict );
    DictionaryC& operator<<( const struct _dictionary_element_* cdict_elem );
};



} // namespace dscpp
