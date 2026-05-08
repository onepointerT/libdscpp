// Copyright (C) 2026 OnePointer
//

#pragma once

#include "cppvariant.hpp"

#include <string>
#include <string_view>


namespace dscpp {
namespace json {

// Declarations
using JsonKey = std::string;
using JsonString = std::string_view;
// Forward declarations
class JsonList;
class JsonMap;


class JsonValue
    :   public dscpp::VariantValue< JsonKey, JsonList, JsonMap, JsonString >
{};


class JsonList
    :   public dscpp::VariantList< JsonKey, JsonList, JsonMap, JsonString >
{};


class JsonMap
    :   public dscpp::VariantMap< JsonKey, JsonValue, JsonList, JsonMap >
{};


} // namespace json
} // namespace dscpp
