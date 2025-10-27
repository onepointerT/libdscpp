
/*-------------------------------------------------------------------------*/
/**
   @file    dictionary.h
   @author  N. Devillard
   @brief   Parser for ini files.
*/
/*--------------------------------------------------------------------------*/

#ifndef _DICTIONARY_ELEMENT_H_
#define _DICTIONARY_ELEMENT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/


#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif


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

#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
