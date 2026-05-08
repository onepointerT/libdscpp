// Copyright (C) 2026 OnePointer
//

#pragma once

#include "category.hpp"
#include "information.hpp"


namespace cocu {


class MetaInformation
    :   public dscpp::Information
    ,   public dscpp::Category< MetaInformation >
{
public:
    const Category& category;

    MetaInformation();
};


} // namespace cocu
