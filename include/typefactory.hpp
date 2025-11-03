/**
 * @file typefactory.hpp
 * @brief A file that defines useful functions for operations on data types for C++.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2025 Sebastian Lau <sebastianlau995@gmail.com>
*/

#pragma once

extern "C" {

}

#include "dataclass.hpp"


namespace dscpp {

/**
 * @brief This class implements functions that are useful for use with `dscpp::DataType`
 */
class TypeFactory {
public:
    /**
     * @brief Get the data type of a `DataClass<InheritingFunctionalCls, DT>`
     * @tparam InheritingFunctionalCls The functional class that adds features on top of `DT`
     * @tparam DT The self-designed data type of your API
     * @param datacls The data class itself
     * @returns A reference to the contained `DT attribute`
     */
    template< typename InheritingFunctionalCls, typename DT >
    static DT& getDT( const typename DataClass<InheritingFunctionalCls, DT> datacls ) {
        return *datacls;
    }
};

} // namespace dscpp
