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

}

#include "classfactory.hpp"
#include "dictionary.hpp"
#include "map.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeinfo>


namespace dscpp {

template< class InheritingClass, class DataType >
    requires dscpp::is_datatype< DataType >::value
class DataClass
    :   public ClassFactory::dataclass
    ,   public Datatype<DataType>
    ,   public InheritingClass
{
protected:
    virtual bool setupVariables( InheritingClass& ic, DataClass<InheritingClass, DataType>& dc ) = 0;
    virtual bool setupVariables( DataClass<InheritingClass, DataType>& dc ) {
        return InheritingClass::setupVariables(*this, dc);
    }

public:
    virtual InheritingClass& toDataStructure( const Dictionary::Section& section ) {
        InheritingClass* ic = new InheritingClass( section );

        this->setupVariables( ic );

        return *ic;
    }

    DataClass( const Dictionary::Section& section )
        :   ClassFactory::dataclass( ClassFactory::getData( section ) )
        ,   DataType( toDataStruct<DataType>(this) )
    {
        this->data = (DataType*) this;
    }
};


} // namespace dscpp
