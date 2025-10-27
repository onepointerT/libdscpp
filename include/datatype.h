
/*-------------------------------------------------------------------------*/
/**
   @file    dictionary.h
   @author  N. Devillard
   @brief   Implements a dictionary for string variables.

   This module implements a simple dictionary object, i.e. a list
   of string/string associations. This object is useful to store e.g.
   informations retrieved from a configuration file (ds files).
*/
/*--------------------------------------------------------------------------*/

#ifndef _DATATYPE_H_
#define _DATATYPE_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

#include "void_struct.h"

#include <stdbool.h>
#include <stddef.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

struct _dataclass_;

typedef struct _datatype_ {
    const char* dt_name;
    void* vars;
    struct _void_struct_* vs;

    bool (*update)( struct _datatype_* dt );

    struct _datatype_* (*initCopy)( const struct _datatype_* other );
    struct _datatype_* (*initDatatype)( const struct _datatype_* other );
    struct _datatype_* (*init)( const struct _void_struct_* var_struct );

    bool (*copyFrom)( const struct _datatype_* other );
    bool (*fromDataclass)( const struct _dataclass_* some_other );
} datatype;

struct _datatype_* datatype_init( void* variables );

struct _datatype_* initCopy( const struct _datatype_* other );
struct _datatype_* initDatatype( const struct _datatype_* other );
struct _datatype_* initFromVoidStruct( const struct _void_struct_* variables );


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/


struct _datatype_* castFromVoid( const struct _void_struct_* vd );
struct _void_struct_* castToVoid( const struct _datatype_* dt );

bool copyFrom( const struct _datatype_* other );
bool fromDataclass( const struct _dataclass_* some_other );


#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
