
#pragma once

#include <concepts>
#include <cstdarg>
#include <functional>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <variant>


namespace dscpp {

/*
namespace details {

template< class V >
using va_arg_as_type = []( const va_list va ) -> std::type_info {
    V v = va_arg( va, V );
    return typeid( V );
};


template< class T, class... Types >
using is_any_of = []() -> bool {
    unsigned int vp = 0;
    va_list va_types = Types...;
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

template< class... Types >
using one_of_t = std::tuple< Types... >;


} // namespace details
*/



template< class... Types >
class BivariativeType
    :   public std::variant< Types... >
{
public:
    const std::type_info& type;

    template< class T >
    //    requires dscpp::details::is_any_of< T, Types... >()
    BivariativeType( T& obj )
        :   std::variant< Types... >( obj )
        ,   type( typeid(T) )
    {}


    template< class T >
    T& get() const {
        return std::get< decltype(std::type_index(this->type)), Types... >( *this );
    }
};


template< class R, class... Types >
class BimonomorphicFunction
    :   public std::function< R (BivariativeType<Types...>&) >
{
protected:
    BivariativeType<Types...>* val;

    friend class BimonomorphicFunction<R, Types...>;
    
public:
    template< class ConcreteParameterType >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >()
    using concrete_function_f = R (*)(ConcreteParameterType&);

    BimonomorphicFunction()
        :   std::function< R (BivariativeType<Types...>&) >( nullptr )
        ,   val( nullptr )
    {}

    template< class ConcreteParameterType >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >()
    BimonomorphicFunction( concrete_function_f<ConcreteParameterType> func )
        :   std::function< R (BivariativeType<Types...>&) >( nullptr )
        ,   val( nullptr )
    {
        this->set_func( func );
    }

    template< class ConcreteParameterType >
    //    requires dscpp::details::is_any_of< ConcreteParameterType, Types... >()
    BimonomorphicFunction( ConcreteParameterType& obj
                         , R (*func)(BivariativeType<Types...>&) = nullptr
    )   :   std::function< R (BivariativeType<Types...>&) >( func )
        ,   val( new BivariativeType<Types...>(obj) )
    {}

    template< class ConcreteParameterType >
    BimonomorphicFunction<R, Types...>& set_param( ConcreteParameterType& obj_param ) {
        this->val = new BivariativeType<Types...>( obj_param );
        return *this;
    }

    template< class ConcreteParameterType >
    BimonomorphicFunction<R, Types...>& set_func( concrete_function_f<ConcreteParameterType>& obj_func ) {
        std::function< R (BivariativeType<Types...>&) >* f
                = new std::function< R (BivariativeType<Types...>&) >(
                            [](BivariativeType<Types...>& obj_param) -> R {
                                decltype(std::type_index(obj_param.type)) obj
                                    = obj_param.get<decltype(std::type_index(obj_param.type))>();
                                return func(obj);
                            }
                );
        this->swap( *f );
        return *this;
    }

    R _( typename BivariativeType< Types... >& obj_param ) {
        return (*this)( obj_param );
    }

    static R operator()( typename BimonomorphicFunction<R, Types...> f ) {
        return f._( f.val );
    }
};


} // namespace dscpp