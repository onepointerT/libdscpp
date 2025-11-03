
/*-------------------------------------------------------------------------*/
/**
   @file    void_struct.c
   @author  N. Devillard
   @brief   Implements a basic void struct with compliance casting.

   This module implements a basic void pointer struct with datatype naming
   for further use on difficult-to-predict generic data formats on a lower
   backend api that thus can be casted to own datatypes.
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
#include <string.h>

#include "castcompat.h"
#include "datacast.h"
#include "datatype.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

struct _void_struct_* void_struct_init( const char* dt_name, const enum _void_struct_ptr_type_ ptr_type ) {
    struct _void_struct_* vs = (struct _void_struct_*) malloc(sizeof(struct _void_struct_));

    memcpy( vs->datatype_name, dt_name, sizeof(char)*strlen(dt_name) );
    vs->vs = NULL;
    vs->toDict = &toDict;
    vs->fromDict = &fromDict;
    vs->castDatatype = &castDatatype;
    vs->castFrom = &castVoidStruct;

    vs->vs_type = ptr_type;

    return vs;
}


/* TODO
struct _void_struct_* void_struct_init_from_datacast( struct _void_struct_* vs, const struct _datacast_* dc )  {
    if ( vs == NULL || dc == NULL ) return NULL;
    else if ( strcmp( vs->datatype_name, dc->datatype_name ) != 0 ) return NULL;

    vs->castDatatype = 
    vs->fromDict

    return vs;
}
*/


struct _void_struct_* void_struct_duplicate( struct _void_struct_* vs ) {
    if ( vs == NULL ) return NULL;

    struct _void_struct_* vs_new = (struct _void_struct_*) malloc(sizeof(struct _void_struct_));
    
    strcpy( vs_new->datatype_name, vs->datatype_name );
    vs_new->vs = vs->vs;
    vs_new->vs_type = vs->vs_type;
    vs_new->toDict = vs->toDict;
    vs_new->fromDict = vs->fromDict;
    vs_new->castDatatype = vs->castDatatype;
    vs_new->castFrom = vs->castFrom;

    return vs_new;
}

void* castVoidStruct( struct _void_struct_* voids ) {
    if ( voids == NULL ) return NULL;
    else if ( strcmp( voids->datatype_name, "" ) == 0 )
        return toVoidPointer( voids );
    else if ( voids->castFrom != NULL )
        return voids->castFrom( voids );
    
    datacast* dc = dc_functions_get_datacast( voids->datatype_name );
    if ( dc == NULL ) return castDatatype( voids->vs, voids->datatype_name );

    return dc->fromVS( voids );
}


struct _void_struct_* castVoidStructPtr( void* void_ptr, const char* datatype_name ) {
    datacast* dc = dc_functions_get_datacast( datatype_name );
    if ( dc != NULL ) return dc->toVS( void_ptr, datatype_name );
    return fromVoidPointer( void_ptr, datatype_name );
}

struct _void_struct_* castToVoidStruct( void* data, const char* datatype_name
                            , struct _void_struct_* (*castFunctionForDatatype)(void*, const char*) ) {
    if ( castFunctionForDatatype != NULL )
        return castFunctionForDatatype(data, datatype_name);
    else {
        struct _void_struct_* vs = castDatatype( data, datatype_name );
        if ( vs != NULL ) return vs;
    }

    struct _void_struct_* vs = void_struct_init( datatype_name, ORIGINAL );
    vs->vs = data;
    
    return vs;
}

void* castFromVoidStruct( struct _datatype_* dt, void* (castFunctionForDatatype)(struct _void_struct_*) ) {
    struct _void_struct_* vs = NULL;

    if ( dt == NULL ) return NULL;
    else if ( dt->vs == NULL ) {
        datacast* dc = dc_functions_get_datacast( dt->dt_name );
        if ( dc != NULL )
            vs = dc->toVS( dt->vars, dt->dt_name );
        else {
            vs = void_struct_init( dt->dt_name, ORIGINAL );
            vs->vs = dt->vars;
        }
    } else if ( dt->vs != NULL ) vs = void_struct_duplicate( dt->vs );
    else if ( dt->vars == 0 ) {
        vs = void_struct_init( dt->dt_name, DATATYPE );
        vs->vs = dt;
    } else {
        vs = void_struct_init( dt->dt_name, DICTIONARY );
        if ( dt->toDict != NULL ) vs->vs = dt->toDict(dt);
        else vs = datatype_castToVoid(dt);
    }

    return castFunctionForDatatype(vs);
}

#ifdef __cplusplus
}

} // namespace dsc
#endif
