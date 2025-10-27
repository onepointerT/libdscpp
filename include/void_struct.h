
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

#ifndef _VOID_STRUCT_H_
#define _VOID_STRUCT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif


#include <stdint.h>


struct _datatype_;
typedef struct _dictionary_ dictionary;

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef struct _void_struct_ {
    const char* datatype_name;
    void* vs;

    dictionary* (*toDict)( const struct _void_struct_* data );
    struct _void_struct_* (*fromDict)( const dictionary* dict );

    struct _void_struct_* (*castDatatype)( void* data );
    void* (*castFrom)( struct _void_struct_* data );
} void_struct;


struct _void_struct_* void_struct_init( const char* dt_name );
struct _void_struct_* void_struct_init_from_datacast( const struct _datacast_* dc );



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/


void* castVoidStruct( struct _void_struct_* voids );

struct _void_struct_* castToVS( void* data, struct _void_struct_* (*castFunctionForDatatype)(void*) );

void* castFromVS( struct _datatype_* dt, void* (castFunctionForDatatype)(struct _void_struct_*) );

struct _void_struct_* castDatatype( void* data );

extern struct _void_struct_* fromDict( const struct _dictionary_* dict );
extern struct _dictionary_* toDict( const struct _void_struct_* vd );

#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
