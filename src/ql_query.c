
/*-------------------------------------------------------------------------*/
/**
   @file    ql_query.h
   @author  N. Devillard
   @brief   Implements the dictionary queries for query languages like `SQL`

   This module implements a simple generic way to query dictionaries in SQL
   syntax and get dataset dictionaries by query request.
*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "ql_query.h"

#include <stdlib.h>
#include <string.h>


#define QL_QUERY_MAX_LENGTH 256
#define QL_QUERY_MAX_KEYS 64
#define QL_QUERY_MAX_SECTIONS 32


/*---------------------------------------------------------------------------
                                New functions
 ---------------------------------------------------------------------------*/
QL_Query make_ql_query( const char* sql_query ) {
   QL_Query qlq = (QL_Query) malloc(sizeof(QL_Query)*QL_QUERY_MAX_LENGTH);

   const size_t query_length = strlen(sql_query);
   memcpy( qlq, sql_query
         , sizeof(const char) * ( query_length > QL_QUERY_MAX_LENGTH ? QL_QUERY_MAX_LENGTH : query_length ) );
   
   return qlq;
}

struct _ql_query_* _ql_query_init( const QL_Query query ) {
   struct _ql_query_* qlq = (struct _ql_query_*) malloc(sizeof(struct _ql_query_));

   qlq->query = query;
   qlq->section_name = NULL;
   qlq->key_names = (char*) malloc(sizeof(char*)*QL_QUERY_MAX_KEYS);

   return qlq;
}

QL_Query* parse_ql_query( const QL_Query query ) {
   QL_Query* qlq_arr = (QL_Query*) malloc(sizeof(QL_Query)*QL_QUERY_MAX_SECTIONS);


}

struct _ql_query_* ql_query_parse( const QL_Query query ) {
   //QL_Query* qlq
}

#ifdef __cplusplus
}
#endif
