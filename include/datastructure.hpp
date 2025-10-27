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
#include "ds.h"
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
