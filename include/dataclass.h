
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

#ifndef _DATACLASS_H_
#define _DATACLASS_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

#include "datatype.h"

/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef struct _dataclass_ {
    const size_t elements;
    struct _datatype_* data;
} dataclass;





/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/


#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
