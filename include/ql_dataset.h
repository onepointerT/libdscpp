
/*-------------------------------------------------------------------------*/
/**
   @file    ql_dataset.h
   @author  N. Devillard
   @brief   Implements the dictionary queries for query languages like `SQL`

   This module implements a simple generic way to query dictionaries in SQL
   syntax and get dataset dictionaries by query request.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _QL_DATASET_H_
#define _QL_DATASET_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "dictionary.h"
#include "dictionary_element.h"
#include "ql_query.h"

#include <stdint.h>


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef struct _ql_element_ {
    const char* name;
    struct _dictionary_element_** data;
    struct _ql_element_** relationals;
} ql_element;


struct _ql_element_* _ql_element_init( const size_t size, const char* elem_name );


typedef struct _ql_dataset_ {
    struct _ql_query_** queries;
    struct _ql_dataset_** relationals;
    struct _ql_element_** elements;
} ql_dataset;

//struct _ql_dataset_* _ql_dataset_init(  )


/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/

struct _ql_dataset_* ql_dataset_query( const ql_query** query );



/*---------------------------------------------------------------------------
                            Extern functions
                          !! PLEASE DEFINE !!
 ---------------------------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif
