/**
 * @file ini.hpp
 * @brief A file that defines *.ini dictionaries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibIniC++: A C++/C library for *.ini files and dictionaries.
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/


#include "ql_dataset.hpp"

extern "C" {

}


namespace dscpp {
namespace ql {


DataSet::String::String( const char* str )
    :   dscpp::TableElementBase()
    ,   std::string_view( str )
{}

DataSet::String::operator std::string() const {
    return (std::string) (*this);
}



} // namespace ql
} // namespace dscpp
