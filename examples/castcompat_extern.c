
/*-------------------------------------------------------------------------*/
/**
   @file    castcompat_extern.c
   @author  N. Devillard
   @brief   Implements casting with datatypes for your own front-end 
            developer's user data

   This module adhires a simple directive of functions that need to be defined
   for typecasting own datatypes from and to `dictionary*` that can be handed
   in to the datacast facility for creating the specific datatypes.

   In this example, only the simple and senseful behaviour is pronounced,
   which will work as business customer's backend agility definit refinement
   definition to `libdsc` so thus it becomes feature-definit where and how to
   cast-and-transform data to human and c'est-side PI readables and transformable
   structs (or classes for enablement of libdsC to another Object-Orientated
   language).
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "castcompat.h"

#include <string.h>

// #include <yourDCL.h>  // Your data creation/constructing library here
// #include <yourDTL.h>  // Your data template library include here

#include "datacast.h"
#include "datatype.h"


/**
 * Some private functions
 */
struct YourDataType1;
static struct YourDataType1* castToDT1( struct _datatype_* dt ) {
    return dcl_cast_dt1( dt->dt_name, dt->vars );
}

struct YourDataType2;
static struct YourDataType2* castToDT2( struct _datatype_* dt ) {
    return dcl_cast_dt2( dc_functions_get_datacast(dt->dt_name)->toDictDT(dt) );
}


/**
 * The first definit must-have extern functions to make the backend work
 * for developer- and user-centric front-end data design.
 * 
 * Just an example.
 */
void* castTo( struct _datatype_* dt ) {
    if ( strcmp(dt->dt_name, "YourDataType1") == 0 ) {
        return castToDT1( dt );
    } else if ( strcmp(dt->dt_name, "YourDataType2") == 0 ) {
        return castToDT2( dt );
    }

    datacast* dc = dc_functions_get_datacast( dt->dt_name );
    if ( dc == NULL ) return NULL;

    return dc->toDictDT( dt ); // In generic ways we could pass a dictionary or a void_struct.
}


/**
 * Used in specific scenario like this:
 */
// struct datatype dt = { .dt_name = "YDT" };
// DSC_CAST(struct YourDataType1, ydt1, dt)
// OR:
// struct YourDataType1* ydt1 = (struct YourDataType1*) castTo(dt);


/**
 * The second definit must-have extern functions to make the backend work
 * for developer- and user-centric front-end data design.
 * 
 * Just an example.
 */
struct _datatype_* castFrom( void* dataptr, const char* datatype_name ) {
    return datatype_init( dataptr, datatype_name );
}


/**
 * The third definit must-define extern function to make the backend work
 * for other APIs or, unyet predictable c'est somewhere a used front end in
 * and for which data science, dynamic usable -. even for the own business
 * developers and conherent consulting and testing teams, is definit here.
 * 
 * From here on, the example predicts, that at least a `(_void_struct*)->vs`
 * pointer (pointer type `void`) holds a human-and-others readable `dictionary*`
 * for further use and convenient constraint on client devices and other
 * ProgrammerInterfaces to be the reason, why I can transform my data from
 * one struct holding variables for use in functions to another use case client.
 */
struct _datatype_* castTypeFromVS( const struct _void_struct_* vs ) {
    datacast* dc = dc_functions_get_datacast( vs->datatype_name );
    if ( dc != NULL ) return dc->fromDictDT( (dictionary*) vs->vs );
    return datatype_init( vs->castFrom != NULL ? vs->castFrom(vs) : NULL, vs->datatype_name );
}
// OR
/*
struct _datatype_* castTypeFromVS( const struct _void_struct_* vs ) {
    
    if ( vs->vs_type == DICTIONARY ) {
        datacast* ds = dc_functions_get_datacast( vs->datatype_name );
        if ( ds == NULL ) return datatype_init( vs->vs_type, vs->datatype_name );
        return ds->fromDictDT( (dictionary*) vs->vs );
    } else if ( vs->vs_type == DATATYPE ) return (struct _datatype_*) vs->vs;

    return datatype_init( vs->vs, vs->datatype_name );
}
*/

/**
 * The fourth definit must-define extern function to make the backend work
 * for other APIs or, unyet predictable c'est somewhere at used front-end in
 * and for which data science, dynamic usable -. especially for the own
 * business client developers and conherent use-cast-consulting and programming
 * of data design structures and functions.
 * 
 * The further constraint, I - the developer and data designer - don't need
 * to be in fright of other use-case clients not being able to accept my
 * variable in another seem-to-seem use-case scenario's client's library
 * for further processing, when using the `libdsc` backend like this:
 * 
 * - `(_void_struct_*)->vs` holds a dictionary for further constrains on
 *      readability and struct/class construction
 * - `(_datatype_*)->vars` holds then the struct or class itself and is
 *      at least retransformable and castable to the original structure
 *      when asked for its datatype name. This is part of the benefits
 *      a top-level library can provide to the unpredicted use-cast of
 *      `libdsc` - whichever . peaceful and human unenslaving and empowering
 *      use case . of data science it could and should be.
 * - 
 */
struct _void_struct_* castVSFromType( const struct _datatype_* dt ) {
    void_struct* vs = void_struct_init( dt->dt_name );
    
    datacast* dc = dc_functions_get_datacast( dt->dt_name );
    if ( dc != NULL ) {
        vs->vs = dc->toDictDT( dt );
    } else {
        vs = dt;
    }
    return datatype_init( vs->castFrom != NULL ? vs->castFrom(vs) : NULL, vs->datatype_name );
}

#ifdef __cplusplus
}
#endif
