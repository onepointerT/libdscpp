
/*-------------------------------------------------------------------------*/
/**
   @file    cutils.c
   @author  N. Devillard
   @brief   Implements utilities for the programming language C.

*/
/*--------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

#include "cutils.h"

#include <stdlib.h>
#include <string.h>


size_t strfindpos( const char* _Str1, const char* StrFind, const size_t pos_start, const size_t pos_end ) {
    const size_t str1len = strlen(_Str1);
    const size_t strFindlen = strlen(StrFind);

    for ( unsigned int is = 0; is + strFindlen - 1 < str1len; is++ ) {
        if ( strcmp(strsubstr(_Str1, is, is + strFindlen - 1), StrFind) == 0 ) return is;
    }

    return str1len;
}

size_t strfindpossimple( const char* _Str1, const char* StrFind ) {
    return strfindpos( _Str1, StrFind, 0, strlen(_Str1) );
}

const char* strsubstr( const char* _Str1, const size_t pos_start, const size_t pos_end ) {
    char* substr = (char*) malloc(sizeof(char)*(pos_start == 0 ? pos_end + 1 : pos_end-pos_start+1));

    const size_t str1len = strlen(_Str1);
    if ( pos_start >= str1len || pos_end >= str1len ) return "";
    
    unsigned int isub = 0;
    for ( unsigned int is = pos_start; is <= pos_end; is++, isub++ ) {
        substr[isub] = _Str1[is];
    }

    return substr;
}

#ifdef __cplusplus
}
#endif
