
/*-------------------------------------------------------------------------*/
/**
   @file    cutils.h
   @author  N. Devillard
   @brief   Implements utilities for the programming language C.

*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _CUTILS_H_
#define _CUTILS_H_

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





/*---------------------------------------------------------------------------
                            Function prototypes
 ---------------------------------------------------------------------------*/
/**
 * @brief Find the position of some substring inside of a string.
 * @param _Str1 The string to search in
 * @param StrFind The string to search for
 * @param pos_start The position to start searching with
 * @param pos_end The position to end searching at
 * @returns The position, where `StrFind` starts the first time inside of `_Str1`
 *      or `strlen(_Str1)+1`, if `StrFind` was not found.
 */
size_t strfindpos( const char* _Str1, const char* StrFind, const size_t pos_start, const size_t pos_end );
/**
 * @brief Find the position of some substring inside of a string.
 * @param _Str1 The string to search in
 * @param StrFind The string to search for
 * @returns The position, where `StrFind` starts the first time inside of `_Str1`
 *      or `strlen(_Str1)+1`, if `StrFind` was not found.
 * 
 * @note Simply calls `strfindpos(_Str1, StrFind, 0, strlen(_Str1)-1)` and is equivalent to this call
 */
size_t strfindpossimple( const char* _Str1, const char* StrFind );
/**
 * @brief Get the substring of inside of a string at a position specified
 * @param _Str1 The string where the substring is in
 * @param pos_start The position where the substring starts
 * @param pos_end The position where the substring ends
 * @returns The substring, that thus means `_Str1[pos_start:pos_end]` newly allocated-and-copied.
 */
const char* strsubstr( const char* _Str1, const size_t pos_start, const size_t pos_end );
/**
 * @brief Concatenate two strings
 * @param _Str1 The first string
 * @param _Str2 The second string
 * @returns The second string behind the first string as one string
 */
const char* strconcat( const char* _Str1, const char* _Str2 );

#ifdef __cplusplus
}
#endif

#endif
