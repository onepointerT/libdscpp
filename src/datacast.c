
/*-------------------------------------------------------------------------*/
/**
   @file    datacast.c
   @author  N. Devillard
   @brief   Implements datacasting for datatypes of the `libdsC` backend and
            a library for specific datacasting per-datatype.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "datacast.h"

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*---------------------------------------------------------------------------
                                Functions
 ---------------------------------------------------------------------------*/

struct _datacast_* datacast_init( const char* dt_name
                        , const castToVS toVoidStruct
                        , const castFromVS fromVoidStruct
                        , const toDictFromDT toDictDataType
                        , const fromDictToDT fromDictDataType
                        , unsigned npos
) {
    struct _datacast_ dcval = {
          .datatype_name = dt_name, .toVS = toVoidStruct, .fromVS = fromVoidStruct
        , .toDictDT = toDictDataType, .fromDictDT = fromDictDataType, .npos = npos
    };
    
    struct _datacast_* dc = (struct _datacast_*) malloc(sizeof(struct _datacast_));
    memcpy( dc, &dcval, sizeof(struct _datacast_) );
    
    return dc;
}


struct _datacast_functions_list_ dc_functions_new() {
    if ( dc_functions_initialized ) return dc_functions;

    struct _datacast_functions_list_ dfl = {
            .dnames = (char**) malloc(sizeof(char*)*DC_FUNCTIONS_INITIAL_SIZE)
          , .n = 0
          , .size = DC_FUNCTIONS_INITIAL_SIZE
          , .max_size =  DC_FUNCTIONS_MAX_SIZE
          , .dc = (struct _datacast_**) malloc(sizeof(struct _datacast_*)*DC_FUNCTIONS_INITIAL_SIZE)
    };

    dc_functions_initialized = true;

    return dfl;
}


size_t dc_functions_resize( const size_t new_size ) {
    if ( dc_functions.size >= dc_functions.max_size
      || new_size >= dc_functions.max_size ) return dc_functions.max_size+1;
    else if ( new_size < dc_functions.size ) return dc_functions.size;
    
    char** new_dnames = (char**) malloc(sizeof(char*)*new_size);
    memcpy( new_dnames, dc_functions.dnames, sizeof(char*)*dc_functions.size);
    struct _datacast_** new_dc = (struct _datacast_**) malloc(sizeof(struct _datacast_*)*new_size);
    memcpy( new_dc, dc_functions.dc, sizeof(struct _datacast_*)*dc_functions.size);

    dc_functions.dnames = new_dnames;
    dc_functions.dc = new_dc;

    dc_functions.size = new_size;

    return new_size;
}


bool dc_functions_register_datacast_struct( struct _datacast_* dc ) {
    if ( dc_functions.n >= dc_functions.size ) {
        if ( dc_functions_resize( dc_functions.size*2 )
          == dc_functions.max_size + 1) return false;
    }
    dc_functions.dc[dc_functions.n] = dc;
    dc_functions.dnames[dc_functions.n] = dc->datatype_name;
    dc_functions.n++;

    return true;
}


bool dc_functions_register_datacast_functions( const char* datatype_name
                        , const castToVS toVoidStruct
                        , const castFromVS fromVoidStruct
                        , const toDictFromDT toDictDataType
                        , const fromDictToDT fromDictDataType
                        , unsigned npos
                     ) {
    struct _datacast_* dc = datacast_init( datatype_name
                                , toVoidStruct, fromVoidStruct
                                , toDictDataType, fromDictDataType
                                , npos );
    return dc_functions_register_datacast_struct( dc );
}


struct _datacast_* dc_functions_get_datacast( const char* datatype_name ) {
    for ( unsigned int idc = 0; idc < dc_functions.n; idc++ ) {
        if ( strcmp(dc_functions.dnames[idc], datatype_name) == 0 )
            return dc_functions.dc[idc];
    }
    return NULL;
}

#ifdef __cplusplus
}
#endif
