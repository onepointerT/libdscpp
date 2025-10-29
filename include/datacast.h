
/*-------------------------------------------------------------------------*/
/**
   @file    datacast.h
   @author  N. Devillard
   @brief   Implements datacasting for datatypes of the `libdsC` backend and
            a library for specific datacasting per-datatype.

*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _DATACAST_H_
#define _DATACAST_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

struct _datatype_;
struct _dictionary_;
struct _void_struct_;

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

/**
 * @brief A function pointer that defines the transformability to void structs.
 */
typedef struct _void_struct_* (*castToVS)(void*, const char*);
/**
 * @brief A function pointer that defines the transformability from void structs.
 */
typedef void* (*castFromVS)(const struct _void_struct_*);
/**
 * @brief A function pointer that defines the transformability from datatypes to dictionary.
 */
typedef struct _dictionary_* (*toDictFromDT)(const struct _datatype_*);
/**
 * @brief A function pointer that defines the transformability from void structs to dictionary.
 */
typedef struct _dictionary_* (*toDictFromVS)(const struct _void_struct_*);
/**
 * @brief A function pointer that defines the transformability from dictionary to datatypes.
 */
typedef struct _datatype_* (*fromDictToDT)(const struct _dictionary_*);


/**
 * @brief A struct that basically holds function pointers to cast a specific named datatype.
 */
typedef const struct _datacast_ {
   /** @brief The name of the datatype */
   const char* datatype_name;
   /** @brief The position of the datatype in the datacast overview `dc_functions` */
   unsigned npos;
   /** @brief A function pointer of the type `castToVS` */
   const castToVS toVS;
   /** @brief A function pointer of the type `castFromVS` */
   const castFromVS fromVS;
   /** @brief A function pointer of the type `toDictFromDT` */
   const toDictFromDT toDictDT;
   /** @brief A function pointer of the type `fromDictToDT` */
   const fromDictToDT fromDictDT;
} datacast;

/**
 * @brief Initialize a `struct _datacast_` pointer's instance
 * @param dt_name The name of the datatype
 * @param toVoidStruct A function pointer of the type
 *    `struct _void_struct_* (*castToVS)(void*, const char*)`,
 *    where `void*` is the pointer to cast and `const char*` is
 *    the datatype's name
 * @param fromVoidStruct A function pointer of the type
 *    `void* (*castFromVS)(const struct _void_struct_*)`,
 *    to cast a `_void_struct_*` to a more high level-API
 *    specific struct/class that is thus castable from the
 *    generic `void*` that is thus to be returned.
 * @param toDictDataType A function pointer of the type
 *    `struct _dictionary_* (*toDictFromDT)(const struct _datatype_*)`,
 *    where it is important to have concrete datatypes
 *    serialized and transformable to other libraries or data
 *    structures, e.g. from C to SQL-readability.
 * @param fromDictDataType A function pointer of the type
 *    `struct _datatype_* (*fromDictToDT)(const struct _dictionary_*)`,
 *    where the programmer gets a `libdsC` standard `datatype*`,
 *    which is e.g. readen from a dictionary of another API
 *    or SQL to the C infrastructure of data science and design.
 * @param npos The position of this `struct datacast` inside of the
 *    datacast infrastructure `dc_functions` or a similar list or map.
 */
struct _datacast_* datacast_init( const char* dt_name
                        , const castToVS toVoidStruct
                        , const castFromVS fromVoidStruct
                        , const toDictFromDT toDictDataType
                        , const fromDictToDT fromDictDataType
                        , unsigned npos
                     );


/**
 *  @brief The initial size of the arrays of `dc_functions`,
 *       thus the initial number of storable `datacast` instance
 *       pointers.
 *  @note Defaults to 16.
 */
#define DC_FUNCTIONS_INITIAL_SIZE 16
/**
 *  @brief The maximum size of the arrays of `dc_functions`,
 *       thus the maximum number of storable `datacast` instance
 *       pointers.
 *  @note Defaults to 256.
 */
#define DC_FUNCTIONS_MAX_SIZE 256

/**
 * @brief The list infrastructure that can hold one `datacast`
 *    object per datatype known to the current C infrastructure
 *    of `libdsC`. It is reachable with `static` access to dc_functions`.
 * @note However, since this is a `static struct`, it is plausible,
 *    thus, that if more than one library of the project uses `libdsC`,
 *    all general `datacast` pointers of all using libraries are part of
 *    the member array `dc_functions->dc`.
 */
