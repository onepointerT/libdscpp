
/*-------------------------------------------------------------------------*/
/**
   @file    datatype_extern.c
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
extern "C" {
#endif

#include "datatype.h"

#include <string.h>

// #include <yourDCL.h>  // Your data creation/constructing library here
// #include <yourDTL.h>  // Your data template library include here

#include "datacast.h"
#include "dataclass.h"


/**
 * Some private functions
 */




/*---------------------------------------------------------------------------
                            Extern functions
                          !! PLEASE DEFINE !!
 ---------------------------------------------------------------------------*/
/**
 * @brief Update the datatype `dt` from a dictionary `dict`
 * @param dt The `datatype*` to update from `dict`
 * @param dict An non-empty `dictionary*` with updates for the datatype `dt`
 * @return True on success.
 * @note Points to `NULL` by default, because it is really your higher-end libraries
 *      definit task to define, how to update your datastructures from a
 *      (key, value)-paired dictionary.
 */
bool update( struct _datatype_* dt, const struct _dictionary_* dict ) {
    // DO Something here !
    if ( strcmp( dt->dt_name, "SomeYourType" ) == 0 ) {
        /* struct _C* c = (C*) dt->vars; */
        /* SOMETHING */
    }
    else return false;
}
/**
 * @brief Cast a `datatype dt` from a backend and API-independently compatible `void_struct`
 * @param vd The pointer to the `void_struct` data type to transform (data at `vd->vs`!)
 * @returns A pointer to a `datatype` on success, `NULL` otherwise
 */
struct _datatype_* datatype_castFromVoid( const struct _void_struct_* vd ) {
    // DO something here, like
    if ( vd->vs_type == DATATYPE ) return (datatype*) vd->vs;
    else if ( vd->vs_type == ORIGINAL ) return datatype_init( vd->vs, vd->datatype_name );
    // TODO: More things.
    else return NULL;
}
/**
 * @brief Update an instance of a `datatype` by copying another
 * @param self The pointer to a `datatype` to copy the data from `other` to
 * @param other The pointer to a `datatype` that is to be copied
 * @returns True on success
 */
bool datatype_copyFrom( struct _datatype_* self, const struct _datatype_* other ) {
    // Do however some struct copy `other -> self` or `other->self.update`
    // e.g.
    datacast* dc = dc_functions_get_datacast( self->dt_name );
    if ( dc == NULL ) return false;
    return self->update( self, dc->toDictDT(other) );
}
/**
 * @brief Update an instance of a `datatype` by transforming from a `dataclass` struct
 * @param self The pointer to a `datatype` to copy the data from `some_other` to
 * @param other The pointer to a `struct _dataclass_` that is to be copied
 * @returns True on success
 */
bool datatype_fromDataclass( struct _datatype_* self, const struct _dataclass_* some_other ) {
    // Do tranform `some_other -> self.update`
    return datatype_copyFrom( self, some_other->data );
}

#ifdef __cplusplus
}
#endif
