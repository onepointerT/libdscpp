
/*-------------------------------------------------------------------------*/
/**
   @file    void_struct.h
   @author  N. Devillard
   @brief   Implements a dictionary for string variables.

   This module implements a simple dictionary object, i.e. a list
   of string/string associations. This object is useful to store e.g.
   informations retrieved from a configuration file (ds files).
*/
/*--------------------------------------------------------------------------*/

#ifndef _CUTILS_H_
#define _CUTILS_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/





/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/
size_t strfindpos( const char* _Str1, const char* StrFind, const size_t pos_start, const size_t pos_end );
size_t strfindpossimple( const char* _Str1, const char* StrFind );
const char* strsubstr( const char* _Str1, const size_t pos_start, const size_t pos_end );


#ifdef __cplusplus
}
#endif

#endif
