
/*-------------------------------------------------------------------------*/
/**
   @file    void_struct.h
   @author  N. Devillard
   @brief   Implements a basic void struct with compliance casting.

   This module implements a basic void pointer struct with datatype naming
   for further use on difficult-to-predict generic data formats on a lower
   backend api that thus can be casted to own datatypes.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _VOID_STRUCT_H_
#define _VOID_STRUCT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>


struct _datatype_;
typedef struct _dictionary_ dictionary;

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/**
 * @brief The basic type of a predictable, but yet generic struct, datastructure
 *      or class pointer (`void*`).
 */
typedef void* voidptr;

/**
 * @brief An `enum` that delimits, which type or type setter was used for the
 *      void pointer in `voidptr (void_struct*)->vs`.
 */
static enum _void_struct_ptr_type_ {
    /** @note The most usual enum values for `voidptr` */
    DATACLASS /** @brief If it is simply a libdsC `_dataclass_*` */,
    DICTIONARY /** @brief If it is simply a libdsC `dictionary*` */,
    DATATYPE /** @brief If it is simply a libdsC standard `_datatype_*` */,
    ORIGINAL /** @brief If it is in further unpredictable use cases the original pointer */,

    /** @note Now some more advanced enum values */
    LANGUAGE /** @brief If the language using libdsC setted the pointer and knows what to do */,
    FRONTEND /** @brief If the front-end handles this */,
    LOWLEVEL_API /** @brief If the front-end's low-level API handles this pointer */,
    CASTCOMPAT_H /** @brief If the functiona and macros from `castcompat.h` are to be used */,
    DATACAST_H /** @brief If the functions and named `datacast*` compatibility is handling this pointer */,

    /** @note Only if the use case of a `voidptr (_void_strucht*)->vs` typeset was not found */
    OTHER /** @brief If we can't say know, how to use or, have another use-case definitly defined. */,
    SOME /** @brief If we can not or will not predict yet and now, how the typesetter sets the pointer `voidptr vs`. */
};

/** @brief A more lexigraphical `typedef` of the enum. Comparable to `ptr_type_datastruct`. */
typedef enum _void_struct_ptr_type_ ptr_type_void_struct;

/**
 * @brief This struct implements a basic void pointer struct with datatype naming
   for further use on difficult-to-predict generic data formats on a lower
   backend api that thus can be casted to own datatypes.
   @note Function pointers can be altered on initialization to have the correct and
   ease-to-use cast function at developer's near distance.
 */
typedef struct _void_struct_ {
    /** @brief The name of the detected or set data type. */
    const char* datatype_name;
    /** @brief A generic pointer to the data type. */
    voidptr vs;
    /** @brief Set, how the voidptr pointer `vs` is to be set -and- to be used */
    enum _void_struct_ptr_type_ vs_type;

    /**
     * @brief A function that is to be able to cast/write especially
     * this `_void_struct_*` to a `_dictionary_*`.
     * @note Can be altered from default to custom function pointer
     */
    dictionary* (*toDict)( const struct _void_struct_* data );
    /**
     * @brief A function that is to be able to cast/read a `_dictionary_*`
     * into especially this type of `_void_struct_*`
     * @note Can be altered from default to custom function pointer
     */
    struct _void_struct_* (*fromDict)( const dictionary* dict );

    /**
     * @brief Cast an data type that is unpredictable by a data science
     * backend API to a `_void_struct_*` pointer of the same type.
     * @note Can be altered from default to custom function pointer
     */
    struct _void_struct_* (*castDatatype)( voidptr data );
    /**
     * @brief Cast an data type that is unpredictable by a data science
     * backend API to a `voidptr` pointer from a `_void_struct_*`
     * @note Can be altered from default to custom function pointer
     */
    voidptr (*castFrom)( struct _void_struct_* data );
} void_struct;


/**
 * @brief Initialize a `void_struct` with a datatype name and a pointer type preliminary inception.
 * @param dt_name The datatype name
 * @param ptr_type One value of `enum ptr_type_void_struct` or `ptr_type_void_struct::SOME` if not yet
 *      destinguished-to-be-known.
 * @returns A valid newly initialized `void_struct *`.
 */
struct _void_struct_* void_struct_init( const char* dt_name, const enum ptr_type_void_struct ptr_type );
/**
 * @brief Init the function pointers of the `void_struct vs` from an seem-use `datacast dc` pointer
 * @param vs A valid and initialized pointer to a `_void_struct_`.
 * @param dc A valid, initialized and corresponding `_datacast_` pointer, this thus means, that
 *      `strcmp( vs->datatypename, dc->datatype_name ) == 0`.
 * @returns `NULL` on failure or `vs` with all data transforming function pointers altered.
 */
//struct _void_struct_* void_struct_init_from_datacast( struct _void_struct_* vs, const struct _datacast_* dc );
/**
 * @brief Duplicate a valid, non-NULL `void_struct` pointer
 * @param vs_other A valid, non-NULL `void_struct` pointer
 * @returns A newly-allocated duplicate of `vs_other`.
 */
struct _void_struct_* void_struct_duplicate( const struct _void_struct_* vs_other );



/*---------------------------------------------------------------------------
                            Macro prototypes
 ---------------------------------------------------------------------------*/




/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/**
 * @brief Cast a `_void_struct_` pointer to a usable `voidptr`, e.g. for further use
 *      in your libraries data type structs and struct variables.
 * @param voids A valid pointer to a `void_struct`
 * @returns A transformed `void *`
 * 
 * @note Defaults to:
 * 
 *      voidptr castVoidStruct( struct _void_struct_* voids ) {
            if ( voids == NULL ) return NULL;
            else if ( strcmp( voids->datatype_name, "" ) == 0 )
                return toVoidPointer( voids );
            else if ( voids->castFrom != NULL )
                return voids->castFrom( voids );
            
            datacast* dc = dc_functions_get_datacast( voids->datatype_name );
            if ( dc == NULL ) return castDatatype( voids->vs, voids->datatype_name );

            return dc->fromVS( voids );
        }
 */
