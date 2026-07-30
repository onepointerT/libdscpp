/**
 * @file map.hpp
 * @brief A file that defines practical structures and short algorithms for std::map and dictionaries.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

#include "uuid.hpp"

#include <concepts>
#include <string>


namespace dscpp {


class Element {
public:
    class UnnamedBase
        :   public dscpp::id::NID
    {
    public:
        UnnamedBase( const std::string nid = id::UUID::v4() );

        virtual operator std::string() const;

        virtual bool operator<( const dscpp::Element::UnnamedBase& another ) const;
    };
    
    class Base
        :   public Element::UnnamedBase
    {
    public:
        const std::string name;

        Base();
        Base( const std::string key );

        virtual operator std::string() const;

        virtual bool operator<( const dscpp::Element::Base& another ) const;
    };
};

template< class T >
//    requires std::is_base_of< Element::UnnamedBase, T >::value 
class ContainerElement
    :   public T
{
public:
    using base_type = typename T;
    
    ContainerElement()
        :   T()
    {}
    ContainerElement( T& elem )
        :   T( elem )
    {}

    void set( T& elem ) { *this = T(elem); }

    virtual bool operator<( const ContainerElement<T>& another ) const {
        return ((std::string) *this) < ((std::string) another);
    }
};


namespace details {
template< class T >
using is_container_element = std::is_base_of< typename Element::Base, T >;

template< typename T >
class Compare
{
public:
    constexpr bool operator()( const Element::UnnamedBase& lhs, const Element::UnnamedBase& rhs ) const {
        return ((std::string) lhs) < ((std::string) rhs);
    }
    constexpr bool operator()( const T& lhs, const T& rhs ) const {
        return ((std::string) lhs) < ((std::string) rhs);
    }
    constexpr bool operator()( const ContainerElement<T>& lhs, const ContainerElement<T>& rhs ) const {
        return lhs < rhs;
    }
};
} // namespace details


} // namespace dscpp


namespace std {

}

