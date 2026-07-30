/**
 * @file uuid.hpp
 * @brief A file that defines named IDs for data.
 * @author Sebastian Lau <sebastianlau995 [at] gmail [dot] com>
 **/
/*
    LibDataScienceC++: A C++/C library for data science processing and data design
    Copyright (C) 2026 Sebastian Lau <sebastianlau995@gmail.com>
*/


#include "uuid.hpp"

#include <random>

#include <uuid_v4.h>

extern "C" {

}


namespace dscpp {
namespace id {


NID::NID( const std::string nid )
    :   name_or_id( nid )
{}


const std::string NID::id() const {
    return this->name_or_id;
}


const std::string UUID::v4() {
    UUIDv4::UUIDGenerator<std::mt19937_64> uuidGenerator;
    const UUIDv4::UUID uuid = uuidGenerator.getUUID();
    return uuid.str();
}


UUID::UUID( const std::string uuid )
    :   dscpp::id::NID( uuid )
{}


} // namespace ctx
} // namespace dscpp
