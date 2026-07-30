// Copyright (C) 2026 OnePointer
//

#pragma once

#include <initializer_list>
#include <list>
#include <map>
#include <string>


namespace dscpp {


/**
 * @brief A category for a subclass. A `SubClass` type can be tagged with different specific
 *      categories that are holden by a `static map` and a generic `static inline list` with all category names.
 * @tparam SubClass The type the subclass has.
 * @note On more information on what this class does, have a insight on tagged data at some time.
 * @
 */
template< class SubClass >
class Category
{
public:
    /** @brief A subclass-independent list of category names */
    static inline std::list< std::string > cnames;
    /** @brief A map of all categories available for `Category< SubClass >` */
    static std::map< std::string, Category* > categories_available;

    /** @brief The name of this category tag */
    const std::string category_name;
    /** @brief The list of all categories of this category tag or this inheriting `SubClass` */
    std::list< Category* > categories_current;

    /** 
     * @brief Constructor. Adds it to `Category::cnames` and `Category<SubClass>::categories_available`,
     *      if not yet contained.
     * @param cname The name of the new category
     */
    Category( const std::string cname )
        :   category_name( cname )
        ,   categories_current()
    {
        if ( ! Category< SubClass >::cnames.contains( cname ) )
            Category< SubClass >::cnames.emplace( cname );
        Category< SubClass >::categories_available[cname] = this;
    }
    /** 
     * @brief Constructor. Adds each name to `Category::cnames` and `Category<SubClass>::categories_available`,
     *      if not yet contained.
     * @param il_available_category_names The names of all available categories for `Category< SubClass >`
     */
    Category( const std::initializer_list< std::string >& il_available_category_names )
        :   category_name( cname )
        ,   categories_current()
    {
        for ( const std::string s : il_available_category_names ) { Category<SubClass>* csc = new Category( s ); }
    }
    /**
     * @brief Copy-constructor.
     * @param category The category to copy from
     */
    Category( const Category& category )
        :   category_name( category.category_name )
        ,   categories_current( category.categories_current )
    {
        Category< SubClass >::categories_available[ category.category_name ] = &category;
    }

    /**
     * @brief Get this category as `std::string_view`
     * @returns In the base class version it returns `this->category_name`.
     */
    virtual operator std::basic_string_view<char>() const { return this->category_name; }

    /**
     * @brief Add category tags to the current inheriting class.
     * @param il_add_category An initializer list with string values. If the category is found for the availability
     *      of category tags for this subclass, it will be added to `this->categories_current`.
     * @returns `*this`
     */
    virtual Category<SubClass>& operator<<( const std::initializer_list<std::string>& il_add_category ) {
        for ( const std::string s : il_add_category ) {
            if ( Category::categories_available.count(s) > 0 )
                this->categories_current.emplace_back( *new Category<SubClass>(Category::categories_available.at(s)) );
        }
        return *this;
    }

    /**
     * @brief Remove category tags to the current inheriting class.
     * @param il_rm_category An initializer list with string values. If the category is found for the current
     *      category tags for this subclass, it will be removed from `this->categories_current`.
     * @returns True, if `count(removed) == il_rm_category.size()`
     */
    virtual bool remove_current_categories( const std::initializer_list<std::string>& il_rm_category ) {
        unsigned int c = 0;
        for ( const std::string s : il_rm_category ) {
            for ( typename std::list< Category* >::iterator it : { this->categories_current.begin()
                                                                 , this->categories_current.end() }
            ) {
                if ( it->category_name == s ) {
                    this->categories_current.remove( *it );
                    ++c;
                    break;
                }
            }
        }
        return c == il_rm_category.size();
    }
};

/**
 * @brief Make your class a tagged class that initializes all `(inline) static` members.
 */
#define tagged_class(type) \
            template type dscpp::Category< type >::cnames; \
            template type dscpp::Category< type >::categories_available; \
            \


} // namespace dscpp
