
/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_iterator.h
   @author  N. Devillard
   @brief   Implements the iterator for `struct _dictionary_`.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _DICTIONARY_ITERATOR_H_
#define _DICTIONARY_ITERATOR_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "dictionary_element.h"

#include <stdbool.h>
#include <stdint.h>


struct _dictionary_;

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/**
 * @brief The iterator for `struct _dictionary_`. Compliance use functions below.
 */
typedef struct _dictionary_iterator_ {
  /** @brief The current `dictionary_element` pointer */
  struct _dictionary_element_* elem;
  /** @brief The iterator's current position */
  unsigned int pos;
  /** @brief The dictionary, the iterator iterates over. */
  struct _dictionary_* dict;
} dictionary_iterator;

/**
 * @brief Create a new unpositioned iterator for a dictionary `dict`
 * @param dict The `dictionary` to create the iterator for.
 * @returns A newly-allocated `dictionary_iterator*`, with unset element and unknown position
 * @note You may call `dictionary_iterator_load_npos()` or `dictionary_iterator_load()`
 *      for initially creating iterators
 */
struct _dictionary_iterator_* _dictionary_iterator_new( struct _dictionary_* dict );

/*-------------------------------------------------------------------------*/
/**
  @brief    Set the iterator to its' next element.
  @param    di The iterator to get it's next element of
  @returns  Pointer to the updated iterator
 */
dictionary_iterator* dictionary_iterator_next(dictionary_iterator* di);
/**
  @brief    Set the iterator to its' previous element.
  @param    di The iterator to get it's previous element of
  @returns  Pointer to the updated iterator
 */
dictionary_iterator* dictionary_iterator_previous(dictionary_iterator* di);

/*-------------------------------------------------------------------------*/
/**
  @brief    Apply the values of `di->elem` to the dictionary `di->dict`.
  @param    di The iterator to apply
  @returns  True on success
 */
bool dictionary_iterator_apply(dictionary_iterator* di);


/*-------------------------------------------------------------------------*/
/**
  @brief    Load a key of a dictionary `dict` to a new instance of `dictionary_iterator*`
  @param    key The key to lookup
  @param    dict The dictionary to lookup in
  @returns  A newly allocated iterator with `strcmp( di->elem->key, key ) == 0` on success, `NULL` otherwise.
 */
dictionary_iterator* dictionary_iterator_load(const char* key, struct _dictionary_* dict);

/*-------------------------------------------------------------------------*/
/**
  @brief    Load a positiona of a dictionary `dict` to a new instance of `dictionary_iterator*`
  @param    npos The position to lookup
  @param    dict The dictionary to lookup in
  @returns  A newly allocated iterator with `di->npos == npos` on success, `NULL` otherwise.
 */
dictionary_iterator* dictionary_iterator_load_npos(const size_t npos, struct _dictionary_* dict);

/*-------------------------------------------------------------------------*/
/**
  @brief    Free all memory associated to an `dictionary_iterator`
  @param    di Dictionary iterator to free

  Free all memory associated to an `dictionary_iterator*`.
  It is mandatory to call this function before the dictionary object
  gets out of the current context.
 */
/*--------------------------------------------------------------------------*/
void dictionary_iterator_free(dictionary_iterator * di);

#ifdef __cplusplus
}
#endif

#endif
