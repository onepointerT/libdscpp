/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_iterator.c
   @author  N. Devillard
   @brief   Implements the iterator for `struct _dictionary_`.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/
#include "dictionary_iterator.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "cutils.h"
#include "dictionary.h"
#include "dictionary_compat.h"


/*---------------------------------------------------------------------------
                            Private functions
 ---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------
                            Function codes
 ---------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
struct _dictionary_iterator_* _dictionary_iterator_new( struct _dictionary_* dict ) {
    struct _dictionary_iterator_* di = (struct _dictionary_iterator_*)
                                            malloc(sizeof(struct _dictionary_iterator_));
    
    di->dict = dict;
    di->elem = NULL;
    di->pos = di->dict->n;

    return di;
}

/*-------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_next(dictionary_iterator* di) {
    if ( di->pos == di->dict->n ) di->pos = 0;

    di->elem = di->pos + 1 < di->dict->n ? dictionary_elem_getpos( di->dict, di->pos + 1, "" ) : NULL;
    if ( di->elem == NULL ) di->pos = di->dict->n;
    else ++di->pos;
    return di;
}

/*-------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_previous(dictionary_iterator* di) {
    if ( di->pos == di->dict->n ) di->pos = di->dict->n - 1;

    di->elem = di->pos - 1 >= 0 ? dictionary_elem_getpos( di->dict, di->pos - 1, "" ) : NULL;
    if ( di->elem == NULL ) di->pos = di->dict->n;
    else --di->pos;
    return di;
}

/*-------------------------------------------------------------------------*/
bool dictionary_iterator_apply(dictionary_iterator* di) {
    if ( di->pos == di->dict->n || di->elem == NULL ) return false;
    strcpy( di->dict->key[di->pos], strconcat( strconcat( di->elem->section, ":" ), di->elem->key ) );
    strcpy( di->dict->val[di->pos], di->elem->value );
    return true;
}

/*-------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_load(const char* key, struct _dictionary_* dict) {
    size_t kpos = dictionary_key_getnpos( dict, key );
    if ( kpos == dict->n ) return NULL;
    return dictionary_iterator_load_npos( kpos, dict );
}

/*-------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_load_npos(const size_t npos, struct _dictionary_* dict) {
    if ( npos >= dict->n ) return NULL;

    dictionary_iterator* di = _dictionary_iterator_new( dict );
    di->pos = npos;
    di->elem = dictionary_elem_getpos( dict, npos, "" );

    return di;
}

/*-------------------------------------------------------------------------*/
void dictionary_iterator_free(dictionary_iterator * di) {
    di->dict = NULL;
    di->elem = NULL;
    di->pos = 0;
    free(di);
}