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

#include "dictionary.hpp"


namespace dsc {


class DictionaryC
    :   public dscpp::Dictionary
    ,   public _dictionary_
{
public:
    Dictionary( const _dictionary_& cdict );
};



} // namespace dscpp
