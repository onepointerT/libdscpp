/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_element.c
   @author  N. Devillard
   @brief   Implements a dictionary for string variables.

   This module implements a simple dictionary object, i.e. a list
   of string/string associations. This object is useful to store e.g.
   informations retrieved from a configuration file (ini files).
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
    dictionary_element de = { .npos = npos, .section = dictionary_key_getsec(key)
                            , .key = dictionary_key_getkey(key), .value = value };
    return &de;
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