// Copyright (C) 2026 OnePointer
//

#pragma once

#include <list>
#include <map>
#include <string>


namespace dscpp {


template< class SubClass >
class Category
    :   protected std::string
{
public:
    static std::list< std::string > cnames;
    static std::map< std::string, Category* > categories;

    Category( const std::string cname );

    operator std::basic_string_view<char>() const;
};


} // namespace dscpp
