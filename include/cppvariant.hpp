// Copyright (C) 2026 OnePointer
//

#pragma once

#include "cppmap.hpp"

#include <any>
#include <concepts>
#include <list>
#include <variant>
#include <type_traits>
#include <typeindex>
#include <typeinfo>


namespace dscpp {

// Forward declaration
template< class Key, class... VariantT >
class VariantValue;



template< class Type >
Type& get( std::any value ) {
    return std::any_cast< decltype(std::type_index(value.type())) >(value);
}

template< class Type, class... VariantT >
Type& get( std::variant< VariantT... >& value ) {
    const size_t idx_value = value.index();
    return dscpp::get<Type>( *new std::any(std::get<idx_value, VariantT...>(value)) );
}


template< class KeyT, class Type, class... VariantT >
Type& get( VariantValue< KeyT, VariantT... >& value ) {
    return dscpp::get<Type, VariantT... >( value );
}




template< class Key, class... VariantT >
class VariantValue
    :   public  std::variant< VariantT... >
{
public:
    std::type_info type;
    Key& key;

    template< class Type >
        requires std::_Is_any_of_v< Type, VariantT... >
    VariantValue( Key& k, Type& t )
        :   std::variant< VariantT >( t )
        ,   type( typeid(Type) )
        ,   key( k )
    {}

    template< class Type = decltype(std::type_index(this->type)) >
    Type& get() {
        return dscpp::get< Key, Type = decltype(std::type_index(this->type)), VariantT... >( *this );
    }
};

template< class Key, class... VariantT >
class VariantMap
    :   protected dscpp::Map< Key, VariantValue< Key, VariantT... > >
{
public:
    typedef typename dscpp::Map< Key, VariantValue< Key, VariantT... > > vmap_t;
    typedef typename dscpp::VariantValue< Key, VariantT... > variant_value_t;

    VariantMap()
        :   vmap_t()
    {}

    using typename vmap_t::const_iterator;
    using typename vmap_t::iterator;
    using typename vmap_t::Value;
    using vmap_t::contains;
    using vmap_t::atPos;
    using vmap_t::get;
    using vmap_t::operator[];
    using vmap_t::begin;
    using vmap_t::end;
    using vmap_t::cbegin;
    using vmap_t::cend;
    using vmap_t::operator();
    using vmap_t::size;
};




template< class Key, class... VariantT >
class VariantList
    :   protected std::list< VariantValue< Key, VariantT... >* >
{
public:
    typedef typename std::list< VariantValue< Key, VariantT... >* > vlist_t;
    typedef typename dscpp::VariantValue< Key, VariantT... > variant_value_t;

    VariantList()
        :   vlist_t()
    {}
};


} // namespace dscpp


namespace std {
template< typename Key, class... VariantT >
using variant_value = dscpp::VariantValue< Key, VariantT... >;

template< typename Key, class... VariantT >
using vmap = dscpp::VariantMap< Key, VariantT... >;

template< typename Key, class... VariantT >
using vlist = dscpp::VariantList< Key, VariantT... >;
} // namespace std