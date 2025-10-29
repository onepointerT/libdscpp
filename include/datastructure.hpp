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

#include "dictionary.hpp"
#include "map.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeinfo>


namespace dscpp {


template< typename InheritingClass >
class DataStruct
    :   protected _dataclass_<InheritingClass>
{
protected:
    template< typename DataIn >
    bool setupFromData( const DataIn* data ) {
        
    }

    virtual bool setup( void* dcdata ) {
        Ini::toDataStruct< InheritingClass >( *this, dcdata );
    }

    DataStruct( void* dcdata )
        :   ClassFactory::_dataclass_<InheritingClass>()
    {
        this->setup(dcdata);
    }

    template< class DataFormat >
    DataStruct( DataFormat* data )
        :   ClassFactory::_dataclass_<InheritingClass>()
    {
        this->setupFromData<DataFormat>(data);
    }

};



} // namespace dscpp
