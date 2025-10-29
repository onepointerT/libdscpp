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


#include <map>
#include <ranges>
#include <string>


namespace dscpp {


template< typename Key, typename T, class Compare = std::less<Key> >
class Map
    :   protected std::map< Key, T, Compare >
{
public:
    typedef typename std::map< Key, T, Compare > stlmap_t;

    class Value
        :   protected std::pair< Key, T >
    {
    public:
        Value( const char* key, T val )
            :   std::pair< Key, T >{ key, val }
        {}

        std::string& key() { return this->first; }
        const std::string& key() const { return this->first; }

        T& value() { return this->second; }
        const T& value() const { return this->second; }
    };

    Map()
        :   stlmap_t()
    {}

    bool contains( const Key key ) {
        return stlmap_t::contains(key);
    }

    const Value*& get( const char* key ) const {
        if ( ! this->contains(key) ) return std::nullptr_t();
        return (*this)(key, std::nullptr_t());
    }


    T& operator[]( const Key key ) {
        return stlmap_t::operator[](key);
    }
    const T& operator[]( const Key key ) const {
        return stlmap_t::operator[](key);
    }

    typedef typename stlmap_t::iterator iterator;
    typedef typename stlmap_t::const_iterator const_iterator;

    iterator begin() {
        return stlmap_t::begin();
    }
    iterator end() {
        return stlmap_t::end();
    }
    const_iterator cbegin() const {
        return stlmap_t::cbegin();
    }
    const_iterator cend() const {
        return stlmap_t::cend();
    }

    Value& operator()( const Key key, T default_value = T() ) const {
        for ( iterator it : { this->begin(), this->end() } ) {
            if ( it->first == key ) return this->getValue(it);
        }
        return *new Value(key, default_value);
    }

    bool apply( const Value& value ) {
        (*this)[value.key()] = value.value();
    }

    static Value& getValue( const typename stlmap_t::iterator it ) {
        return *new Value(it->first, it->second);
    }

    size_t append_range( std::ranges::subrange<iterator>& rng ) {
        stlmap_t::insert_range( rng );
    }

    size_t size() const {
        return stlmap_t::size();
    }
};


template< typename Key, typename T, class Compare = std::less<Key> >
class MMap
    :   public Map< Key, Map< Key, T, Compare >*, Compare >
{
public:
    typedef typename Map< Key, T, Compare > submap_t;
    typedef typename Map< Key, submap_t*, Compare >::iterator map_iterator_t;

    class Iterator
        :   public map_iterator_t
    {
    public:
        typedef typename submap_t::iterator sub_iterator_t;

        friend class MMap< Key, T, Compare >;

    protected:
        sub_iterator_t* submap_it;

        Iterator( const map_iterator_t& pos, const sub_iterator_t& subpos )
            :   map_iterator_t( pos )
            ,   submap_it( subpos )
        {}

    public:
        sub_iterator_t& operator_() {
            return *this->submap_it;
        }

        sub_iterator_t& sub() {
            return *this->submap_it;
        }

        Iterator& operator++() {
            map_iterator_t::operator++();
            this->submap_it = this->second->begin();
        }
        Iterator& operator--() {
            map_iterator_t::operator--();
            this->submap_it = this->second->end();
        }
    };

    typedef Iterator iterator;
    typedef const Iterator const_iterator;

    iterator& begin() {
        return *new Iterator( this->begin(), (*this->begin())->begin() );
    }

    iterator& end() {
        return *new Iterator( this->end(), NULL );
    }
};

template< typename Key, typename T >
class DMap : public MMap< Key, T > {};

} // namespace dscpp


namespace std {
template< typename Key, typename T, typename Compare = std::less<Key> >
using dict_map = typename dscpp::DMap< Key, T >;

template< typename Key, typename T, typename Compare = std::less<Key> >
using mmap = typename dscpp::MMap< Key, T, Compare >;

template< typename Key, typename T, typename Compare = std::less<Key> >
using submap_iterator = typename dscpp::MMap< Key, T, Compare >::Iterator;
}

