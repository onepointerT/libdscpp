
/*-------------------------------------------------------------------------*/
/**
   @file    datascience.h
   @author  N. Devillard
   @brief   Includes the definition files of `libdsC`
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _DATASCIENCE_H_
#define _DATASCIENCE_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "castcompat.h"
#include "datacast.h"
#include "dataclass.h"
#include "datatype.h"
#include "dictionary.h"
#include "void_struct.h"


inline static enum ptr_type_void_struct default_type_vs;
#define DSC_MODE_PTR_VOID_STRUCT(ptr_type) default_type_vs = ptr_type;


#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
