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

class ClassFactory {
public:
    typedef struct _dataclass_
        :   public dsc::_dataclass_
    {
        std::type_info type_data;
    } dataclass;

    template< typename DT >
    static void* toDataVoidPtr( const Dictionary::Section& section ) {
        DT* datatype = new DT(section);
        return datatype;
    }

    template< typename DT >
    static ClassFactory::dataclass* getData( const Dictionary::Section& section
        , void* (*toDataPtr)(const Dictionary::Section&) = &ClassFactory::toDataVoidPtr<DT> ) {
        ClassFactory::dataclass* dc = new ClassFactory::dataclass{ .elements = section.size()
                                , .data = new _datatype_{ .dt_name = typeid(DT).name(), .vars = (DT*) ClassFactory::toDataVoidPtr(section) }
                                , .type_data = typeid(DT) };
        return dc;
    }

    template< typename DTC >
    static DTC*& castData( const dataclass& dc ) {
        return static_cast<decltype(std::declval(std::type_index(dc.type_data).name())) *>(dc.data);
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
    requires dscpp::is_datatype< DataType >::value
class DataClass;

template< class DT >
    requires is_datatype<DT>::value
inline static DataType<DT>& toDataStruct( const Datatype<DT>& dc, void* data ) {
    return dscpp::toDataStruct<DT>(dc, data);
}

} // namespace dscpp
