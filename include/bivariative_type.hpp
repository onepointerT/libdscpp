// Copyright (C) 2026 The OnePointer Authors.
//

#pragma once

#include "cppvector.hpp"
#include "cpputils.hpp"

#include <concepts>
#include <cstdarg>
#include <cstring>
#include <functional>
#include <list>
#include <stdexcept>
#include <string>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <unordered_set>
#include <utility>
#include <variant>


namespace dscpp {


namespace details {

/**
 * @brief Get the next argument from the `va_list` as `std::type_info`
 * @tparam The class, thus the current call to `va_arg` returns. Will be substituted
 *      by preprocessor and compiler.
 * @param va The `va_list` with `va_start` already called.
 * @returns A `std::type_info` holding the type information introspecting on `va_arg( va, V )`.
 */
template< class V >
using va_arg_as_type = []( const va_list va ) -> std::type_info {
    V v = va_arg( va, V );
    return typeid( V );
};


/**
 * @brief Test, if a type `T` is any of `Types...`
 * @tparam T The type to test for
 * @tparam Types... The types that thus shall or could contain `T`, e.g. all types of a
 *      `std::tuple< Types... >` or a `std::variant< Types... >`.
 * @returns True, if `T` is contained in `Types...`
 */
template< class T, class... Types >
using is_any_of_f = []() -> bool {
    unsigned int vp = 0;
    va_list va_types = va_list( Types... );
    va_start( va_types );
    const int count = va_arg( va_types, int );
    for ( int vi = 0; vi < count; vi++ ) {
        const std::type_info& ctype
                = dscpp::details::va_arg_as_type( va_types );
        if ( typeid(T).name() == ctype.name() ) return true;
    }
    va_end( va_types );
    return false;
};

template< class T, class... Types >
concept is_any_of = requires (T t, Types... types) -> bool {
    dscpp::details::is_any_of_f< T, Types... >();
};

/**
 * @brief Generic type that holds one type of `Types...`
 * @tparam Types... The types that can be holded by the `std::tuple< Types... >`
 */
template< class... Types >
using one_of_t = std::tuple< Types... >;

/**
 * @brief An exception that shall be thrown, when the current type is unaccepted by a bimonomorphic type or function.
 */
using type_unaccepted = std::bad_function_call;
} // namespace details



/**
 * @brief Class, that thus handles generic multivariative types and holds one of them.
 * @tparam Types... All types that are predictable for the current instance or inheriting class
 * @note Inherits `std::variant< Types... >`.
 */
template< class... Types >
class BivariativeType
    :   public std::variant< Types... >
{
public:
    /** @brief The `std::type_info` on and about the currently contained object */
    const std::type_info& type;

    /**
     * @brief Constructor.
     * @tparam T The type this `BivariativeType< Types... >` containes
     * @param obj A reference to a valid object of the type `T`
     */
    template< class T >
    //    requires dscpp::details::is_any_of< T, Types... >
    BivariativeType( T& obj )
        :   std::variant< Types... >( obj )
        ,   type( typeid(T) )
    {}

    /**
     * @brief Get the contained object or value as reference
     * @tparam The type can be gotten here. Will be substituted by preprocessor and compiler.
     * @returns A pointer to the holden object of the type `T`, if `T` is currently holden by this instance
     *      of `BivariativeType< Types... >`. `T` is a subset and one of `Types...` and will be substituted at
     *      compile-time by `decltype(std::type_index(this->type))`.
     */
    template< class T >
    T* get() const {
        if ( std::holds_alternative< decltype(std::type_index(this->type)), Types... >( *this ) )
            return &(std::get< decltype(std::type_index(this->type)), Types... >( *this ));
        return nullptr;
    }

    /**
     * @brief Set the contained object or value as reference
     * @tparam The type can be gotten here. Will be substituted by preprocessor and compiler.
     * @param obj A reference to the object of the type `T`. `T` is a subset and one of `Types...`.
     */
    template< class T >
    //    requires dscpp::details::is_any_of< T, Types... >
    void set( T& obj ) {
        *this = obj;
    }
};


/**
 * @brief A bimonomorphic function can accept any argument of a `BivariativeType<Types...>` as concrete
 *      parameter, such that it is deterministicaly predictable, which parameter types can appear, but
 *      since their appearing happens later, they can be omitted as long as the function is not called for
 *      bivariate enkomorphic types.
 * @tparam R The return value of the function
 * @tparam Types... All types that such can appear as parameter
 * @note Inherits `std::function< R (BivariativeType<Types...>&) >`
 */
template< class R, class... Types >
class BimonomorphicFunction
    :   public std::function< R (BivariativeType<Types...>&) >
{
protected:
    /** @brief The value the function's parameter currently has */
    BivariativeType<Types...>* val;

    friend class BimonomorphicFunction<R, Types...>;
    
public:
    /** 
     * @brief If to be ensured, you can also set a function, that only accepts a
     *      `ConcreteParameterType` out of `Types...`. We call this a `concrete_function_f`.
     * @tparam ConcreteParameterType One type of the types contained in `Types...`.
     */
    template< class ConcreteParameterType >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >()
    using concrete_function_f = R (*)(ConcreteParameterType&);

    /**
     * @brief Constructor with default empty values set.
     */
    BimonomorphicFunction()
        :   std::function< R (BivariativeType<Types...>&) >( nullptr )
        ,   val( nullptr )
    {}

    /** 
     * @brief Constructor with a concrete function set.
     * @tparam ConcreteParameterType One type of the types contained in `Types...`.
     * @param func A `concrete_function_f<ConcreteParameterType>` to set for this object.
     * @param param A pointer to the parameter for the first call, defaults to `nullptr`
     */
    template< class ConcreteParameterType >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >()
    BimonomorphicFunction( concrete_function_f<ConcreteParameterType> func
                         , ConcreteParameterType* param = nullptr
    )   :   std::function< R (BivariativeType<Types...>&) >( nullptr )
        ,   val( param == nullptr ? nullptr : new BivariativeType<ConcreteParameterType>(*param) )
    {
        this->set_func( func );
    }

    /** 
     * @brief Constructor with a generic bimonomorphic function set.
     * @tparam ConcreteParameterType One type of the types contained in `Types...`.
     * @param func A `concrete_function_f<ConcreteParameterType>` to set for this object.
     * @param param A pointer to the parameter for the first call, defaults to `nullptr`
     */
    template< class ConcreteParameterType >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >
    BimonomorphicFunction( R (*func)(BivariativeType<Types...>&) )
        :   std::function< R (BivariativeType<Types...>&) >( func )
        ,   val( new BivariativeType<ConcreteParameterType>(obj) )
    {}

    /** 
     * @brief Set the parameter for the next function call
     * @tparam ConcreteParameterType One type of the types contained in `Types...`.
     * @param obj_param A reference to the parameter for the next call, has to have the type `ConcreteParameterType`.
     */
    template< class ConcreteParameterType >
    BimonomorphicFunction<R, Types...>& set_param( ConcreteParameterType& obj_param ) {
        this->val = new BivariativeType<ConcreteParameterType>( obj_param );
        return *this;
    }

    /** 
     * @brief Set the concrete function for the next function call
     * @tparam ConcreteParameterType One type of the types contained in `Types...`.
     * @param obj_func A reference to the `concrete_function_f<ConcreteParameterType>` which will be wrapped into a generic
     *      bimonomorphic function, that only accepts a specific type out of the non-union set `Types...`
     */
    template< class ConcreteParameterType >
    BimonomorphicFunction<R, Types...>& set_func( concrete_function_f<ConcreteParameterType>& obj_func ) {
        std::function< R (BivariativeType<Types...>&) >* f
                = new std::function< R (BivariativeType<Types...>&) >(
                            [](BivariativeType<Types...>& obj_param) -> R {
                                typename ConcreteParameterType* obj
                                    = obj_param.get<ConcreteParameterType>();
                                if ( obj == nullptr ) throw new dscpp::details::type_unaccepted();
                                return obj_func(obj);
                            }
                );
        this->swap( *f );
        return *this;
    }

    /** 
     * @brief Set the concrete function for the next function call
     * @param obj_func A reference to the function that accepts the bivaritive type as parameter.
     */
    BimonomorphicFunction<R, Types...>& set_func( R (*obj_func)(BivariativeType<Types...>&) ) {
        this->swap( *obj_func );
        return *this;
    }
    
    /** 
     * @brief Call the current instance's function with a object parameter of the type `BivariativeType<Types...>`.
     * @param obj_param A reference to the parameter that the function accepts.
     * @returns The result value of the type `R` returned by the function that thus this instance holds.
     */
    R _( typename BivariativeType< Types... >& obj_param ) {
        return (*this)( obj_param );
    }

    /** 
     * @brief Call the current instance's function with a object parameter of the type `BivariativeType<Types...>`.
     * @tparam T One type out of the non-union set `Types...`
     * @param obj_param A reference to the parameter that the function accepts.
     * @returns The result value of the type `R` returned by the function that thus this instance holds.
     */
    template< typename T >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >
    R _( T& obj_param ) {
        typename BivariativeType< Types... >& tobj = *new BivariativeType< T >( obj_param );
        return this->_( tobj );
    }
};


} // namespace dscpp


namespace std {
template< class... Types >
using bivariative_type = typename BivariativeType< Types... >;

template< class R, class... Types >
using bimonomorphic_function = typename BimonomorphicFunction< T, Types... >;
} // namespace std