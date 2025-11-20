/**
 * @file cpptensor.hpp
 * @brief A file that defines a `libds` tensor for representing and holding data for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "cpptensor.hpp"


namespace dscpp {

// Forward declaration
template< typename Key, typename T >
class ViewElement;

template< typename KeyType, typename T, typename SubType >
class DataTensor
    :   public dscpp::Tensor< KeyType, T, SubType >::Ordered
{};

} // namespace dscpp
