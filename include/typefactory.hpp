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
#include "dataclass.h"
}

#include "dictionary.hpp"
#include "map.hpp"

#include <concepts>
#include <string>
#include <string_view>
#include <typeinfo>


namespace dscpp {

class ClassFactory {
public:
    typedef struct _dataclass_
        :   public dscpp::_dataclass_
    {
        const std::type_info type_data;
    } dataclass;

    template< typename DT >
    static void* toDataVoidPtr( const Dictionary::Section& section ) {
        DT* datatype = new DT(section);
        return datatype;
    }

    template< typename DT >
    static dataclass*& getData( const Dictionary::Section& section
        , void* (*toDataPtr)(const Dictionary::Section&) = &ClassFactory::toDataVoidPtr ) {
        dataclass* dc = new dataclass{ .elements: section.size()
                                , .data: toDataPtr(section)
                                , .datatype: typeid(DT) };
        return dc;
    }

    template< typename DT >
    static DT*& castData( const dataclass& dc ) {
        return static_cast<DT=decltype(dc.datatype.name())>(dc.data);
    }

    template< class DT >
    using _datatype_ = dscpp::DataType<DT>;

    template< class DT >
    using is_dtype = std::is_base_of< _datatype_<DT>, DT >;
};

template< typename DT >
using Datatype = ClassFactory::_datatype_<DT>;

template< typename DT >
using is_datatype = ClassFactory::is_dtype<DT>;

template< typename InheritingClass, class DataType >
class DataClass;

template< class DataType >
    requires is_datatype<DataType>::value
inline static DataType& toDataStruct( const Datatype<DataType>& dc, void* data ) {
    return dscpp::toDataStruct<DataType>(dc, data);
}

} // namespace dscpp
