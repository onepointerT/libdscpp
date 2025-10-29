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


template< class DT, const char* dt_name >
extern inline DT& toSpecificDatatype( const struct dsc::_datatype_* dt );

template< class DT, class DTO >
extern inline DT& fromSpecificDatatype( const DTO& dt_other );



template< class InheritingType >
class DataTypeBase {
public:
    DataTypeBase( const void* dt_other );

    virtual bool acceptData( const InheritingType& iht ) = 0;

    virtual bool copyDataFrom( const struct dsc::_datatype_* dt ) {
        return this->acceptData( dscpp::toSpecificDatatype< InheritingType, dt->dt_name >( dt ) );
    }

    template< class DTO >
    bool copyDataTransform( const DTO& dt_other ) {
        return this->acceptData( dscpp::fromSpecificDatatype<InheritingType, DTO>( dt_other ) );
    }
};


namespace detail {
template< class DT >
using is_subclass_of_datatype_base = std::is_base_of< DataTypeBase<DT>, DT >;
} // namespace detail


template< class DT >
    requires detail::is_subclass_of_datatype_base< DT >::value
class DataType
    :   public DT
{
protected:
    struct dsc::_datatype_* dtc;

    virtual bool setup( void* dcdata ) = 0;
    virtual bool setup( const dictionary* dict ) = 0;

    DataType();

public:
    DT& operator()() {
        return *this;
    }

    DataType<DT>& operator<<( const DT& other );
    DataType<DT>& operator<<( const struct dsc::_datatype_* other ) {
        /*try {*/ this->copyDataFrom( other ); /*}*/ // catch whatever to do when no cpyDT.
        return *this;
    }


    template< class DTO >
    bool copyFrom( const DTO* data ) {
        if ( data == 0 ) return false;
        return this->copyDataTransform( *data );
    }
    template<>
    bool copyFrom( const struct dsc::_datatype_* other ) {
        return this->copyDataFrom( other );
    }

    bool fromVoidPtr( void* dcdata ) { this->setup(dcdata); }
    bool fromDataClass( const dsc::dataclass& dc ) { this->fromVoidPtr(dc.data); }
};


} // namespace dscpp
