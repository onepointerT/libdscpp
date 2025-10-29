
/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_iterator.h
   @author  N. Devillard
   @brief   An iterator for the `struct _dictionary_`
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
namespace dsc {

extern "C" {
#endif

#include "dictionary_element.h"

#include <stdbool.h>
#include <stdint.h>


struct _dictionary_;

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef struct _dictionary_iterator_ {
  struct _dictionary_element_* elem;
  unsigned int pos;
  struct _dictionary_* dict;
} dictionary_iterator;

struct _dictionary_iterator_* _dictionary_iterator_new();

/*-------------------------------------------------------------------------*/
/**
  @brief    Parse an ini file and return an allocated dictionary object
  @param    ininame Name of the ini file to read.
  @return   Pointer to newly allocated dictionary
 */
/*--------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_plus(dictionary_iterator* di);
dictionary_iterator* dictionary_iterator_minus(dictionary_iterator* di);

/*-------------------------------------------------------------------------*/
/**
  @brief    Parse an ini file and return an allocated dictionary object
  @param    ininame Name of the ini file to read.
  @return   Pointer to newly allocated dictionary
 */
/*--------------------------------------------------------------------------*/
bool dictionary_iterator_apply(dictionary_iterator* di);


/*-------------------------------------------------------------------------*/
/**
  @brief    Parse an ini file and return an allocated dictionary object
  @param    ininame Name of the ini file to read.
  @return   Pointer to newly allocated dictionary
 */
/*--------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_load(const char* key);

/*-------------------------------------------------------------------------*/
/**
  @brief    Parse an ini file and return an allocated dictionary object
  @param    ininame Name of the ini file to read.
  @return   Pointer to newly allocated dictionary
 */
/*--------------------------------------------------------------------------*/
dictionary_iterator* dictionary_iterator_load_npos(const size_t* npos);

/*-------------------------------------------------------------------------*/
/**
  @brief    Free all memory associated to an ini dictionary
  @param    d Dictionary to free

  Free all memory associated to an ini dictionary.
  It is mandatory to call this function before the dictionary object
  gets out of the current context.
 */
/*--------------------------------------------------------------------------*/
void dictionary_iterator_free(dictionary_iterator * di);

#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
