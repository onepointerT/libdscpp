
/*-------------------------------------------------------------------------*/
/**
   @file    datatype.c
   @author  N. Devillard
   @brief   Implements the general data type of `libdsC`

   This module implements a simple generic data type object, since data is
   provided in many different ways, structs, classes and read-methods.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

#include "datatype.h"

#include <stdlib.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


struct _datatype_* datatype_init( void* variables, const char* datatype_name ) {
    struct _datatype_* dt = (struct _datatype_*) malloc(sizeof(struct _datatype_));

    dt->dt_name = datatype_name;

    dt->update = &update;
    dt->copyFrom = &datatype_copyFrom;
    dt->fromDataclass = &datatype_fromDataclass;
    dt->init = &datatype_initFromVoidStruct;
    dt->initCopy = &datatype_initCopy;
    dt->initDatatype = &datatype_initDatatype;

    dt->vars = variables;

    return dt;
}

struct _datatype_* datatype_initCopy( const struct _datatype_* other ) {
    struct _datatype_* dt = (struct _datatype_*) malloc(sizeof(struct _datatype_));
    if ( copyFrom(dt, other) ) return dt;
    return NULL;
}

struct _datatype_* datatype_initDatatype( const struct _datatype_* other ) {
    return datatype_init( other->vars, other->dt_name );
}

struct _datatype_* datatype_initFromVoidStruct( const struct _void_struct_* vd ) {
    struct _datatype_* dt = (struct _datatype_*) malloc(sizeof(struct _datatype_));
    return datatype_castFromVoid( vd );
}

struct _void_struct_* datatype_castToVoid( const struct _datatype_* dt ) {
    struct _void_struct_* vd = void_struct_init(dt->dt_name, ORIGINAL);
    vd->vs = dt->vars;
    return vd;
}

#ifdef __cplusplus
}

} // namespace dsc
#endif
