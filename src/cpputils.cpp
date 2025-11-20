/**
 * @file cpputils.hpp
 * @brief A file that defines *.ini dictionaries for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/


#include "cpputils.hpp"

extern "C" {

}


namespace dscpp {

Element::Base::Base()
    :   Element::UnnamedBase()
    ,   name()
{}

Element::Base::Base( const std::string key )
    :   Element::UnnamedBase()
    ,   name()
{}

Element::Base::operator std::string() const {
    return this->name;
}

} // namespace dscpp
