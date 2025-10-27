
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

#include "datatype.h"

#include <stdlib.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/


struct _datatype_* datatype_init( void* variables ) {
    struct _datatype_* dt = (struct _datatype_*) malloc(sizeof(struct _datatype_));


    dt->update = NULL;
    dt->copyFrom = &copyFrom;
    dt->fromDataclass = &fromDataclass;
    dt->init = &initFromVoidStruct;
    dt->initCopy = &initCopy;
    dt->initDatatype = &initDatatype;

    dt->vars = variables;

    return dt;
}

struct _datatype_* initCopy( const struct _datatype_* other ) {

}

struct _datatype_* initDatatype( const struct _datatype_* other ) {

}

struct _datatype_* initFromVoidStruct( const struct _void_struct_* vd ) {

}

struct _datatype_* castFromVoid( const struct _void_struct_* vd ) {
    return initFromVoidStruct( vd );
}

struct _void_struct_* castToVoid( const struct _datatype_* dt ) {
    struct _void_struct_* vd = void_struct_init(dt->dt_name);
    vd->vs = dt->vars;
    return vd;
}

bool copyFrom( const struct _datatype_* other ) {

}

bool fromDataclass( const struct _dataclass_* some_other ) {

}

#ifdef __cplusplus
}

} // namespace dsc
#endif
