
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

#ifndef _CUTILS_H_
#define _CUTILS_H_

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

typedef struct _void_struct_* (*castToVS)(void*);
typedef void* (*castFromVS)(const struct _void_struct_*);
typedef struct _dictionary_* (*toDictFromDT)(const struct _datatype_*);
typedef struct _dictionary_* (*toDictFromVS)(const struct _void_struct_*);
typedef struct _datatype_* (*fromDictToDT)(const struct _dictionary_*);


typedef struct _datacast_ {
   const char* datatype_name;
   unsigned npos;
   const castToVS toVS;
   const castFromVS fromVS;
   const toDictFromDT toDictDT;
   const fromDictToDT fromDictDT;
} datacast;

struct _datacast_* datacast_init( const char* dt_name
                        , const castToVS toVoidStruct
                        , const castFromVS fromVoidStruct
                        , const toDictFromDT toDictDataType
                        , const fromDictToDT fromDictDataType
                        , unsigned npos
                     );

struct _datacast_functions_list_;
struct _datacast_functions_list_ dc_functions_new();

#define DC_FUNCTIONS_INITIAL_SIZE 16
#define DC_FUNCTIONS_MAX_SIZE 256

static struct _datacast_functions_list_ {
   char** dnames;
   size_t    n;
   struct _datacast_** dc;

   size_t size;
   size_t max_size;
} dc_functions;

#define DC_FUNCTIONS_INIT() inline dc_functions = dc_functions_new(); \
            extern void* castToMyLib( const struct _datatype_* dt ); \
            // for use with e.g. `ex = (struct example*) castToMyLib(data);` \
         #define DSC_CAST(dataType) castToMyLib(#dataType)

size_t dc_functions_resize( const size_t new_size );
bool dc_functions_register_datacast_struct( struct _datacast_* dc );
bool dc_functions_register_datacast_functions( const char* datatype_name
                        , const castToVS toVoidStruct
                        , const castFromVS fromVoidStruct
                        , const toDictFromDT toDictDataType
                        , const fromDictToDT fromDictDataType
                        , unsigned npos
                     );
struct _datacast_* dc_functions_get_datacast( const char* datatype_name );

/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

#define DSC_REGISTER_DATACAST_STRUCT(func) dc_functions_register_datacast_struct(#func);
#define DSC_REGISTER_DATACAST_FUNCTIONS(datatype_name, toVS, fromVS, toDictDT, fromDictDT) \
            dc_functions_register_datacast_functions(#datatype_name, #toVS, #fromVS, #toDictDT, #fromDictDT);

#ifdef __cplusplus
}
#endif

#endif
