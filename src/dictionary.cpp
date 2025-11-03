/**
 * @file ini.hpp
 * @brief A file that defines *.ini dictionaries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibIniC++: A C++/C library for *.ini files and dictionaries.
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/


#include "dictionary.hpp"

extern "C" {

}


namespace dscpp {


DictionaryKey::DictionaryKey( const char* key, const char* value )
    :   std::string_view( value )
    ,   key( key )
{}


Dictionary::Section::Section( kmap_t& section_map, const char* secname )
    :   kmap_t( section_map )
    ,   section_name( secname )
{}

const std::vector< std::string >& Dictionary::Section::keys() {
    std::vector< std::string >* keyvec
                = new std::vector< std::string >();

    for ( Section::const_iterator sit : { this->cbegin(), this->cend() } ) {
        keyvec->emplace_back( sit->first );
    }

    return *keyvec;
}

Dictionary::Section& Dictionary::Section::operator<<( DictionaryKey& key ) {
    (*this)[key.key] = &key;
    return *this;
}

Dictionary::Section& Dictionary::Section::operator<<( std::pair< std::string, std::string > kv_pair ) {
    return ((*this) << *new DictionaryKey(kv_pair.first.c_str(), kv_pair.second.c_str()));
}


bool Dictionary::Section::contains( const std::string key_name ) const {
    for ( typename Dictionary::Section::const_iterator sit = this->cbegin()
        ; sit != this->cend(); ++sit
    ) {
        if ( sit->first.compare(key_name) == 0 ) return true;
    }
    return false;
}


DictionaryKey& Dictionary::Section::operator()( const std::string key_name ) {
    if ( ! this->contains(key_name) ) {
        (*this) << std::pair{ key_name, "" };
    }
    return *((*this)[key_name]);
}


Dictionary::DictionaryIterator::DictionaryIterator( MapIterator mapit )
    :   MapIterator( mapit )
{}

Dictionary::Section& Dictionary::DictionaryIterator::section() {
    return *new Dictionary::Section( *((*this)->second), (*this)->first.c_str() );
}


const Dictionary::Section& Dictionary::DictionaryIterator::section() const {
    return *new Dictionary::Section( *((*this)->second), (*this)->first.c_str() );
}


bool Dictionary::DictionaryIterator::apply( const Dictionary::Section& section_update ) {
    if ( section_update.section_name != (*this)->first ) return false;

    for ( Section::const_iterator secit = section_update.cbegin()
        ; secit != section_update.cend(); secit++
    ) {
        DictionaryKey* dk = (*secit).second;

        for ( submap_iterator_t smit = (*this)->second->begin()
            ; smit != (*this)->second->end(); ++smit
        ) {

            if ( smit->first == dk->key ) {
                if ( *(smit->second) != *dk )
                    smit->second = dk;
            }
        }
    }

    return true;
}


Dictionary::DictionaryIterator Dictionary::DictionaryIterator::operator++() {
    MapIterator::operator++();
    return *this;
}

Dictionary::DictionaryIterator Dictionary::DictionaryIterator::operator--() {
    MapIterator::operator--();
    return *this;
}


Dictionary::Dictionary()
    :   dscpp::MMap< std::string, DictionaryKey* >( *new dscpp::MMap< std::string, DictionaryKey* >() )
{}

const std::vector< std::string >& Dictionary::section_keys() {
    std::vector< std::string >* skvec
            = new std::vector< std::string >();

    for ( typename Dictionary::iterator sit = this->begin()
        ; sit != this->end()
        ; ++sit
    ) {
        skvec->push_back( sit->first );
    }

    return *skvec;
}

Dictionary::Section& Dictionary::section( const char* section_name ) {
    for ( typename Dictionary::DictionaryIterator sit = this->begin()
        ; sit != this->end()
        ; ++sit
    ) {
        if ( sit->first.compare(section_name) == 0 ) return sit.section();
    }

    (*this)[section_name] = new dscpp::Map< std::string, DictionaryKey* >();
    return *new Dictionary::Section( *((*this)[section_name]), section_name );
}

bool Dictionary::apply( const Section& section ) {
    kmap_t* submap = (*this)[section.section_name];
    if ( submap == NULL ) {
        (*this)[section.section_name] = new kmap_t();
        submap = (*this)[section.section_name];
    }

    for ( typename Section::const_iterator sit = section.cbegin()
        ; sit != section.cend(); ++sit
    ) {
        if ( ! submap->contains(sit->first) ) {
            (*submap)[sit->first] = sit->second;
        } else {
            DictionaryKey* k = sit->second;
            if ( *k != *((*submap)[sit->first]) ) (*submap)[sit->first] = k;
        }
    }

    return true;
}

typename Dictionary::DictionaryIterator Dictionary::begin() {
    return *new Dictionary::DictionaryIterator( dscpp::MMap< std::string, DictionaryKey* >::begin() );
}

typename Dictionary::DictionaryIterator Dictionary::end() {
    return *new Dictionary::DictionaryIterator( dscpp::MMap< std::string, DictionaryKey* >::end() );
}

bool Dictionary::apply( const typename Dictionary::DictionaryIterator& it ) {
    return this->apply( *new Section( *(it->second), it->first.c_str()) );
}

dscpp::MMap< std::string, DictionaryKey* > Dictionary::to_stl() const {
    return *this;
}

} // namespace dscpp
