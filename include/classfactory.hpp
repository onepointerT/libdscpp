/**
 * @file classfactory.hpp
 * @brief A file that defines dataclasses with the `libdsC` and `libdsC++` facitlity libraries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {
}

#include "dataclass.h"
#include "datatype.h"

#include "datatype.hpp"
#include "dictionary.hpp"
#include "map.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeindex>
#include <typeinfo>
#include <utility>


namespace dscpp {

/**
 * @brief The C++ type factory for conversion and creation of datatype classes.
 */
class ClassFactory {
public:
    /**
     * @brief The C++ generic type of data classes for e.g. use in inheritance of other
     *      libraries or parts of the dsC++API.
     * @note Adds an attribute of the type `std::type_info type_data` that thus can be
     *      used for e.g. type casting a `ClassFactory::DataClass dc` basing and inheriting
     *      type like this
     * 
     *      `return static_cast<decltype(std::declval(std::type_index(dc.type_data).name())) *>(dc.data);`
     * @note You may use `ClassFactory::castData()` for conversion of the `ClassFactory::DataClass::data`
     *      attribute
     */
    typedef struct _DataClass_
        :   public _dataclass_
    {
        std::type_info type_data;
    } DataClass;

    /**
     * @brief Brief create a API-common datatype `DT` from its constructor `DT(const Dictionary::Section& )`
     *      and get it as `voidptr`
     * @tparam DT The data type to create
     * @param section The section to create the data type `DT` from
     * @returns A new instance of `DT*`. You may cast the `void*` with
     *      `DT* dt = (DT*) ClassFactory::toDataVoidPtr<DT>(section);`
     */
    template< typename DT >
    static void* toDataVoidPtr( const dscpp::Dictionary::Section& section ) {
        DT* datatype = new DT(section);
        return datatype;
    }

    /**
     * @brief Get the data of a `Dictionary::Section` as a generic `libdsC` data class at it's C++ API
     * @tparam DT The datatype of the attribute at `ClassFactory::DataClass::data::vars`.
     * @param section The section to create the `datatype` from
     * @param toDataPtr The function that thus transforms the `dscpp::Dictionary::Section` to the type `DT`.
     * @note `void* ClassFactory::DataClass::data::vars = (DT*) toDataPtr(section)`.
     * @returns A pointer to a `DataClass`
     */
    template< typename DT >
    static dscpp::ClassFactory::DataClass* getData( const dscpp::Dictionary::Section& section
        , void* (*toDataPtr)(const dscpp::Dictionary::Section&) = &dscpp::ClassFactory::toDataVoidPtr<DT> ) {
        ClassFactory::DataClass* dc = new ClassFactory::DataClass{ .elements = section.size()
                                , .data = new struct _datatype_{ .dt_name = typeid(DT).name()
                                , .vars = (DT*) toDataPtr(section) }
                                , .type_data = typeid(DT) };
        return dc;
    }

    /**
     * @brief Cast data from a `DataClass` reference to a type `DTC`
     * @tparam DTC The type to cast `dc` to.
     * @note This function will use `dc.type_data` for finding out `DTC` with
     *      `decltype(std::declval(std::type_index(dc.type_data).name()))`
     * @returns A pointer-to-reference of the type `DTC` of the generic `datatype` at `dc.data`
     */
    template< typename DTC >
    static DTC*& castData( const dscpp::ClassFactory::DataClass& dc ) {
        return static_cast<decltype(std::declval(std::type_index(dc.type_data).name())) *>(dc.data);
    }

    /**
     * @brief The `dscpp::DataType` for `ClassFactory`
     * @tparam DT The concrete datatype that is inherited by `dscpp::DataType<DT>`
     */
    template< class DT >
    using Datatype = dscpp::DataType<DT>;

    /**
     * @brief Control, if you have implemented a valid `libdsC++` datatype.
     * @tparam DT The concrete datatype that is used by `dscpp::DataTypeBase<DT>`
     * @note You can use `requires` of `<concepts>` for controlling of type safety like this
     *      
     *      template< class DT >
                requires ClassFactory::is_dtype< DT >::value
            class DataType
                :   public DT
            {}
     */
    template< class DT >
    using is_dtype = std::is_base_of< DataTypeBase<DT>, DT >;
};

/**
 * @brief The `dscpp::DataType` for `libdsC++`
 * @tparam DT The concrete datatype that is inherited by `dscpp::DataType<DT>`
 */
template< typename DT >
using Datatype = ClassFactory::Datatype<DT>;

/**
 * @brief Control, if you have implemented a valid `libdsC++` datatype.
 * @tparam DT The concrete datatype that is used by `dscpp::DataTypeBase<DT>`
 * @note You can use `requires` of `<concepts>` for controlling of type safety like this
 *      
 *      template< class DT >
            requires ClassFactory::is_dtype< DT >::value
        class DataType
            :   public DT
        {}
    */
template< typename DT >
using is_datatype = ClassFactory::is_dtype<DT>;

// Forward declaration
template< typename InheritingClass, class DataType >
    requires dscpp::is_datatype< DataType >::value
class DataClass;


/**
 * @brief Transform a `dscpp::DataType<DT>` into a functional `DataClass< .., DT >`
 * @tparam The data type value collector class or struct, that is inherited by `dscpp::DataType<DT>`
 *      and has `DataTypeBase<DT>` as it's base class
 * @tparam FunctionalType The `DataClass< InheritedType, DT >` has a functional base which always inherits
 *      `dscpp::OwnDataClass` and adds functionality to a general data type
 * @param dc The simple `DataType<DT>` to transform to a `DataClass`
 * @param data The data to add as `voidptr`
 * @returns A `DataClass< FunctionalType, DT >` of `libdsC++` on success, `NULL` otherwise
 */
template< class DT, class FunctionalType >
extern inline dscpp::DataClass<FunctionalType, DT>* toDataCls( const Datatype<DT>& dc, void* data );


} // namespace dscpp
