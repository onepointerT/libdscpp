/**
 * @file ds.hpp
 * @brief A file that defines common datatype facilities for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {
}


#include "datatype.h"
#include "dictionary.hpp"
#include "map.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeinfo>
#include <type_traits>


namespace dscpp {


/**
 * @brief Convert a `libdsC` general `datatype` pointer `dt` to a datatype `DT`
 * @tparam DT The data type to transform `dt` to
 * @tparam dt_name The name of the data type `DT`
 * @param dt A valid pointer to a standard `libdsC` `struct _datatype_`
 * @returns A reference to a newly created instance of the type `DT`
 */
template< class DT, const char* dt_name >
extern inline DT& toSpecificDatatype( const struct _datatype_* dt );

/**
 * @brief Convert a datatype `DTO` to a datatype `DT`
 * @tparam DT The data type to transform `dt_other` to
 * @tparam DTO The other data type to transform `dt_other` from
 * @param dt_other A valid reference to a standard data type of your data science API
 * @returns A reference to a newly created instance of the type `DT`
 */
template< class DT, class DTO >
extern inline DT& fromSpecificDatatype( const DTO& dt_other );


/**
 * @brief The base class of your data types for data design.
 * @tparam InheritingType The type that your data type base has
 */
template< class InheritingType >
class DataTypeBase {
protected:
    void* dtbase_data;

public:
    /**
     * @brief Constructor
     * @param dt_other The pointer to the data or `NULL`,
     *      if your data class will be added at `DataType< InheritingType >::dtc`
     */
    DataTypeBase( const void* dt_other )
        :   dtbase_data( dt_other )
    {}

    /**
     * @brief Accept new data for this data type
     * @param iht A reference to the instance of your data type that is inheriting
     *      this base class
     * @returns True on success
     * @note This function is pure virtual
     */
    virtual bool acceptData( const InheritingType& iht ) = 0;

    /**
     * @brief Copy data from a general datatype pointer from `libdsC`
     * @param dt The pointer to the `struct _datatype_`
     * @returns True on success
     */
    virtual bool copyDataFrom( const struct _datatype_* dt ) {
        return this->acceptData( dscpp::toSpecificDatatype< InheritingType, dt->dt_name >( dt ) );
    }

    /**
     * @brief Copy data from a another datatype reference from one of your APIs
     * @tparam DTO The type that the other data type has got
     * @param dt_other The reference to your data type of the type `DTO`
     * @returns True on success
     */
    template< class DTO >
    bool copyDataTransform( const DTO& dt_other ) {
        return this->acceptData( dscpp::fromSpecificDatatype<InheritingType, DTO>( dt_other ) );
    }
};


/** @brief Detail concepts */
namespace detail {
/**
 * @brief Test, if a class `DT` is inheriting the class `DataTypeBase<DT>`
 * @tparam DT The data type to check, if it has got `DataTypeBase<DT>` as its base class
 */
template< class DT >
using is_subclass_of_datatype_base = std::is_base_of< DataTypeBase<DT>, DT >;
} // namespace detail


/**
 * @brief This class represents the default data type of `libdsC++`
 * @tparam DT The class of your data type. `DT` needs to inherit from `DataTypeBase<DT>`
 * @note Inherits your data type `DT`
 */
template< class DT >
    requires detail::is_subclass_of_datatype_base< DT >::value
class DataType
    :   public DT
{
protected:
    /** @brief A pointer to a `struct _datatype_` from `libdsC` */
    struct _datatype_* dtc;

    /**
     * @brief Setup this data type
     * @param dcdata The data types data as `voidptr`
     * @returns True on success
     * @note This function is pure virtual
     */
    virtual bool setup( void* dcdata ) = 0;
    /**
     * @brief Setup this data type
     * @param dict A pointer to a `dictionary`
     * @returns True on success
     * @note This function is pure virtual
     */
    virtual bool setup( const dictionary* dict ) = 0;

    /** @brief Constructor */
    DataType()
        :   DT()
    {}

public:
    /**
     * @brief Get a reference to your data type
     * @returns A reference to `DT`
     */
    DT& operator()() {
        return *this;
    }

    /**
     * @brief Update the data from another of the classes with the same
     *      data type `DT` of your API
     * @param other A reference to another instance of the same data type
     * @returns A reference to `*this`
     */
    DataType<DT>& operator<<( const DT& other ) {
        /*try {*/ this->copyDataTransform<DT>( other ); /*}*/ // catch whatever to do when no cpyDT.
        return *this;
    }
    /**
     * @brief Update the data from another of the standard `datatype`s of `libdsC++`
     * @param other A pointer to another instance of the type `struct _datatype_`
     * @returns A reference to `*this`
     */
    DataType<DT>& operator<<( const struct _datatype_* other ) {
        /*try {*/ this->copyDataFrom( other ); /*}*/ // catch whatever to do when no cpyDT.
        return *this;
    }

    /**
     * @brief Copy data from another of your data types
     * @tparam DTO The type of the other data type
     * @param data A pointer to an instance of `DTO`
     * @returns True on success
     */
    template< class DTO >
    bool copyFrom( const DTO* data ) {
        if ( data == 0 ) return false;
        return this->copyDataTransform( *data );
    }
    /** @note Specialization of `copyFrom<DTO>( const DTO* data )` */
    template<>
    bool copyFrom( const struct _datatype_* other ) {
        return this->copyDataFrom( other );
    }

    /**
     * @brief Setup this data type from a `voidptr`
     * @param dcdata The data class/struct/type to copy data from
     * @returns True on success
     */
    bool fromVoidPtr( void* dcdata ) { this->setup(dcdata); }
    /**
     * @brief Setup this data type from a `struct _dataclass_`
     * @param dc The data class/struct/type to copy data from
     * @returns True on success
     */
    bool fromDataClass( const dataclass& dc ) { this->fromVoidPtr(dc.data); }
};


} // namespace dscpp
