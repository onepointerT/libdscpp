/**
 * @file ql_dataset.hpp
 * @brief A file that defines a `libds` query language data set for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "cdictionary.hpp"
#include "ql_table.hpp"

#include <string_view>


namespace dscpp {
namespace ql {


class DataSet {
public:
    const std::string name;

    class String
        :   public dscpp::TableElementBase
        ,   public std::string_view
    {
    public:
        String( const char* str );

        virtual operator std::string() const;
    };

    class Selection
        :   public DictionaryC
    {};

    class Sorting
        :   public dscpp::Table< DataSet::String >::Named
    {
    public:
        Sorting();
    };
};


} // namespace ql
} // namespace dscpp
