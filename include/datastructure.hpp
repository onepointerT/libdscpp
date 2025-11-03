/**
 * @file datastructure.hpp
 * @brief A file that defines a generic datastructure interface for C++.
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

#include "classfactory.hpp"
#include "cdictionary.hpp"
#include "datatype.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeinfo>
#include <typeindex>
#include <utility>


namespace dscpp {


/**
 * @brief A simple generic data structure of `libdsC++` specializing a
 *      `dscpp::DataClass` with some functionality
 * @tparam InheritingClass The class that is giving a `dscpp::DataClass`
 *      more functionality than simply holding data
 */
template< typename InheritingClass >
    requires dscpp::detail::is_subclass_of_datatype_base< InheritingType >::value
class DataStruct
    :   public dscpp::DictionaryC
    ,   public InheritingClass
{
protected:
    /** 
     * @brief Setup your `DataStruct` from another format of data
     * @tparam DataIn The other format of data, e.g. a data protocol providing data
     * @param data A pointer to the data
     * @returns True on success
     */
    template< typename DataIn >
    virtual bool setupFromData( const DataIn* data ) = 0;

    /**
     * @brief Setup your `DataStruct` from another format of data
     * @tparam DTO The other format of data, e.g. a `libdsC++`-API's `DataClass` or `DataType`
     * @param dcdata A pointer to the data
     * @returns True on success
     */
    template< class DTO >
    virtual bool setup( void* dcdata ) {
        return this->copyDataTransform<DTO>( *((DTO*) dcdata) );
    }

    /**
     * @brief Constructor. Setup this instance with data
     * @param dcdata A pointer to the data
     * @param type The `std::type_info` value as given from `typeid(dcdata)`.
     */
    DataStruct( void* dcdata, std::type_info type )
        :   dscpp::DictionaryC()
        ,   InheritingClass()
    {
        this->setup<decltype(std::declval(std::type_index(type).name()))>(dcdata);
    }

    /**
     * @brief Constructor. Setup this instance with data of another format
     * @tparam DataFormat Another data format, e.g. `DataClass` or `DataType`
     * @param data A pointer to the data
     * @param type The `std::type_info` value as given from `typeid(dcdata)`.
     */
    template< class DataFormat >
    explicit DataStruct( DataFormat* data )
        :   dscpp::DictionaryC()
        ,   InheritingClass()
    {
        this->setupFromData<DataFormat>(data);
    }

};



} // namespace dscpp
