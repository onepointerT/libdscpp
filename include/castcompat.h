
/*-------------------------------------------------------------------------*/
/**
   @file    castcompat.h
   @author  N. Devillard
   @brief   Implements casting with datatypes for your own front-end 
            developer's user data

   This module adhires a simple directive of functions that need to be defined
   for typecasting own datatypes from and to `dictionary*` that can be handed
   in to the datacast facility for creating the specific datatypes.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _CASTCOMPAT_H_
#define _CASTCOMPAT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "datacast.h"
#include "datatype.h"

#include <stdint.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/



/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                            Extern functions
                          !! PLEASE DEFINE !!
 ---------------------------------------------------------------------------*/


/**
 * @brief In all more-or-less predictable scenarios the data science backend needs
 *      to provide a class that can cast a C datatype (e.g. `((_datatype_*) concrete_dt)->vars`)
 *      to my datatype or - at least . a user-and-machine readable `dictionary*` for handling,
 *      prooving and providing user's data.
 * @param dt The C datatype that is to be casted to a struct just created and defined for more
 *          non-generic data handling. The basic datatype struct of `libdsc`
 * @returns A `void` pointer with the specific data type as pointer that can be casted to
 *              your specific struct (or for more object-orientated-ways: class instance).
 * 
 * @note This function needs to be written by the library using the data design
 *      backend `libdsc` and could be like this
 * 
 *
 *      The first definit must-have extern functions to make the backend work
 *      for developer- and user-centric front-end data design.
 * 
 *      Just an example.
 *      
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
 *  @note Have a look at the macros `DSC_CAST()` and `DSC_CASTTO()` !
 *
 *  @note The first definit must-have extern functions to make the backend work
 *      for developer- and user-centric front-end data design.
 */
extern void* castTo( struct _datatype_* dt );

/**
 * @brief Define a specific variable and cast from e.g. an incoming `datatype` pointer.
 * @param type The type to cast to
 * @param var_name How to reference the name of the variable that is to be called
 * @param datatype_data The `datatype*` that hires and holds the data and is castable to `##type *` with `castTo()`.
 * @note For example, `DSC_CAST(struct YourDataType1, ydt1, dt)` evaluates to
 *          `struct YourDataType1* ydt1 = (struct YourDataType1*) castTo(dt);`
 */
#define DSC_CAST(type, var_name, datatype_data) \ \\ ##type * ##var_name = (##type *) castTo(datatype_data);
/**
 * @brief Cast a specific type from e.g. an incoming `datatype` pointer.
 * @param type The type to cast to
 * @param datatype_data The `datatype*` that hires and holds the data and is castable to `##type *` with `castTo()`.
 * @note For example, `exampleFunction( DSC_CASTO(struct YourDataType1, dt)->vars );` evaluates to
 *          `exampleFunction( ((struct YourDataType1*) castTo(dt))->vars );`
 */
#define DSC_CASTTO(type, datatype_data) ((##type *) castTo(datatype_data))



/**
 * @brief In all more-or-less predictable scenarios the data science backend needs
 *      to provide a class that can cast to a more generic C datatype 
 *      (e.g. `castToDict(castFrom(concrete_cls, "YDT"))->toREST("192.168.0.12:81")`)
 *      of this data design backend API . and  - at least . a machine transformable and
 *      API-unspecific `dictionary` for handling, prooving and providing user's data to other
 *      libraries, clients, servers or front-ends.
 * @param dataptr The concrete class or struct pointer that needs a for example serializable
 *           C datatype of `libdsc`.
 * @param datatype_name The name of the incoming and thus for `libdsc` handled datatype for further
 *           decisional logic and conditions.
 * @returns A `struct _datatype_` pointer with the specific data type as pointer that can be casted to
 *              your specific struct (or for more object-orientated-ways: class instance).
 * 
 * @note This function needs to be written by the library using the data handling
 *      backend `libdsc`.
 * 
 *      It could be simply implemented like
 * 
 *      
 *      struct _datatype_* castFrom( void* dataptr, const char* datatype_name ) {
 *          return datatype_init( dataptr, datatype_name );
 *      }
 * 
 * @note Have a look at the macro `DSC_CASTFROM()` !
 * 
 * @note The second definit must-have extern functions to make the backend work
 *      for developer- and user-centric front-end data design.
 */
extern struct _datatype_* castFrom( void* dataptr, const char* datatype_name );
/**
 * @brief Cast a specific incoming variable to an `datatype` pointer.
 * @param dataptr The pointer to a datastruct that is thus to be casted to `_datatype_*`.
 * @param datatype_name The name of the type of the `dataptr` as `const char*`.
 * @note For example, `dictionary* newDict = castToDict(DSC_CASTFROM(concrete_cls, "YDT"));` evaluates to
 *          `dictionary* newDict = castToDict(castFrom(concrete_cls, "YDT"));`
 */
#define DSC_CASTFROM(dataptr, datatype_name) castFrom(dataptr, datatype_name)


/**
 * @brief Cast or transform a standard `libdsC` back-end `void_struct` to a default
 *      `libdsC` back-to-front-end-level `datatype`.
 * @param vs A pointer to the valid `void_struct`.
 * @returns A pointer to a `datatype`.
 * 
 * @note This function needs to be written by the library using the data handling
 *      backend `libdsc`.
 * 
 * @note The third definit must-define extern function to make the backend work
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
extern struct _datatype_* castTypeFromVS( const struct _void_struct_* vs );

/**
 * @brief Cast or transform a standard `libdsC` pointer of `datatype` to a default
 *      `libdsC` back-end-level `void_struct`.
 * @param vs A pointer to the valid `datatype`.
 * @returns A pointer to a `void_struct`.
 * 
 * @note This function needs to be written by the library using the data handling
 *      backend `libdsc`.
 * 
 * @note The fourth definit must-define extern function to make the backend work
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
 */
extern struct _void_struct_* castVSFromType( const struct _datatype_* dt );


extern struct _void_struct_* castVSFromDict( const struct _dictionary_* dict );
extern struct _dictionary_* castDictFromVS( const struct _void_struct_* vs );


#ifdef __cplusplus
}
#endif

#endif
