/**
 * @file map.hpp
 * @brief A file that defines practical structures and short algorithms for std::map and dictionaries.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

#include "cppview.hpp"
#include "datatype.hpp"



namespace dscpp {

template< typename Key, typename T >
class ViewSubGroup
    :   public TensorKind< Key, T, ViewSubGroup< Key, T >* >
{};


template< typename Key, typename T >
class ViewTensor
    :   public DataTensor< KeyType, T, ViewSubGroup< KeyType, T >
{};


template< typename Key, typename T >
class ViewElement
    :   public Element::Base
    ,   public ViewTensor< KeyType, T >
{};



} // namespace dscpp


namespace std {

}

