/**
 * @file cpptensor.hpp
 * @brief A file that defines a `libds` tensor for containing data for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "cppmap.hpp"
#include "cpptable.hpp"
#include "cppvector.hpp"

#include <concepts>
#include <type_traits>


namespace dscpp {

template< typename KeyType, typename T >
class TensorSubtypeBase {
public:
    KeyType key;
    T& values;

    T& data() { return this->values; }
};

namespace details {
template< typename KT, typename T, typename ST >
concept is_tensor_container = requires ( ST& st ) -> bool {
      std::is_base_of< dscpp::Map< KT, T >, ST >::value
    || std::is_base_of< dscpp::Vector< T >, ST >::value;
};

template< typename KT, typename T, typename ST >
concept is_tensor_subtype = requires ( ST& st ) -> bool {
    is_tensor_container< KT, T, ST > && std::is_base_of< TensorSubtypeBase< KT, T >, ST >::value;
};
} // namespace details


template< class Key, class T, class SubTensorT >
    requires details::is_tensor_container< Key, T, SubTensorT >
class TensorKind
    :   public Table<T>::SubOrdering< Key, SubTensorT >
    ,   public TensorSubtypeBase< Key, T >
{};


namespace details {
template< typename KT, typename T, class SubTensorT >
concept is_tensor_kind = requires ( SubTensorT& stt ) -> bool {
    is_tensor_container< KT, T, SubTensorT > && std::is_base_of< TensorKind< KT, T, SubTensorT >,, SubTensorT >::value;
};
} // namespace details


template< typename KeyType, typename T, class SubType >
    requires details::is_tensor_kind< KeyType, T, SubType >
class Tensor {
public:
    template< class MV_Compare, class ST_Compare >
    class Simple
        :   public dscpp::MMap< KeyType, dscpp::MultiVector< SubType, ST_Compare >, MV_Compare >
    {

    };

    class Ordered
        :   public Table<T>::SortingKind<KeyType, SubType>
    {

    };
};


} // namespace dscpp
