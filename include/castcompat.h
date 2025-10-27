
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

#ifndef _CASTCOMPAT_H_
#define _CASTCOMPAT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "datacast.h"

#include <stdint.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

extern void* castTo( _datatype_* dt );

struct _datatype_* castTypeFromVS( const _void_struct_* vs );
struct _void_struct_* castVSFromType( const _datatype_* vs );

#ifdef __cplusplus
}
#endif

#endif
