// Copyright (C) 2026 OnePointer
//

#pragma once

#include "category.hpp"
#include "uuid.hpp"

#include <initializer_list>
#include <string>


namespace dscpp {

/** @brief The namespace of contextual data science */
namespace ctx {

/**
 * @brief The base class context
 */
class Context {
public:
    /** @brief The name or ID of this contextual data */
    const dscpp::id::NID named_id;

    /**
     * @brief Constructor.
     * @param nid The name or ID for the current instance
     */
    Context( const std::string nid = dscpp::id::UUID::v4() );
};


/**
 * @brief A `dscpp::ctx::Context` that can be tagged with categories.
 */
class TaggedContext
    :   public dscpp::ctx::Context
    ,   public dscpp::Category< TaggedContext >
{
public:
    /**
     * @brief Constructor
     * @param il_available_category_names The names of all available categories for tagged contexts
     * @param nid The name or ID for the current instance
     */
    TaggedContext( const std::initializer_list< std::string >& il_available_category_names
                 , const std::string nid = dscpp::id::UUID::v4() );
};

tagged_class( TaggedContext )

} // namespace ctx
} // namespace dscpp
