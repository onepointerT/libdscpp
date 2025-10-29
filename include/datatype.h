
/*-------------------------------------------------------------------------*/
/**
   @file    datatype.h
   @author  N. Devillard
   @brief   Implements the general data type of `libdsC`

   This module implements a simple generic data type object, since data is
   provided in many different ways, structs, classes and read-methods.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _DATATYPE_H_
#define _DATATYPE_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

#include "dictionary.h"
#include "void_struct.h"

#include <stdbool.h>
#include <stddef.h>

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

struct _dataclass_;
struct _dictionary_;

/**
 * @brief The general `datatype` struct of `libdsC`. It can save whatever
 *      `struct`/`class` of your choice at it's member `void* vars`.
 * 
 * @note Function pointers can be altered on initialization to have the
 *      correct behaviour and ease-to-use functions at developers sight.
 */
typedef struct _datatype_ {
    /** 
     * @brief The human-readable name of a datatype or an empty `""`
     *      for default or generic handling of the convenience `struct _datatype_`.
     */
    const char* dt_name;
    /** 
     * @brief A pointer to the data variables at your struct, class or similar.
     * @note You can e.g. use `((ConcreteClass*) dt->vars)->personStruct->specificVariable`
     *      and could define a macro for type casting of the `datatype` of `libdsC`,
     *      like `CONCRETE_CLASS(dt) ((ConcreteClass*) dt->vars)` for each type, that uses
     *      the `libdsC` facility infrastructure for `datatype`s.
     * @note A `struct` pointer of a . specific kind .; if other programming facility languages
     *       use this library, also a class or an extern native C pointer is set-able here !
     */
    void* vars; // this is a struct pointer of a specific kind !
    /**
     * @brief Optionally an pointer to a `_void_struct_*` for transformability
     *      convenience/comfort at other AOIPs and libraries and program's clients.
     */
    struct _void_struct_* vs;

    /**
     * @brief Update the datatype `dt` from a dictionary `dict`
     * @note Points to `NULL` by default, because it is really your higher-end libraries
     *      definit task to define, how to update your datastructures from a
     *      (key, value)-paired dictionary.
     */
    bool (*update)( struct _datatype_* dt, const struct _dictionary_* dict );

    /**
     * @brief Initialize a `libdsC` instance of `struct _datatype_` by copying it from
     *      another `struct _datatype_*`.
     */
    struct _datatype_* (*initCopy)( const struct _datatype_* other );
    /**
     * @brief Initialize a `libdsC` instance of `struct _datatype_` by using the pointer
     *      `void* vars` from another `struct _datatype_*`, too.
     */
    struct _datatype_* (*initDatatype)( const struct _datatype_* other );
    /**
     * @brief Initialize a `libdsC` instance of `struct _datatype_` by using the pointer
     *      to a backend `_void_struct_*` (of your kind).
     */
    struct _datatype_* (*init)( const struct _void_struct_* var_struct );

    /**
     * @brief Copy one datatype `other` to another `self`.
     */
    bool (*copyFrom)( struct _datatype_ self, const struct _datatype_* other );
    /**
     * @brief Make an update/creation of a datatype `self` from a `dataclass`.
     */
    bool (*fromDataclass)( struct _datatype_ self, const struct _dataclass_* some_other );

    struct _datatype_* (*fromDict)( const struct _dictionary_* dict );
    struct _dictionary_* (*toDict)( const struct _datatype_* dt );
} datatype;

/**
 * @brief Initialize an newly allocated instance of a `datatype`
 * @param variables The pointer that is to be set for `datatype::vars`
 * @param datatype_name The name of the datatype to be initialized now
 * @returns A `struct _datatype_` pointer on success, `NULL` otherwise.
 */
struct _datatype_* datatype_init( void* variables, const char* datatype_name );

/**
 * @brief Initialize an newly allocated instance of a `datatype` by copying another
 * @param other The pointer to a `datatype` that is to be copied
 * @returns A `struct _datatype_` pointer on success, `NULL` otherwise.
 */
struct _datatype_* datatype_initCopy( const struct _datatype_* other );
/**
 * @brief Initialize an newly allocated instance of a `datatype` by using the values
 *      of `other->vars` additionally, too
 * @param other The pointer to a `datatype` that is to be used and pointed-to also
 * @returns A `struct _datatype_` pointer on success, `NULL` otherwise.
 */
struct _datatype_* datatype_initDatatype( const struct _datatype_* other );
/**
 * @brief Initialize an newly allocated instance of a `datatype`
 * @param variables The pointer that is to be transformed and set for `datatype::vars`
 *      from a generic `void_struct`.
 * @returns A `struct _datatype_` pointer on success, `NULL` otherwise.
 */
struct _datatype_* datatype_initFromVoidStruct( const struct _void_struct_* variables );


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

/**
 * @brief Cast a `datatype dt` to a backend and API-independently compatible `void_struct`
 * @param dt The pointer to the data type to transform
 * @returns A pointer to a `void_struct` on success, `NULL` otherwise
 */
struct _void_struct_* datatype_castToVoid( const struct _datatype_* dt );



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
extern bool update( struct _datatype_* dt, const struct _dictionary_* dict );
/**
 * @brief Cast a `datatype dt` from a backend and API-independently compatible `void_struct`
 * @param vd The pointer to the `void_struct` data type to transform (data at `vd->vs`!)
 * @returns A pointer to a `datatype` on success, `NULL` otherwise
 */
extern struct _datatype_* datatype_castFromVoid( const struct _void_struct_* vd );
/**
 * @brief Update an instance of a `datatype` by copying another
 * @param self The pointer to a `datatype` to copy the data from `other` to
 * @param other The pointer to a `datatype` that is to be copied
 * @returns True on success
 */
extern bool datatype_copyFrom( struct _datatype_* self, const struct _datatype_* other );
/**
 * @brief Update an instance of a `datatype` by transforming from a `dataclass` struct
 * @param self The pointer to a `datatype` to copy the data from `some_other` to
 * @param other The pointer to a `struct _dataclass_` that is to be copied
 * @returns True on success
 */
extern bool datatype_fromDataclass( struct _datatype_* self, const struct _dataclass_* some_other );


#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
