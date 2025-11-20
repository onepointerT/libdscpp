
/*-------------------------------------------------------------------------*/
/**
   @file    ql.h
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

#ifndef _QL_QUERY_H_
#define _QL_QUERY_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


/*---------------------------------------------------------------------------
                                New types
 ---------------------------------------------------------------------------*/

typedef const char* QL_Query;

QL_Query make_ql_query( const char* sql_query );


typedef struct _ql_query_ {
    QL_Query query;
    const char* section_name;
    const char** key_names;
} ql_query;

struct _ql_query_* _ql_query_init( const QL_Query query );

/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/
QL_Query* parse_ql_query( const QL_Query query );

struct _ql_query_* ql_query_parse( const QL_Query query );





/*---------------------------------------------------------------------------
                            Extern functions
                          !! PLEASE DEFINE !!
 ---------------------------------------------------------------------------*/



#ifdef __cplusplus
}
#endif

#endif
