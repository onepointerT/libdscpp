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
#include <stdexcept>
#include <string>


/**
 * @brief `LibdsC++`: An intuitive and highly usable API backend for data science and data design with C/C++
 */
namespace dscpp {


/**
 * @brief This is a default `std::map< Key, T, Compare >` with some additional functions
 * @tparam Key The key value's type, e.g. `std::string`; no const
 * @tparam T The type to save as elements for the `dscpp::Map`
 * @tparam Compare How to compare the elements on such things like sorting, merging and similar.
 *      Defaults to `std::less< Key >` and is optionally omittable
 */
template< typename Key, typename T, class Compare = std::less<Key> >
class Map
    :   protected std::map< Key, T, Compare >
{
public:
    /** @brief The type of the underlying standard template library map as typedef */
    typedef typename std::map< Key, T, Compare > stlmap_t;

    /**
     * @brief This nested class comprises a value tuple consisting of a `Key` and an
     *      object `T` per element.
     */
    class Value
        :   protected std::pair< Key, T >
    {
    public:
        /**
         * @brief Constructor
         * @param key The key to save
         * @param val The value to save
         */
        Value( const char* key, T val )
            :   std::pair< Key, T >{ key, val }
        {}

        /**
         * @brief Get the saved key as reference to a `std::string`
         * @returns The saved key as reference to a `std::string`
         */
        std::string& key() { return this->first; }
        /**
         * @brief Get the saved key as reference to a `const std::string`
         * @returns The saved key as reference to a `const std::string`
         */
        const std::string& key() const { return this->first; }

        /**
         * @brief Get the value as reference
         * @returns The value as reference to a `T`
         */
        T& value() { return this->second; }
        /**
         * @brief Get the value as reference
         * @returns The value as reference to a `const T`
         */
        const T& value() const { return this->second; }
    };

    /**
     * @brief Default Constructor
     */
    Map()
        :   stlmap_t()
    {}

    /**
     * @brief Test, if a `Key key` is contained inside of the `dscpp::Map`
     * @returns True, if the key was found inside of the `dscpp::Map< Key, T >`
     */
    bool contains( const Key key ) {
        return stlmap_t::contains(key);
    }

    /**
     * @brief Get the `Map< Key, T >::Value` referred to a key, if the key exists
     * @param key The key to search for
     * @returns A pointer-to-reference of a `const Map<Key, T>::Value`, if `key` was
     *      found, a `std::nullptr_t`, if `key` was not found
     */
    const Value*& get( const char* key ) const {
        if ( ! this->contains(key) ) return std::nullptr_t();
        return (*this)(key, std::nullptr_t());
    }

    /**
     * @brief Access the elements inside the map by reference
     * @param key The key to dereference it's value of
     * @returns A reference to an value object `T`
     */
    T& operator[]( const Key key ) {
        try {
            return stlmap_t::operator[](key);
        } catch ( std::out_of_range& oor ) {
            stlmap_t::insert( { key, std::nullptr_t() } );
            return stlmap_t::operator[](key);
        }
    }

    /** @brief The default `iterator` of `Map< Key, T, Compare >` from `stlmap_t` */
    typedef typename stlmap_t::iterator iterator;
    /** @brief The default `const_iterator` of `Map< Key, T, Compare >` from `stlmap_t` */
    typedef typename stlmap_t::const_iterator const_iterator;

    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::iterator`
     * @returns An `iterator` to the first element of the map
     */
    iterator begin() {
        return stlmap_t::begin();
    }
    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::iterator`
     * @returns An `iterator` to behind-the-last element of the map
     */
    iterator end() {
        return stlmap_t::end();
    }
    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::const_iterator`
     * @returns A `const_iterator` to the first element of the map
     */
    const_iterator cbegin() const {
        return stlmap_t::cbegin();
    }
    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::iterator`
     * @returns A `const_iterator` to behind-the-last element of the map
     */
    const_iterator cend() const {
        return stlmap_t::cend();
    }
    /**
     * @brief Get a reference to a new `Map< Key, T, Compare >::Value` for more actions
     * @note You may apply a `Value&` with the function `Map< Key, T, Compare >::apply()`
     * @param key The key where the value is stored
     * @param default_value The default value, that is thus used for creating a new `Map< Key, T >::Value`,
     *              if `key` was not found
     * @returns A reference to a `Map< Key, T >::Value`
     */
    Value& operator()( const Key key, T default_value = T() ) const {
        for ( iterator it : { this->begin(), this->end() } ) {
            if ( it->first == key ) return this->getValue(it);
        }
        return *new Value(key, default_value);
    }
    /**
     * @brief Apply a value to its' key inside of the `Map< Key, T >`
     * @note You may get a `Value&` from the function `Map< Key, T, Compare >::operator()(Key, T)`
     * @param value The value to apply to it's position inside the map
     * @returns True on success.
     */
    bool apply( const Value& value ) {
        try {
            (*this)[value.key()] = value.value();
        } catch ( std::out_of_range& oor ) { return false; }
        return true;
    }
    /**
     * @brief Get the `Map< Key, T >::Value` of a `stlmap_t::iterator it`
     * @param it The iterator to transform to a `Value` object
     * @returns A reference to a newly created `Map< Key, T, Compare >::Value` object
     * @note You may apply a `Value&` with the function `Map< Key, T, Compare >::apply()`
     */
    static Value& getValue( const typename stlmap_t::iterator it ) {
        return *new Value(it->first, it->second);
    }
    /**
     * @brief Append a range of iterators, e.g. from another `Map< Key, T, Compare >` to this map
     * @param rng The range to append and insert at the end of this `Map< Key, T, Compare >`
     * @returns The number of elements inserted into the map
     */
    size_t append_range( std::ranges::subrange<iterator>& rng ) {
        return stlmap_t::insert_range( rng );
    }
    /**
     * @brief Get the current size of the `Map< Key, T >`
     * @returns The number of elements inside of this map
     */
    size_t size() const {
        return stlmap_t::size();
    }
};


/**
 * @brief This class makes maps containing maps more easy to use by providing an
 *      `MMap< Key, T, Compare >::MapIterator` that thus holds one iterator to the
 *      submap per position
 * 
 * @tparam Key The key value's type, e.g. `std::string`; no const
 * @tparam T The type to save as elements of each position's key submap for the `dscpp::Map< Key, T, Compare >`
 * @tparam Compare How to compare the elements on such things like sorting, merging and similar.
 *      Defaults to `std::less< Key >` and is optionally omittable
 * 
 * @note This object inherits `dscpp::Map< Key, Map< Key, T, Compare >*, Compare >`
 */
template< typename Key, typename T, class Compare = std::less<Key> >
class MMap
    :   public Map< Key, Map< Key, T, Compare >*, Compare >
{
public:
    /** @brief The own type of the `MMap` */
    typedef Map< Key, Map< Key, T, Compare >*, Compare > map_t;
    /** @brief The type of the submaps stored at each key */
    typedef Map< Key, T, Compare > submap_t;
    /** @brief The type of the map iterator */
    typedef typename Map< Key, submap_t*, Compare >::iterator map_iterator_t;
    /** @brief The type of the submap iterator */
    typedef typename Map< Key, T, Compare >::iterator submap_iterator_t;

    /**
     * @brief The iterator of a `MMap< Key, T, Compare >`. You can access the submaps
     *      with `sub()`
     * @note Inherits `map_iterator_t`
     */
    class MapIterator
        :   public map_iterator_t
    {
    protected:
        /**
         * @brief The `submap_iterator_t`, an iterator for the submap at each position
         *      of this `MMap`
         */
        submap_iterator_t submap_it;

    public:
        /**
         * @brief Constructor
         * @param pos The position to begin at
         * @param subpos The position to begin at inside of the `submap_t` at this position.
         *          Defaults to `pos->second->begin()`.
         */
        MapIterator( map_iterator_t pos, submap_iterator_t subpos )
            :   map_iterator_t( pos )
            ,   submap_it( subpos )
        {}

        /**
         * @brief Dereference the `submap_iterator_t` of the submap at the current position
         *      of this instance's `MapIterator`
         * @returns The current position of `this->submap_it`
         */
        submap_iterator_t operator_() {
            return *this->submap_it;
        }

        /**
         * @brief Dereference the `submap_iterator_t` of the submap at the current position
         *      of this instance's `MapIterator`
         * @returns The current position of `this->submap_it`
         */
        submap_iterator_t sub() {
            return *this->submap_it;
        }

        /**
         * @brief Alter the position of the `MapIterator` to the next position behind the current
         *      element and set `this->submap_it` to `(*this)->second->begin()`
         * @returns This instance of the `MMap< Key, T >::MapIterator`
         */
        MapIterator operator++() {
            map_iterator_t::operator++();
            this->submap_it = (*this)->second->begin();
            return *this;
        }
        /**
         * @brief Alter the position of the `MapIterator` to the next position before the current
         *      element and set `this->submap_it` to `(*this)->second->end()`
         * @returns This instance of the `MMap< Key, T >::MapIterator`
         */
        MapIterator operator--() {
            map_iterator_t::operator--();
            this->submap_it = (*this)->second->end();
            return *this;
        }
    };

    /** @brief The `stlmap_t` type of the base class */
    using stlmap_t = typename Map< Key, Map< Key, T, Compare >*, Compare >::stlmap_t;

    /**
     * @brief Get a new `MapIterator` at the begin position of this `MMap< Key, T, Compare >`
     */
    MMap< Key, T, Compare >::MapIterator begin() {
        return *new MapIterator( map_t::begin(), map_t::begin()->second->begin() );
    }

    /**
     * @brief Get a new `MapIterator` at the behind-the-last element's position of this
     *      `MMap< Key, T, Compare >`
     */
    MMap< Key, T, Compare >::MapIterator end() {
        return *new MapIterator( map_t::end(), (new submap_t())->end() );
    }
};

/**
 * @brief This class makes dictionary maps containing maps more easy to use by providing an
 *      `MMap< Key, T >::MapIterator` that thus holds one iterator to the
 *      submap per position of the `MapIterator`
 * 
 * @tparam Key The key value's type, e.g. `std::string`; no const
 * @tparam T The type to save as elements of each position's key submap for the `dscpp::Map< Key, T, Compare >`
 * 
 * @note This object inherits `dscpp::MMap< Key, T >`
 */
template< typename Key, typename T >
class DMap : public MMap< Key, T > {};

} // namespace dscpp


namespace std {
template< typename Key, typename T >
using dict_map = typename dscpp::DMap< Key, T >;

template< typename Key, typename T, typename Compare = std::less<Key> >
using mmap = typename dscpp::MMap< Key, T, Compare >;

template< typename Key, typename T, typename Compare = std::less<Key> >
using submap_iterator = typename dscpp::MMap< Key, T, Compare >::submap_iterator_t;

template< typename Key, typename T, typename Compare = std::less<Key> >
using mmap_iterator = typename dscpp::MMap< Key, T, Compare >::MapIterator;
}

