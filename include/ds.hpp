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

using DataScienceKey = Dictionary::Key;
using DataScienceMap = dscpp::MMap< const std::string, IniVariable* >;

IniMap& parseFromFile( const char* filepath );


class DataScience
    :   public IniMap
{
public:
    static IniMap& parseFromFile( const char* filepath );

    Ini( const std::string filepath );

    class Compact
    {
    protected:
        ini_t* m_ini;
        Dictionary& m_dict;
        
    public:
        Compact();

        Dictionary::Key& get_key( const char* section_name, const char* key );
        Dictionary::Key& get_key_byIndex( const char* section_name, const unsigned int idx );
    };

    class PerSection
    {
    protected:
        Dictionary& m_dict;

    public:
        PerSection( Dictionary& dict );

        Dictionary::Section& get_section( const char* key );
        Dictionary::Key& get_key( const char* section_name, const char* key );
        Dictionary::Key& get_key( const Dictionary::Section& dct_section, const char* key );
    };

    class ClassFactory {
    public:
        typedef struct _dataclass_ {
            const size_t elements;
            void* data;
            const std::type_info datatype;
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
        class _datatype_ {
        protected:
            virtual bool setup( void* dcdata ) = 0;

            _datatype_();

        public:
            template< class DT >
            bool copyFrom( const DT* data );
            bool fromVoidPtr( void* dcdata ) { this->setup(dcdata); }
            bool fromDataClass( const dataclass& dc ) { this->fromVoidPtr(dc.data); }
        };

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

    template< typename InheritingClass >
    class DataStruct
        :   protected ClassFactory::_dataclass_<InheritingClass>
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

    
    template< class InheritingClass, class DataType >
        requires is_datatype< DataType >::value
    class DataClass
        :   public ClassFactory::dataclass
        ,   public DataType
    {
    protected:
        virtual bool setupVariables( InheritingClass& ic, DataClass<InheritingClass, DataType>& dc ) = 0;
        virtual bool setupVariables( DataClass<InheritingClass, DataType>& dc ) {
            return InheritingClass::setupVariables(*this, dc);
        }

    public:
        virtual InheritingClass& toDataStructure( const Dictionary::Section& section ) {
            typename InheritingClass* ic = new InheritingClass( section );

            this->setupVariables( ic );

            return *ic;
        }

        DataClass( const Dictionary::Section& section )
            :   ClassFactory::dataclass( ClassFactory::getData( section ) )
            ,   DataType( Ini::toDataStruct<DataType>(this) )
        {
            this->data = (DataType*) this;
        }
    };

protected:

public:
    static Compact* getFromFile( const char* filepath );
    static PerSection* getFile( const char* filepath );

    static PerSection* transform( const Compact& compact_ini );
};

} // namespace dscpp
