/**
 * @file ini.hpp
 * @brief A file that defines *.ini dictionaries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibIniC++: A C++/C library for *.ini files and dictionaries.
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/


#include "cdictionary.hpp"

extern "C" {
#include "dictionary_compat.h"
#include "dictionary_element.h"
#include "dictionary_iterator.h"
}


namespace dsc {


DictionaryC::DictionaryC( struct _dictionary_* cdict )
    :   dscpp::Dictionary( *new dscpp::Dictionary() )
    ,   _dictionary_( *dictionary_new(cdict->size) )
{
    this->update( cdict );
}

bool DictionaryC::update( struct _dictionary_* cdict ) {
    for ( dictionary_iterator* dit = dictionary_iterator_load_npos(0, cdict)
        ; dit != NULL && dit->pos != cdict->n
        ; dit = dictionary_iterator_next(dit)
    ) {
        this->update( dit->elem );
    }
    
    return true;
}

bool DictionaryC::update( const struct _dictionary_element_* cdict_elem ) {
    if ( ! this->contains(cdict_elem->section) ) {
        (*this)[cdict_elem->section] = new Section( *new kmap_t, cdict_elem->section );
    }

    (*((*this)[cdict_elem->section]))[cdict_elem->key]
                    = new dscpp::DictionaryKey( cdict_elem->key, cdict_elem->value );

    return true;
}

DictionaryC& DictionaryC::operator<<( struct _dictionary_* cdict ) {
    for ( dictionary_iterator* dit = dictionary_iterator_load_npos(0, cdict)
        ; dit->pos < cdict->n
        ; dit = dictionary_iterator_next(dit)
    ) {
        this->update( dit->elem );
    }
    return *this;
}


DictionaryC& DictionaryC::operator<<( const struct _dictionary_element_* cdict_elem ) {
    this->update( cdict_elem );
    return *this;
}


} // namespace dsc
