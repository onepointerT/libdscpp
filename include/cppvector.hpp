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

#include "cpputils.hpp"

#include <concepts>
#include <memory>
#include <ranges>
#include <stdexcept>
#include <string>
#include <vector>


namespace dscpp {


class VectorElementBase
    :   public Element::Base
{
public:
    VectorElementBase() : Element::Base() {}
    VectorElementBase( const std::string key ) : Element::Base(key) {}
};

template< class T >
class VectorElement final
    :   public ContainerElement<T>
    ,   public T
{
public:
    VectorElement()
        :   T()
    {}
    VectorElement( T& elem )
        :   T( elem )
    {}
};


namespace details {
template< class T >
using is_vector_element = std::is_base_of< typename VectorElementBase, T >;
} // namespace details

/**
 * @brief This is a default `std::map< Key, T, Compare >` with some additional functions
 * @tparam Key The key value's type, e.g. `std::string`; no const
 * @tparam T The type to save as elements for the `dscpp::Map`
 * @tparam Compare How to compare the elements on such things like sorting, merging and similar.
 *      Defaults to `std::less< Key >` and is optionally omittable
 */
template< typename T, class Allocator = std::allocator<T> >
    requires details::is_vector_element<T>::value
class Vector
    :   protected std::vector< VectorElement<T>, Allocator >
{
public:
    /** @brief The type of the underlying standard template library vector as typedef */
    typedef typename std::vector< VectorElement<T>, Allocator > stlvector_t;
    typedef typename VectorElement<T> value_t;

    /**
     * @brief Default Constructor
     */
    Vector()
        :   stlvector_t()
    {}

    /**
     * @brief Test, if a `Key key` is contained inside of the `dscpp::Map`
     * @returns True, if the key was found inside of the `dscpp::Map< Key, T >`
     */
    bool contains( const std::string key ) {
        for ( T elem : *this ) {
            if ( ((std::string) elem) == key ) return true;
        }
        return false;
    }

    /**
     * @brief This nested class comprises a value tuple consisting of a `Key` and an
     *      object `T` per element.
     */
    class Value
        :   protected std::pair< std::string, T >
    {
    public:
        /**
         * @brief Constructor
         * @param key The key to save
         * @param val The value to save
         */
        Value( T& val )
            :   std::pair< std::string, T >{ ((std::string) val), val }
        {}
        /**
         * @brief Constructor
         * @param val The value to save
         */
        Value( const typename Vector<T, Allocator>::iterator it )
            :   std::pair< std::string, T >{ ((std::string) *it), it }
        {}
        /**
         * @brief Constructor
         * @param elem The value to save
         */
        Value( const typename VectorElement<T>& elem )
            :   std::pair< std::string, T >{ ((std::string) elem), elem }
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

        operator T() const { return this->value(); }
    };

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
    T& operator[]( const std::string key ) {
        for ( T& elem : *this ) { if ( ((std::string) elem) == key ) return elem; }
        return (*this)(key, *new T(key));
    }

    /** @brief The default `iterator` of `Map< Key, T, Compare >` from `stlvector_t` */
    typedef typename stlvector_t::iterator iterator;
    /** @brief The default `const_iterator` of `Map< Key, T, Compare >` from `stlvector_t` */
    typedef typename stlvector_t::const_iterator const_iterator;

    class VectorIterator
        :   public iterator
    {
    public:
        VectorIterator( const iterator it )
            :   iterator( it )
        {}
        VectorIterator( const const_iterator cit )
            :   iterator( cit )
        {}

        Value& getValue() const {
            return *new Value(((std::string) **this), **this);
        }

        void setValue( const Value& val ) {
            **this = *new VectorElement<T>(val.value());
        }

        const std::string key() const { return (std::string) **this; }
        VectorElement<T>& value() const { return **this; }
    };

    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::iterator`
     * @returns An `iterator` to the first element of the map
     */
    iterator begin() {
        return stlvector_t::begin();
    }
    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::iterator`
     * @returns An `iterator` to behind-the-last element of the map
     */
    iterator end() {
        return stlvector_t::end();
    }
    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::const_iterator`
     * @returns A `const_iterator` to the first element of the map
     */
    const_iterator cbegin() const {
        return stlvector_t::cbegin();
    }
    /** 
     * @brief Get `Map< Key, T, Compare >::front()` as `Map< Key, T, Compare >::iterator`
     * @returns A `const_iterator` to behind-the-last element of the map
     */
    const_iterator cend() const {
        return stlvector_t::cend();
    }
    /**
     * @brief Get a reference to a new `Map< Key, T, Compare >::Value` for more actions
     * @note You may apply a `Value&` with the function `Map< Key, T, Compare >::apply()`
     * @param key The key where the value is stored
     * @param default_value The default value, that is thus used for creating a new `Map< Key, T >::Value`,
     *              if `key` was not found
     * @returns A reference to a `Map< Key, T >::Value`
     */
    Value& operator()( const std::string key, T default_value = T() ) const {
        for ( iterator it : { this->begin(), this->end() } ) {
            if ( ((std::string) *it) == key ) return this->getValue(it);
        }
        return this->push_back( *new VectorElement<T>(&default_value) );
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
     * @brief Get the `Map< Key, T >::Value` of a `stlvector_t::iterator it`
     * @param it The iterator to transform to a `Value` object
     * @returns A reference to a newly created `Map< Key, T, Compare >::Value` object
     * @note You may apply a `Value&` with the function `Map< Key, T, Compare >::apply()`
     */
    static Value& getValue( const typename stlvector_t::iterator it ) {
        return *new Value(it);
    }
    /**
     * @brief Append a range of iterators, e.g. from another `Map< Key, T, Compare >` to this map
     * @param rng The range to append and insert at the end of this `Map< Key, T, Compare >`
     * @returns The number of elements inserted into the map
     */
    size_t append_range( std::ranges::subrange<iterator>& rng ) {
        return stlvector_t::append_range( rng );
    }
    /**
     * @brief Get the current size of the `Map< Key, T >`
     * @returns The number of elements inside of this map
     */
    size_t size() const {
        return stlvector_t::size();
    }

private:
    static inline std::unique_ptr< Vector<T, Allocator> > vectorend;

public:
    static inline const const_iterator staticend() {
        if ( ! Vector<T, Allocator>::vectorend ) {
            Vector<T, Allocator>::vectorend = std::unique_ptr< Vector<T, Allocator> >( new Vector<T, Allocator>() );
        }
        return Vector<T, Allocator>::vectorend->cend();
    }

    static bool is_end( const const_iterator cit ) { return cit == Vector<T, Allocator>::staticend(); }
    static bool is_end( const const_iterator cit, const Vector<T, Allocator>& vec ) {
        return cit == Vector<T, Allocator>::staticend() || cit == vec.cend();
    }

};


template< class T, class Allocator = std::allocator<T> >
inline bool equals( const typename Vector<T, Allocator>::const_iterator lhs
                  , const typename Vector<T, Allocator>::const_iterator rhs
) {
    if ( lhs != rhs ) {
        if ( Vector<T, Allocator>::is_end(lhs) ) return Vector<T, Allocator>::is_end(rhs);
        else return false;
    }
    return true;
}


/**
 * @brief This class makes maps containing maps more easy to use by providing an
 *      `MultiVector< T, Compare, SubVector, Allocator >::VectorIterator` that thus holds one iterator to the
 *      subvector per position
 * 
 * @tparam Key The key value's type, e.g. `std::string`; no const
 * @tparam T The type to save as elements of each position's key subvector for the `dscpp::Map< Key, T, Compare >`
 * @tparam Compare How to compare the elements on such things like sorting, merging and similar.
 *      Defaults to `std::less< Key >` and is optionally omittable
 * 
 * @note This object inherits `dscpp::Map< Key, Map< Key, T, Compare >*, Compare >`
 */
template< typename T, class Compare = details::Compare<T>, class Allocator = std::allocator<T> >
class SortableVector
    :   public Vector< T, Allocator >
{
public:
    typedef typename Compare compare;
    /** @brief The own type of the `MMap` */
    typedef Vector<T, Allocator> vector_t;

    SortableVector()
        :   vector_t()
    {}

    void swap( const const_iterator lhs, const const_iterator rhs ) {
        typename iterator lval = this->insert( lhs, *rhs );
        typename iterator rval = this->insert( rhs, *lhs );
        this->erase( lval + 1 );
        this->erase( rval + 1 );
    }

    void sort() {
        for ( typename const_iterator cit = this->begin(); cit != this->end(); cit++ ) {
            for ( typename const_iterator cit2 = this->end() - 1; cit2 != cit; cit2-- ) {
                if ( ((std::string) *cit) >= ((std::string) *cit2) ) this->swap( cit, cit2 );
            }
        }
    }
};


template< class T
        , class Compare = details::Compare<T>
        , class SubVector = dscpp::SortableVector< T, Compare >
        , class Allocator = std::allocator<T>
>
class MultiVector
    :   public dscpp::SortableVector< SubVector, Compare, Allocator >
{
    /** @brief The type of the subvectors stored at each key */
    typedef typename SubVector subvector_t;
    /** @brief The type of the map iterator */
    typedef typename SortableVector< SubVector, Compare, Allocator >::iterator vector_iterator_t;
    /** @brief The type of the subvector iterator */
    typedef typename SubVector::iterator subvector_iterator_t;


private:
    static inline std::unique_ptr<subvector_t> subvectorend;

public:
    static inline const subvector_t::const_iterator static_subvector_end() {
        if ( ! MultiVector< T, Compare, SubVector, Allocator >::subvectorend ) {
            MultiVector< T, Compare, SubVector, Allocator >::subvectorend
                        = std::unique_ptr< SubVector >( new subvector_t() );
        }
        return MultiVector< T, Compare, SubVector, Allocator >::subvectorend->cend();
    }

    static bool is_subvector_end( const typename subvector_t::const_iterator subvector_cit ) {
        return subvector_cit == MultiVector< T, Compare, SubVector, Allocator >::static_subvector_end();
    }

    /**
     * @brief The iterator of a `MultiVector< T, Compare, SubVector, Allocator >`. You can access the subvectors
     *      with `sub()`
     * @note Inherits `vector_iterator_t`
     */
    class VectorIterator
        :   public vector_iterator_t
    {
    private:
        const MultiVector< T, Compare, SubVector, Allocator >& vector;

    protected:
        /**
         * @brief The `subvector_iterator_t`, an iterator for the subvector at each position
         *      of this `MMap`
         */
        subvector_iterator_t subvector_it;

        subvector_iterator_t subvector_iterator( const vector_iterator_t mit ) {
            if ( MultiVector< T, Compare, SubVector, Allocator >::is_end(*this, this->vector) )
                return MultiVector< T, Compare, SubVector, Allocator >::static_subvector_end();
            return mit->begin();
        }

        void set_subvector_iterator( const vector_iterator_t mit ) {
            this->subvector_it = this->subvector_iterator( mit );
        }

    public:
        /**
         * @brief Constructor
         * @param pos The position to begin at
         * @param subpos The position to begin at inside of the `subvector_t` at this position.
         *          Defaults to `pos->second->begin()`.
         */
        VectorIterator( vector_iterator_t pos, subvector_iterator_t subpos
                      , const MultiVector< T, Compare, SubVector, Allocator >& vec )
            :   vector_iterator_t( pos )
            ,   vector( vec )
            ,   subvector_it( subpos )
        {}
        /**
         * @brief Constructor
         * @param pos The position to begin at
         * @param subpos The position to begin at inside of the `subvector_t` at this position.
         *          Defaults to `pos->second->begin()`.
         */
        VectorIterator( vector_iterator_t pos
                      , const MultiVector< T, Compare, SubVector, Allocator >& vec )
            :   vector_iterator_t( pos )
            ,   vector( vec )
            ,   subvector_it( this->subvector_iterator( *this ) )
        {}

        /**
         * @brief Dereference the `subvector_iterator_t` of the subvector at the current position
         *      of this instance's `VectorIterator`
         * @returns The current position of `this->subvector_it`
         */
        subvector_iterator_t operator~() {
            return this->subvector_it;
        }

        /**
         * @brief Dereference the `subvector_iterator_t` of the subvector at the current position
         *      of this instance's `VectorIterator`
         * @returns The current position of `this->subvector_it`
         */
        SubVector* sub() {
            if ( MultiVector< T, Compare, SubVector, Allocator >::is_end(*this, this->vector) )
                return NULL;
            return **this;
        }

        /**
         * @brief Alter the position of the `VectorIterator` to the next position behind the current
         *      element and set `this->subvector_it` to `(*this)->second->begin()`
         * @returns This instance of the `MMap< Key, T >::VectorIterator`
         */
        VectorIterator operator++() {
            vector_iterator_t::operator++();
            this->set_subvector_iterator();
            return *this;
        }
        /**
         * @brief Alter the position of the `VectorIterator` to the next position before the current
         *      element and set `this->subvector_it` to `(*this)->second->end()`
         * @returns This instance of the `MMap< Key, T >::VectorIterator`
         */
        VectorIterator operator--() {
            vector_iterator_t::operator--();
            this->set_subvector_iterator();
            return *this;
        }

        inline bool operator==( const VectorIterator another ) {
            if ( MultiVector< T, Compare, SubVector, Allocator >::is_end(another) ) {
                return MultiVector< T, Compare, SubVector, Allocator >::is_end(static_cast<vector_iterator_t>(this));
            } else {
                if ( another != static_cast<vector_iterator_t>(this) ) return false;
                return ~another == this->subvector_it;
            }
            return false;
        }
    };

    /** @brief The `stlvector_t` type of the base class */
    using stlvector_t = typename Vector< SubVector, Allocator >::stlvector_t;

    /**
     * @brief Get a new `VectorIterator` at the begin position of this `MultiVector< T, Compare, SubVector, Allocator >`
     */
    MultiVector< T, Compare, SubVector, Allocator >::VectorIterator begin() {
        return *new VectorIterator( vector_t::begin(), vector_t::begin()->begin() );
    }

    /**
     * @brief Get a new `VectorIterator` at the behind-the-last element's position of this
     *      `MultiVector< T, Compare, SubVector, Allocator >`
     */
    MultiVector< T, Compare, SubVector, Allocator >::VectorIterator end() {
        return *new VectorIterator( vector_t::end(), MultiVector< T, Compare, SubVector, Allocator >::static_subvector_end() );
    }

    subvector_iterator_t end_subvectors() const {
        return this->static_subvector_end();
    }
};


} // namespace dscpp


namespace std {

}

