// Copyright (C) 2026 OnePointer
//

#pragma once

#include "category.hpp"

#include <string>


namespace dscpp {

/** @brief The namespace of ID-tagged data science */
namespace id {


/**
 * @brief The base class NID that represents an identification (primary) key holding a name or an ID.
 */
class NID {
public:
    /** @brief The name or ID of this data */
    const std::string name_or_id;

    /**
     * @brief Constructor.
     * @param nid The name or ID for the current instance
     */
    NID( const std::string nid );

    /** @brief Get the name or ID of this data */
    const std::string id() const;
};


/**
 * @brief The UUID class of `libdscpp`.
 * @note Inherits `dscpp::id::NID`
 */
class UUID
    :   public dscpp::id::NID
{
public:
    /** @brief Get a newly generated UUIDv4 as `std::string` */
    static const std::string v4();

    /** @brief Create a new `dscpp::id::UUID` object. */
    UUID( const std::string uuid = dscpp::id::UUID::v4() );
};


} // namespace id
} // namespace dscpp