static struct _datacast_functions_list_ {
   /**
    *  @brief The names of the datatypes known to `dc_functions`.
    *  @note `dnames[i] == dc[i]->datatype_name`
    */
   char** dnames;
   /** @brief The number of castable datatypes known to `dc_functions` */
   size_t    n;
   /**
    *  @brief The `datacast*` abilities known to `dc_functions`
    *  @note `dc[i]->datatype_name == dnames[i]`
    */
   struct _datacast_** dc;

   size_t size;
   size_t max_size;
} dc_functions;

/** 
 * @brief Just for static usability and initializability it is
 *       important not to overwrite the already-existing instance
 *       of `dc_functions`, if already given.
 */
static bool dc_functions_initialized = false;

/**
 * @brief Set the static variable `dc_functions` to a newly created
 *    instance of `struct _datacast_functions_list_`
 */
static struct _datacast_functions_list_ dc_functions_new();

/**
 * @brief Once, it is needed to initialize dc_functions. Do this with this
 *    macro and add the ability of everything you need to use it in your own
 *    library.
 */
#define DC_FUNCTIONS_INIT() inline dc_functions = dc_functions_new(); \
            extern void* castToMyLib( const struct _datatype_* dt ); \
            // for use with e.g. `ex = (struct example*) castToMyLib(data);`
         #define DSC_CAST(dataType) castToMyLib(#dataType)

/**
 * @brief Grow the arrays of `dc_functions` to a new limit
 * @param new_size The new size of the arrays of `dc_functions`
 * @returns The real new size or, if `new_size < dc_functions.size`, the current size.
 * @note `new_size <= dc_functions.max_size = DC_FUNCTIONS_MAX_SIZE`
 */
static size_t dc_functions_resize( const size_t new_size );
/**
 * @brief Register a new `struct _datacast_*` at the facility environment
 *    for datacasting (`dc_functions`).
 * @param dc A valid `datacast*` struct pointer.
 * @returns True, if `dc` was new at and registered at `dc_functions`
 */
static bool dc_functions_register_datacast_struct( struct _datacast_* dc );
/**
 * @brief Register a new `struct _datacast_*` at the facility environment
 *    for datacasting (`dc_functions`).
 * @param dt_name The name of the datatype
 * @param toVoidStruct A function pointer of the type
 *    `struct _void_struct_* (*castToVS)(void*, const char*)`,
 *    where `void*` is the pointer to cast and `const char*` is
 *    the datatype's name
 * @param fromVoidStruct A function pointer of the type
 *    `void* (*castFromVS)(const struct _void_struct_*)`,
 *    to cast a `_void_struct_*` to a more high level-API
 *    specific struct/class that is thus castable from the
 *    generic `void*` that is thus to be returned.
 * @param toDictDataType A function pointer of the type
 *    `struct _dictionary_* (*toDictFromDT)(const struct _datatype_*)`,
 *    where it is important to have concrete datatypes
 *    serialized and transformable to other libraries or data
 *    structures, e.g. from C to SQL-readability.
 * @param fromDictDataType A function pointer of the type
 *    `struct _datatype_* (*fromDictToDT)(const struct _dictionary_*)`,
 *    where the programmer gets a `libdsC` standard `datatype*`,
 *    which is e.g. readen from a dictionary of another API
 *    or SQL to the C infrastructure of data science and design.
 * @param npos The position of this `struct datacast` inside of the
 *    datacast infrastructure `dc_functions` or a similar list or map.
 * @returns True, if a new `struct datacast` was new at and registered at `dc_functions`
 */
static bool dc_functions_register_datacast_functions( const char* datatype_name
                        , const castToVS toVoidStruct
                        , const castFromVS fromVoidStruct
                        , const toDictFromDT toDictDataType
                        , const fromDictToDT fromDictDataType
                        , unsigned npos
                     );
/**
 * @brief Get the datacast struct - if any - for a specific named datatype
 * @param datatype_name The name of the datatype to search its cast ability of
 * @returns If the `datatype_name` was found, a `struct _datacast_` pointer,
 *    `NULL` otherwise.
 */
static struct _datacast_* dc_functions_get_datacast( const char* datatype_name );

/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

#define DSC_REGISTER_DATACAST_STRUCT(strct) dc_functions_register_datacast_struct(#strct);
#define DSC_REGISTER_DATACAST_FUNCTIONS(datatype_name, toVS, fromVS, toDictDT, fromDictDT) \
            dc_functions_register_datacast_functions(#datatype_name, #toVS, #fromVS, #toDictDT, #fromDictDT);

#ifdef __cplusplus
}
#endif

#endif
