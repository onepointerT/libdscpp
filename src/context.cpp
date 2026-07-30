/**
 * @file context.hpp
 * @brief A file that defines contexts for (optionally: tagged) data.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2026 Sebastian Lau <sebastianlau995@gmail.com>
*/


#include "context.hpp"

extern "C" {

}


namespace dscpp {
namespace ctx {


Context::Context( const std::string nid )
    :   named_id( nid )
{}


TaggedContext::TaggedContext( const std::initializer_list< std::string >& il_available_category_names
                            , const std::string nid
)   :   Context( nid )
    ,   Category( il_available_category_names )
{}


} // namespace ctx
} // namespace dscpp
