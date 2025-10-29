/**
 * @file dataclass.hpp
 * @brief A file that defines the specific dataclass for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
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
#include <type_traits>


namespace dscpp {

class OwnDataClass {
protected:
    virtual void* getDT() = 0;

    template< class DT >
    DT& getDataType() { (*(DT*) this->getDT()); }
};


template< class InheritingClass, class DataType >
    requires std::is_base_of< OwnDataClass, InheritingClass >::value
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

    virtual void* getDT() final { return (DataType*) this; }

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


#define DSC_DEFINE_DATACLASS(functional_cls, datatype) template class dscpp::DataClass< functional_cls, datatype >;
#define DSC_MAKE_DATACLASS(functional_cls, datatype, nameCLS) typedef typename dscpp::DataClass< functional_cls, datatype > nameCLS;

} // namespace dscpp
