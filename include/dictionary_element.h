
/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_element.h
   @author  N. Devillard
   @brief   The `struct _dictionary_` element-wise.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _DICTIONARY_ELEMENT_H_
#define _DICTIONARY_ELEMENT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef struct _dictionary_element_ {
   unsigned int      npos;    /* Position in the dictionary (the index) */
   const char*       section;
   const char*       key;
   const char*       value;
} dictionary_element;



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/
struct _dictionary_;
typedef struct _dictionary_ dictionary;

/*-------------------------------------------------------------------------*/
/**
  @brief    Get a value from a dictionary.
  @param    d       dictionary object to search.
  @param    key     Key to look for in the dictionary.
  @param    def     Default value to return if key not found.
  @return   1 pointer to internally allocated character string.

  This function locates a key in a dictionary and returns a pointer to its
  value, or the passed 'def' pointer if no such key can be found in
  dictionary. The returned character pointer points to data internal to the
  dictionary object, you should not try to free it or modify it.
 */
/*--------------------------------------------------------------------------*/
dictionary_element* dictionary_elem_get(const dictionary * d, const char * key, const char * def);
dictionary_element* dictionary_elem_getpos(const dictionary * d, const unsigned int npos, const char * def);

const unsigned int dictionary_elem_getnpos( const dictionary * d, const char* section, const char* key );

bool dictionary_elem_set( dictionary * d, const dictionary_element * elem );

#ifdef __cplusplus
}
#endif

#endif
