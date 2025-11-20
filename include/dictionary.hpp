/**
 * @file dictionary.hpp
 * @brief A file that defines dictionaries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {
#include "dictionary.h"
}

#include "cppmap.hpp"

#include <string>
#include <string_view>
#include <utility>
#include <vector>


namespace dscpp {


/**
 * @brief A class that implements the (value, key)-pair of a dictionary.
 * @note The default inherited `std::string_view` represents the value
 *      that is ordered to a key of the dictionary
 */
class DictionaryKey
    :   public std::string_view
{
public:
    /** @brief The key of the value */
    const std::string key;

    /**
     * @brief Constructor
     * @param key The key of the value
     * @param value The value itself
     */
    DictionaryKey( const char* key, const char* value );
};


/**
 * @brief This class implements a dictionary with sections
 * @note Inherits `dscpp::MMap< std::string, DictionaryKey* >`
 */
class Dictionary
    :   public dscpp::MMap< std::string, DictionaryKey* >
{
public:
    /** @brief The submap of the dictionary (the section map) */
    typedef typename dscpp::Map< std::string, DictionaryKey* > kmap_t;

    /**
     * @brief This class implements the section of a dictionary and contains
     *      pointers to `DictionaryKey`s ordered to a key
     * @note Inherits `Dictionary::kmap_t`
     */
    class Section
        :   public kmap_t
    {
    public:
        /** @brief The name of this section */
        const std::string section_name;

        /**
         * @brief Constructor
         * @param section_map A pointer to this section's map
         * @param secname The name of this section
         */
        Section( kmap_t& section_map, const char* secname );

        /**
         * @brief Get the key names of all key of this dictionary section
         * @returns A reference to a `std::vector< std::string >` with all keys
         *      contained
         */
        const std::vector< std::string >& keys();

        /**
         * @brief Add a `dscpp::DictionaryKey` to this section
         * @param key A reference to a valid `DictionaryKey` that is to be
         *      added to this `Section`.
         * @returns A reference to `*this`
         * @note You may apply updated sections with `Dictionary::apply()`
         */
        Section& operator<<( DictionaryKey& key );
        /**
         * @brief Add a `dscpp::DictionaryKey` to this section
         * @param kv_pair A (key, value)-`std::pair` that is to be added to this `Section`.
         * @returns A reference to `*this`
         * @note You may apply updated sections with `Dictionary::apply()`
         */
        Section& operator<<( std::pair< std::string, std::string > kv_pair );

        /**
         * @brief Test, if a key is contained in this section
         * @param key_name The key to lookup
         * @returns True, if the key was found in this section
         */
        bool contains( const std::string key_name ) const;

        /**
         * @brief Get a `DictionaryKey` by its name
         * @param key_name The key to lookup
         * @returns A reference to the `dscpp::DictionaryKey` or, if
         *      `! this->contains(key_name)`, a newly created reference to
         *      a `DictionaryKey` of this `Section`
         */
        DictionaryKey& operator()( const std::string key_name );
    };

    /**
     * @brief Constructor
     */
    Dictionary();

    /**
     * @brief Get the key names of all sections of this dictionary
     * @returns A reference to a `std::vector< std::string >` with all section keys
     *      contained
     */
    const std::vector< std::string >& section_keys();

    /**
     * @brief Get a section inside of this `Dictionary` instance
     * @param section_name The name of the section
     * @returns A reference to a `Dictionary::Section` that can be applied
     *      on update with `Dictionary::apply`
     */
    Section& section( const char* section_name );
    /**
     * @brief Apply an updated section to this instance of `Dictionary`
     * @param section The reference to the updated `Dictionary::Section`
     * @returns True on success
     */
    bool apply( const Section& section );

    /**
     * @brief This is basically a `MMap< std::string, DictionaryKey* >::MapIterator`
     *      with a few additional specialized features and attributes
     * @note Inherits `dscpp::MMap< std::string, DictionaryKey* >::MapIterator`
     */
    class DictionaryIterator
        :   public dscpp::MMap< std::string, DictionaryKey* >::MapIterator
    {
    protected:
        /** @brief The type of the derived `MapIterator` */
        typedef typename dscpp::MMap< std::string, DictionaryKey* >::MapIterator map_it_t;

        /**
         * @brief Constructor
         * @param mapit The `MapIterator` as gotten by `MMap::begin()` and `MMap::end()`
         */
        DictionaryIterator( MapIterator mapit );

        friend class Dictionary;

    public:
        /**
         * @brief Get the current position as `Dictionary::Section`
         * @returns A reference to the `Dictionary::Section` of the current position of
         *      this `DictionaryIterator`
         */
        Dictionary::Section& section();
        /**
         * @brief Get the current position as `Dictionary::Section`
         * @returns A reference to the `Dictionary::Section` of the current position of
         *      this `DictionaryIterator`
         */
        const Dictionary::Section& section() const;
        /**
         * @brief Apply an updated `Dictionary::Section` to this instance of `DictionaryIterator`
         * @param it The reference to the updated `Dictionary::Section`
         * @returns True on success
         */
        bool apply( const Dictionary::Section& section_update );

        /**
         * @brief Alter the position of the `DictionaryIterator` to the next position behind the current
         *      element and set `this->submap_it` to `(*this)->second->begin()`
         * @returns This instance of the `Dictionary::DictionaryIterator`
         */
        DictionaryIterator operator++();
        /**
         * @brief Alter the position of the `DictionaryIterator` to the previous position before the current
         *      element and set `this->submap_it` to `(*this)->second->begin()`
         * @returns This instance of the `Dictionary::DictionaryIterator`
         */
        DictionaryIterator operator--();
        
        using map_it_t::sub;
    };

    /**
     * @brief Get a new `DictionaryIterator` at the begin position of this `Dictionary`
     */
    DictionaryIterator begin();
    /**
     * @brief Get a new `DictionaryIterator` at the behind-the-last element's position of this
     *      `Dictionary`
     */
    DictionaryIterator end();
    /**
     * @brief Apply an updated `DictionaryIterator` to this instance of `Dictionary`
     * @param it The reference to the updated `DictionaryIterator`
     * @returns True on success
     */
    bool apply( const DictionaryIterator& it );

    /**
     * @brief Transform this dictionary into an standard template library map
     * @returns A copy of `*this`.
     */
    dscpp::MMap< std::string, DictionaryKey* > to_stl() const;
};



} // namespace dscpp
