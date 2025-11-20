/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_element.c
   @author  N. Devillard
   @brief   The `struct _dictionary_` element-wise.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "dictionary_element.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dictionary.h"
#include "dictionary_compat.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/
dictionary_element* dictionary_elem_new( const char* key, const char* value, const unsigned int npos ) {
    struct _dictionary_element_* de = (struct _dictionary_element_*) malloc(sizeof(struct _dictionary_element_));

    de->npos = npos;
    de->section = dictionary_key_getsec(key);
    de->key = dictionary_key_getkey(key);
    de->value = value;
    
    return de;
}

/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
dictionary_element* dictionary_elem_get(const dictionary * d, const char * key, const char * def) {
    const char* value = dictionary_getstring( d, key, def );
    return dictionary_elem_new( key, value, dictionary_key_getnpos(d, key) );
}

/*--------------------------------------------------------------------------*/
dictionary_element* dictionary_elem_getpos(const dictionary * d, const unsigned int npos, const char * def) {
    if ( npos >= d->n ) return NULL;
    return dictionary_elem_new( d->key[npos], d->val[npos], npos );
}

/*--------------------------------------------------------------------------*/
const unsigned int dictionary_elem_getnpos( const dictionary * d, const char* section, const char* key ) {
    const char* keystr = dictionary_key_make(section, key);
    for ( unsigned int dn = 0; dn < d->n; dn++ ) {
        if ( strcmp( d->key[dn], keystr ) == 0 ) return dn;
    }
    return d->size;
}

/*--------------------------------------------------------------------------*/
bool dictionary_elem_set( dictionary * d, const dictionary_element* elem ) {
    const char* keystr = dictionary_key_make( elem->section, elem->key );
    const unsigned int npos = dictionary_elem_getnpos( d, elem->section, elem->key );
    if ( npos == d->size && d->size >= d->n )
        return 0 == dictionary_set( d, keystr, elem->value );
    else if ( npos < d->n )
        return 0 == dictionary_set( d, keystr, elem->value );
    else return false;
}