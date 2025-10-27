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
}

#include "map.hpp"

#include <string>
#include <string_view>


namespace dscpp {


class Dictionary {
public:
    class Key
        :   public std::string_view
    {
    public:
        const std::string key;

        Key( const char* key, const char* value );
    };

    
    typedef typename dscpp::Map< const std::string, Key* > kmap_t;

    class Section
        :   public kmap_t
    {
    public:
        Section()
            :   kmap_t()
        {}

        Section& operator<<( const Key& key );
        Section& operator<<( std::pair< std::string, std::string > kv_pair );

        Key& operator()( const std::string key_name );
        const Key& operator()( const std::string key_name ) const;
    };

    typedef typename dscpp::Map< const std::string, Section* > smap_t;

protected:
    smap_t& m_sections;

public:
    Dictionary();

    smap_t& sections();
    const smap_t& sections() const;

    Section& section( const char* section_name );
    const Section& section( const char* section_name ) const;

    dscpp::MMap< const std::string, Key* > to_stl() const;
};



} // namespace dscpp
