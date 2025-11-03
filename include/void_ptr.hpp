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

#include "cdictionary.hpp"


namespace dscpp {

/**
 * @brief Free function that defines, how to cast or transform data
 *      from a `voidptr` to a specific type `VS`
 * @tparam VS The type you want to have from `vars_struct`
 * @returns A reference to `VS`, holding the data of `vars_struct`
 */
template< typename VS >
extern VS& castFromVoid( void* vars_struct );
/**
 * @brief Free function that defines, how to transform a `void*` to a
 *      `libdsC` dictionary
 * @param vars_struct The `void*` to transform to a default `struct _dictionary_`
 * @returns A pointer to a C `dictionary`
 */
extern struct _dictionary_* castToDictionary( void* vars_struct );


/**
 * @brief Like in `libdsC`, this represents a more generic data class for
 *      less predictable use cases
 */
class VoidStruct {
public:
    /** @brief The data pointer to a class/struct/type */
    void* vars;

    /**
     * @brief Get the data as a specific type
     * @tparam VS The type to get the data as
     * @returns A reference to `VS` by using `dscpp::castFromVoid<VS>( this->vars )`
     */
    template< typename VS >
    VS& vars() {
        return dscpp::castFromVoid<VS>( this->vars );
    }

    /**
     * @brief Get the data as a `DictionaryC`
     * @returns A reference to a `DictionaryC` by using `dscpp::castToDictionary(this->vars)`
     */
    DictionaryC& toDictionary() const {
        return *new DictionaryC( dscpp::castToDictionary(this->vars) );
    }
};


} // namespace dscpp
