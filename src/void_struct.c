
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

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

#include "void_struct.h"

#include <stddef.h>
#include <stdlib.h>

#include "datatype.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

struct _void_struct_* void_struct_init( const char* dt_name ) {
    struct _void_struct_* vs = (struct _void_struct_*) malloc(sizeof(struct _void_struct_));

    vs->datatype_name = dt_name;
    vs->vs = NULL;
    vs->toDict = &toDict;
    vs->fromDict = &fromDict;
    vs->castDatatype = &castDatatype;
    vs->castFrom = &castVoidStruct;

    return vs;
}

void* castVoidStruct( struct _void_struct_* voids ) {
    if ( voids->castDatatype == NULL ) 
        return NULL;
    return voids->castDatatype( voids->vs );
}

int castTo( void* data, int (*castFunctionForDatatype)(void*) ) {
    return castFunctionForDatatype(data);
}


struct _void_struct_* castFrom( int cls, struct _void_struct_* (castFunctionForDatatype)(int) ) {
    return castFunctionForDatatype(cls);
}

#ifdef __cplusplus
}

} // namespace dsc
#endif
