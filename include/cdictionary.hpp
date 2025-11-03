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

#include "dictionary.hpp"


namespace dscpp { class Dictionary; }

/**
 * @brief  `LibdsC`: An intuitive and highly usable API backend for data science and data design with C/C++
 */
namespace dsc {

/**
 * @brief The compatibility-layer dscpp::Dictionary for C `dictionary` structs
 * @note Inherits `dscpp::Dictionary` and `struct _dictionary_`
 */
class DictionaryC
    :   public dscpp::Dictionary
    ,   public _dictionary_
{
public:
    /**
     * @brief Constructor
     * @param cdict A `struct _dictionary_` pointer for creation of a `dscpp::DictionaryC`
     */
    DictionaryC( struct _dictionary_* cdict );

    /**
     * @brief Update this instance with an C `dictionary` instance
     * @param cdict An C `struct _dictionary_` instance
     * @returns True on success
     */
    bool update( struct _dictionary_* cdict );
    /**
     * @brief Update this instance from an C `dictionary_element` instance
     * @param cdict An C `struct _dictionary_element_` instance
     * @returns True on success
     */
    bool update( const struct _dictionary_element_* cdict_elem );

    /**
     * @brief Update this instance with an C `dictionary` instance
     * @param cdict An C `struct _dictionary_` instance
     * @returns `*this`
     */
    DictionaryC& operator<<( struct _dictionary_* cdict );
    /**
     * @brief Update this instance from an C `dictionary_element` instance
     * @param cdict An C `struct _dictionary_element_` instance
     * @returns `*this`
     */
    DictionaryC& operator<<( const struct _dictionary_element_* cdict_elem );
};



} // namespace dsc


namespace dscpp {
using CDictionary = dsc::DictionaryC;
using DictionaryC = dsc::DictionaryC;
} // namespace dscpp