voidptr castVoidStruct( struct _void_struct_* voids );
/**
 * @brief Cast a generic `voidptr` to a `_void_struct_` pointer for further use on the
 *      low-level LibraryAPIs.
 * @param voidptr A pointer to a data structure or datatype
 * @param datatype_name The name of the datatype for now either handling of datatypes
 *      or `""` for default generic handling of datatypes.
 * @returns A valid `_void_struct_` pointer on success, NULL otherwise.
 * 
 * @note Defaults to
 * 
 *      struct _void_struct_* castVoidStructPtr( void* void_ptr, const char* datatype_name ) {
            datacast* dc = dc_functions_get_datacast( datatype_name );
            if ( dc != NULL ) return dc->toVS( void_ptr, datatype_name );
            return fromVoidPointer( void_ptr, datatype_name );
        }
 */
struct _void_struct_* castVoidStructPtr( voidptr void_ptr, const char* datatype_name );
/**
 * @brief Cast a generic `voidptr` to a `_void_struct_` pointer 
 *      for further use on the low-level/front-end-conversion LibAPIs.
 * @param voidptr A pointer to a data structure or datatype
 * @param datatype_name The name of the datatype for now either handling of datatypes
 *      or "" for default generic handling of datatypes.
 * @param castFunctionForDatatype 
 * @returns A valid `_void_struct_` pointer on success, NULL otherwise.
 * 
 * @note Defaults to
 *      
 *      struct _void_struct_* castToVoidStruct( void* data, const char* datatype_name
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
 */
struct _void_struct_* castToVoidStruct( voidptr data, const char* datatype_name
                                , struct _void_struct_* (*castFunctionForDatatype)(voidptr, const char*) );
/**
 * @brief Call `castToVoidStruct( data, "", &castDatatype )`
 * @param data A `voidptr` pointer to a valid data or `NULL` for initialization concernings
 * @param datatype_name The name of the datatype of data or `""` for generic data handling
 * @returns A pointer to a newly initialized `_void_struct_`
 */
#define DSC_CASTTO_VOID_STRUCT(data, datatype_name) castToVoidStruct( data, datatype_name, &castDatatype )

/**
 * @brief Cast a generic `_void_struct_` pointer to a `voidptr` 
 *      for further use on the low-level/front-end-conversion LibAPIs.
 * @param dt A pointer to a data structure of the type `_datatype_*`
 * @param datatype_name The name of the datatype for now either handling of datatypes
 *      or "" for default generic handling of datatypes.
 * @returns A valid `_void_struct_` pointer on success, NULL otherwise.
 * 
 * @note Defaults to
 * 
 *      void* castFromVoidStruct( struct _datatype_* dt, void* (castFunctionForDatatype)(struct _void_struct_*) ) {
            struct _void_struct_* vs = NULL;

            if ( dt == NULL ) return NULL;
            else if ( dt->vs == NULL ) {
                datacast* dc = dc_functions_get_datacast( dt->dt_name );
                if ( dc != NULL )
                    vs = dc->toVS( dt->vars );
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
                else vs = castToVoid(dt);
            }

            return castFunctionForDatatype(vs);
        }
 */
voidptr castFromVoidStruct( struct _datatype_* dt, voidptr (castFunctionForDatatype)(struct _void_struct_*) );
/**
 * @brief Call `castFromVoidStruct(DSC_CASTTO_VOID_STRUCT(dt, ""), &castVoidStruct)`
 * @param dt A pointer to a `datatype` with valid data or `NULL` for initialization concernings
 * @returns A pointer to a newly initialized and reusable `void*`.
 */
#define DSC_CASTFROM_VOID_STRUCT(dt) castFromVoidStruct(DSC_CASTTO_VOID_STRUCT(dt, ""), &castVoidStruct)




/*---------------------------------------------------------------------------
                            Extern functions
                          !! PLEASE DEFINE !!
 ---------------------------------------------------------------------------*/

/**
 * @brief Cast a pointer of a non-generic datatype to a `_void_struct_*` in your
 *      convenient library's ways. One may for example choose to use
 *      `(void_struct*)->vs = (dictionary*) dict` on default for transformation and
 *      conformitation concernings.
 */
extern struct _void_struct_* castDatatype( voidptr data, const char* datatype_name );
/**
 * @brief Transform a dict to a `void_struct` or simply set the pointer of the member 
 *      `vs` of a newly created `_void_struct_` instance to `dict`.
 */
extern struct _void_struct_* fromDict( const struct _dictionary_* dict );
/**
 * @brief Transform a `void_struct` to a `dictionary` pointer or simply get the pointer
 *      of the member `vs` of a `_void_struct_ vd` instance and cast it to `dictionary*`,
 *      if that is thus the mode of your data convenience-and-standards library.
 */
extern struct _dictionary_* toDict( const struct _void_struct_* vd );
/**
 * @brief Cast a pointer of a non-generic datatype to a `_void_struct_*` in your
 *      convenient library's ways. One may for example choose to use
 *      `(void_struct*)->vs = (dictionary*) dict` on default for transformation and
 *      conformitation concernings or use the original data and set the datatype's name.
 */
extern struct _void_struct_* fromVoidPointer( voidptr data, const char* datatype_name );
/**
 * @brief Untransform the generic-and-default `void_struct* vs` to a `voidptr` that is
 *      usable higher at the API.
 */
extern voidptr toVoidPointer( struct _void_struct_* vs );

#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
