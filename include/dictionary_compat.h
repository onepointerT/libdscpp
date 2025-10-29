
/*-------------------------------------------------------------------------*/
/**
   @file    dictionary_compat.h
   @author  N. Devillard
   @brief   All functions to use `struct _dictionary_*` more than defined in
            `dictionary.h`.
*/
/*--------------------------------------------------------------------------*/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#ifndef _DICTIONARY_COMPAT_H_
#define _DICTIONARY_COMPAT_H_

/*---------------------------------------------------------------------------
                                Includes
 ---------------------------------------------------------------------------*/

#include "dictionary.h"
#include <stdint.h>

#ifdef __cplusplus
namespace dsc {

extern "C" {
#endif

/*-------------------------------------------------------------------------*/
/**
  @brief    Configure a function to receive the error messages.
  @param    errback  Function to call.

  By default, the error will be printed on stderr. If a null pointer is passed
  as errback the error callback will be switched back to default.
 */
/*--------------------------------------------------------------------------*/

void dictionary_set_error_callback(int (*errback)(const char *, ...));

/*-------------------------------------------------------------------------*/
/**
  @brief    Get number of sections in a dictionary
  @param    d   Dictionary to examine
  @return   int Number of sections found in dictionary

  This function returns the number of sections found in a dictionary.
  The test to recognize sections is done on the string stored in the
  dictionary: a section name is given as "section" whereas a key is
  stored as "section:key", thus the test looks for entries that do not
  contain a colon.

  This clearly fails in the case a section name contains a colon, but
  this should simply be avoided.

  This function returns -1 in case of error.
 */
/*--------------------------------------------------------------------------*/

int dictionary_getnsec(const dictionary * d);


/*-------------------------------------------------------------------------*/
/**
  @brief    Get name for section n in a dictionary.
  @param    d   Dictionary to examine
  @param    n   Section number (from 0 to nsec-1).
  @return   Pointer to char string

  This function locates the n-th section in a dictionary and returns
  its name as a pointer to a string statically allocated inside the
  dictionary. Do not free or modify the returned string!

  This function returns NULL in case of error.
 */
/*--------------------------------------------------------------------------*/

const char * dictionary_getsecname(const dictionary * d, int n);


/*-------------------------------------------------------------------------*/
/**
  @brief    Save a dictionary to a loadable ini file
  @param    d   Dictionary to dump
  @param    f   Opened file pointer to dump to

  This function dumps a given dictionary into a loadable ini file.
  It is Ok to specify @c stderr or @c stdout as output files.

  All values are quoted, these charecters are escaped:

  - ' : the quote character (e.g. "String with \"Quotes\"")
  - \ : the backslash character (e.g. "C:\\tmp")

 */
/*--------------------------------------------------------------------------*/

void dictionary_dump_ini(const dictionary * d, FILE * f);

/*-------------------------------------------------------------------------*/
/**
  @brief    Save a dictionary section to a loadable ini file
  @param    d   Dictionary to dump
  @param    s   Section name of dictionary to dump
  @param    f   Opened file pointer to dump to

  This function dumps a given section of a given dictionary into a loadable ini
  file.  It is Ok to specify @c stderr or @c stdout as output files.
 */
/*--------------------------------------------------------------------------*/

void dictionary_dumpsection_ini(const dictionary * d, const char * s, FILE * f);

/*-------------------------------------------------------------------------*/
/**
  @brief    Dump a dictionary to an opened file pointer.
  @param    d   Dictionary to dump.
  @param    f   Opened file pointer to dump to.

  This function prints out the contents of a dictionary, one element by
  line, onto the provided file pointer. It is OK to specify @c stderr
  or @c stdout as output files. This function is meant for debugging
  purposes mostly.
 */
/*--------------------------------------------------------------------------*/
void dictionary_dump(const dictionary * d, FILE * f);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the number of keys in a section of a dictionary.
  @param    d   Dictionary to examine
  @param    s   Section name of dictionary to examine
  @return   Number of keys in section
 */
/*--------------------------------------------------------------------------*/
int dictionary_getsecnkeys(const dictionary * d, const char * s);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the number of keys in a section of a dictionary.
  @param    d    Dictionary to examine
  @param    s    Section name of dictionary to examine
  @param    keys Already allocated array to store the keys in
  @return   The pointer passed as `keys` argument or NULL in case of error

  This function queries a dictionary and finds all keys in a given section.
  The keys argument should be an array of pointers which size has been
  determined by calling `dictionary_getsecnkeys` function prior to this one.

  Each pointer in the returned char pointer-to-pointer is pointing to
  a string allocated in the dictionary; do not free or modify them.
 */
/*--------------------------------------------------------------------------*/
const char ** dictionary_getseckeys(const dictionary * d, const char * s, const char ** keys);


/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key
  @param    d       Dictionary to search
  @param    key     Key string to look for
  @param    def     Default value to return if key not found.
  @return   pointer to statically allocated character string

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the pointer passed as 'def' is returned.
  The returned char pointer is pointing to a string allocated in
  the dictionary, do not free or modify it.
 */
/*--------------------------------------------------------------------------*/
const char * dictionary_getstring(const dictionary * d, const char * key, const char * def);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key, convert to an int
  @param    d Dictionary to search
  @param    key Key string to look for
  @param    notfound Value to return in case of error
  @return   integer

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the notfound value is returned.

  Supported values for integers include the usual C notation
  so decimal, octal (starting with 0) and hexadecimal (starting with 0x)
  are supported. Examples:

  - "42"      ->  42
  - "042"     ->  34 (octal -> decimal)
  - "0x42"    ->  66 (hexa  -> decimal)

  Warning: the conversion may overflow in various ways. Conversion is
  totally outsourced to strtol(), see the associated man page for overflow
  handling.

  Credits: Thanks to A. Becker for suggesting strtol()
 */
/*--------------------------------------------------------------------------*/
int dictionary_getint(const dictionary * d, const char * key, int notfound);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key, convert to an long int
  @param    d Dictionary to search
  @param    key Key string to look for
  @param    notfound Value to return in case of error
  @return   integer

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the notfound value is returned.

  Supported values for integers include the usual C notation
  so decimal, octal (starting with 0) and hexadecimal (starting with 0x)
  are supported. Examples:

  - "42"      ->  42
  - "042"     ->  34 (octal -> decimal)
  - "0x42"    ->  66 (hexa  -> decimal)

  Warning: the conversion may overflow in various ways. Conversion is
  totally outsourced to strtol(), see the associated man page for overflow
  handling.
 */
/*--------------------------------------------------------------------------*/
long int dictionary_getlongint(const dictionary * d, const char * key, long int notfound);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key, convert to an int64_t
  @param    d Dictionary to search
  @param    key Key string to look for
  @param    notfound Value to return in case of error
  @return   integer

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the notfound value is returned.

  Supported values for integers include the usual C notation
  so decimal, octal (starting with 0) and hexadecimal (starting with 0x)
  are supported. Examples:

  - "42"      ->  42
  - "042"     ->  34 (octal -> decimal)
  - "0x42"    ->  66 (hexa  -> decimal)

  Warning: the conversion may overflow in various ways. Conversion is
  totally outsourced to strtoimax(), see the associated man page for overflow
  handling.

  This function is usefull on 32bit architectures where `long int` is only
  32bit.
 */
/*--------------------------------------------------------------------------*/
int64_t dictionary_getint64(const dictionary * d, const char * key, int64_t notfound);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key, convert to an uint64_t
  @param    d Dictionary to search
  @param    key Key string to look for
  @param    notfound Value to return in case of error
  @return   integer

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the notfound value is returned.

  Supported values for integers include the usual C notation
  so decimal, octal (starting with 0) and hexadecimal (starting with 0x)
  are supported. Examples:

  - "42"      ->  42
  - "042"     ->  34 (octal -> decimal)
  - "0x42"    ->  66 (hexa  -> decimal)

  Warning: the conversion may overflow in various ways. Conversion is
  totally outsourced to strtoumax(), see the associated man page for overflow
  handling.

  This function is usefull on 32bit architectures where `long int` is only
  32bit.
 */
/*--------------------------------------------------------------------------*/
uint64_t dictionary_getuint64(const dictionary * d, const char * key, uint64_t notfound);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key, convert to a double
  @param    d Dictionary to search
  @param    key Key string to look for
  @param    notfound Value to return in case of error
  @return   double

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the notfound value is returned.
 */
/*--------------------------------------------------------------------------*/
double dictionary_getdouble(const dictionary * d, const char * key, double notfound);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the string associated to a key, convert to a boolean
  @param    d Dictionary to search
  @param    key Key string to look for
  @param    notfound Value to return in case of error
  @return   integer

  This function queries a dictionary for a key. A key as read from an
  ini file is given as "section:key". If the key cannot be found,
  the notfound value is returned.

  A true boolean is found if one of the following is matched:

  - A string starting with 'y'
  - A string starting with 'Y'
  - A string starting with 't'
  - A string starting with 'T'
  - A string starting with '1'

  A false boolean is found if one of the following is matched:

  - A string starting with 'n'
  - A string starting with 'N'
  - A string starting with 'f'
  - A string starting with 'F'
  - A string starting with '0'

  The notfound value returned if no boolean is identified, does not
  necessarily have to be 0 or 1.
 */
/*--------------------------------------------------------------------------*/
int dictionary_getboolean(const dictionary * d, const char * key, int notfound);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the section from an associated to a key; keys are saved as `section:key`
  @param    key Key string to look at
  @return   const char*

  Everything before ':' or "".
 */
/*--------------------------------------------------------------------------*/
const char* dictionary_key_getsec(const char * key);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the key from an associated to a key; keys are saved as `section:key`
  @param    key Key string to look at
  @return   const char*

  Everything behind ':' or "".
 */
/*--------------------------------------------------------------------------*/
const char* dictionary_key_getkey(const char * key);

/*-------------------------------------------------------------------------*/
/**
  @brief    Get the section from an associated to a key; keys are saved as `section:key`
  @param    key Key string to look for
  @return   const char*

  The notfound value returned if no boolean is identified, does not
  necessarily have to be 0 or 1.
 */
/*--------------------------------------------------------------------------*/
const size_t dictionary_key_getnpos(const dictionary * d, const char * key);


/*-------------------------------------------------------------------------*/
/**
  @brief    Set an entry in a dictionary.
  @param    ini     Dictionary to modify.
  @param    entry   Entry to modify (entry name)
  @param    val     New value to associate to the entry.
  @return   int     0 if Ok, -1 otherwise.

  If the given entry can be found in the dictionary, it is modified to
  contain the provided value. If it cannot be found, the entry is created.
  It is Ok to set val to NULL.
 */
/*--------------------------------------------------------------------------*/
int dictionary_set(dictionary * ini, const char * entry, const char * val);


/*-------------------------------------------------------------------------*/
/**
  @brief    Delete an entry in a dictionary
  @param    ini     Dictionary to modify
  @param    entry   Entry to delete (entry name)

  If the given entry can be found, it is deleted from the dictionary.
 */
/*--------------------------------------------------------------------------*/
void dictionary_unset(dictionary * ini, const char * entry);

/*-------------------------------------------------------------------------*/
/**
  @brief    Finds out if a given entry exists in a dictionary
  @param    ini     Dictionary to search
  @param    entry   Name of the entry to look for
  @return   integer 1 if entry exists, 0 otherwise

  Finds out if a given entry exists in the dictionary. Since sections
  are stored as keys with NULL associated values, this is the only way
  of querying for the presence of sections in a dictionary.
 */
/*--------------------------------------------------------------------------*/
int dictionary_find_entry(const dictionary * ini, const char * entry) ;

/*-------------------------------------------------------------------------*/
/**
  @brief    Parse an ini file and return an allocated dictionary object
  @param    ininame Name of the ini file to read.
  @return   Pointer to newly allocated dictionary

  This is the parser for ini files. This function is called, providing
  the name of the file to be read. It returns a dictionary object that
  should not be accessed directly, but through accessor functions
  instead.

  Iff the value is a quoted string it supports some escape sequences:

  - \" or ' : the quote character
  (e.g. 'String with "Quotes"' or "String with 'Quotes'")
  - \ : the backslash character (e.g. "C:\tmp")

  Escape sequences always start with a backslash. Additional escape sequences
  might be added in the future. Backslash characters must be escaped. Any other
  sequence then those outlined above is invalid and may lead to unpredictable
  results.

  The returned dictionary must be freed using dictionary_freedict().
 */
/*--------------------------------------------------------------------------*/
dictionary * dictionary_load(const char * ininame);

/*-------------------------------------------------------------------------*/
/**
  @brief    Parse an ini file and return an allocated dictionary object
  @param    in File to read.
  @param    ininame Name of the ini file to read (only used for nicer error messages)
  @return   Pointer to newly allocated dictionary

  This is the parser for ini files. This function is called, providing
  the file to be read. It returns a dictionary object that should not
  be accessed directly, but through accessor functions instead.

  Iff the value is a quoted string it supports some escape sequences:

  - \" or ' : the quote character
  (e.g. 'String with "Quotes"' or "String with 'Quotes'")
  - \ : the backslash character (e.g. "C:\tmp")

  Escape sequences always start with a backslash. Additional escape sequences
  might be added in the future. Backslash characters must be escaped. Any other
  sequence then those outlined above is invalid and may lead to unpredictable
  results.

  The returned dictionary must be freed using dictionary_freedict().
 */
/*--------------------------------------------------------------------------*/
dictionary * dictionary_load_file(FILE * in, const char * ininame);

/*-------------------------------------------------------------------------*/
/**
  @brief    Free all memory associated to an ini dictionary
  @param    d Dictionary to free

  Free all memory associated to an ini dictionary.
  It is mandatory to call this function before the dictionary object
  gets out of the current context.
 */
/*--------------------------------------------------------------------------*/
void dictionary_freedict(dictionary * d);

#ifdef __cplusplus
}

} // namespace dsc
#endif

#endif
