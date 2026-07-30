// Copyright (C) 2026 The OnePointer Authors.
//

#pragma once

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
#include <utility>


namespace dscpp {

/**
 * @brief A simple covilant type holding dual values, no covilance with more than two values can be made with this class.
 * @tparam T1 The first type
 * @tparam T2 The second type
 * @tparam compare_cast The type to cast both types `T1` and `T2` to for comparison when sorting in a list.
 */
template< typename T1, typename T2, typename compare_cast = std::string >
class Covilance
{
public:
    /** @brief The type this covilance has as its first type */
    using type = typename T1;
    /** @brief The covariant type this covilance has as its furthermore type */
    using type_covariant = typename T2;

    /**
     * @brief Get the type out of `{ T1, T2 }` that is thus not `T`.
     * @tparam T The type you already have of the covariance.
     * @returns An `std::type_info` with the type of `Covilance<T1, T2>` that is not `T`.
     */
    template< typename T >
    using the_other_type = []() -> std::type_info {
        if ( decltype(T) != decltype(T1) ) return typeid(T1);
        return typeid(T2);
    };

    /**
     * @brief The generic covilance class that is univaritly correlant to another entomoregen
     *      type of the covariance types that are defined by the template parameters of this `Covilant<T1, T2>`.
     * @note A covilant definition of `Covilant<T1, T1>` is not coherent, endomorphistic in spection of the types
     *      and therefore no real covilance, but the type `T1` itself (simply: no bivariance).
     * @tparam T The covariance class of correlativ coherent types `T1` and `T2`. `T` is to be either of the type `T1`
     *      or of the type `T2`.
     * @note Inherits `T` for simplicity at type handling and already-defined functions.
     */
    template< typename T >
    class Class
        :   public T
    {
    public:
        /** @brief Exactly the other type of `{ T1, T2 }` is not `T`. */
        decltype(std::type_index(Covilance<T1, T2>::the_other_type<T>()))& cov;

        /** @brief The other correlant and covilax type of `{ T1, T2 }` that is not `T` */
        using covilant_type = Covilance<T1, T2>::the_other_type<T>();
        /** 
         * @brief Constructor.
         * @param obj1 The object reference to the instance with the type `T1`.
         * @param obj2 The object reference to the instance with the type `T2`.
         * @note If `Covilance<T1, T2>::the_other_type<T>().name() == typeid(T1)`, then the covariant variable
         *      of the current `Covilance<T1, T2>::Class<T>::cov = obj2` and `T( obj1 )`, other way round it would be, if the expr
         *      evaluates to false.
         */
        Class( T1& obj1, T2& obj2 )
            :   T( Covilance<T1, T2>::the_other_type<T>().name() == typeid(T1).name()
                 ? obj1 : obj2 )
            ,   cov( Covilance<T1, T2>::the_other_type<T>().name() == typeid(T1).name()
                 ? obj2 : obj1 )
        {}

        /**
         * @brief A generic typecast operator for the type
         * @tparam Type The type to cast the value of `*this` to.
         * @returns `static_cast<Type>(*this)`
         */
        template< typename Type = T >
        virtual operator Type() const { return static_cast<Type>(*this); }

        /**
         * @brief The specific typecast operator that thus casts the class `T`
         *      of  `Covilance<T1, T2>::Class<T>` to a `std::basic_string<char>`.
         * @returns The instances object of the type `T` as `std::string`.
         */
        template<>
        virtual operator std::basic_string<char>() const { return ((std::string) static_cast<typename T>(*this)); }
    };

    /** 
     * @brief The first of both covilant correlative covilax values, see `Covilance<T1, T2>::Class<T1>`.
     */
    Class< T1 >& first;
    /** 
     * @brief The second of both covilant correlative covilax values, see `Covilance<T1, T2>::Class<T2>`.
     */
    Class< T2 >& second;

    /**
     * @brief Constructor.
     * @param obj1 A reference to first object's data instance of the type `T1`.
     * @param obj2 A reference to first object's data instance of the type `T1`.
     */
    Covilance( T1& obj1, T2& obj2 )
        :   first( *new Class<T1>( obj1, obj2 ) )
        ,   second( *new Class<T2>( obj2, obj1 ) )
    {}

    /**
     * @brief The compare operators for covilant objects
     */
    template< typename T >
    class Compare {
        static bool operator()( const T& t1, const T& t2 ) const {
            return static_cast<compare_cast>(t1) < static_cast<compare_cast>(t2);
        }
        static bool operator()( const T* t1, const T* t2 ) const {
            if ( t2 == nullptr ) return false;
            else if ( t1 == nullptr && t2 != nullptr ) return true;
            else if ( t1 == nullptr ) return false;
            return static_cast<compare_cast>(*t1) < static_cast<compare_cast>(*t2);
        }
        /// @brief  A covilance `covil1` is only smaller than another `covil2`, if both values are 
        ///                in a complete no-partial order, this means no a strict, unweak and complete epimorphistic ordering.
        ///                That means that pairs of {(t11, t12), (t21, t22)} are only to be endomorphistic by coherent value
        ///                and in a strict unweak total ordering.
        static bool operator()( const typename Covilance<T1, T2>& covil1
                              , const typename Covilance<T1, T2>& covil2
        ) const {
            return (*this)( covil1.first, covil2.first ) && (*this)(covil1.second, covil2.second);
        }
    };

    /**
     * @brief Compare if another instance's object of the type `T` holds a value, that is greater or equal 
     *      to the covilax other value.
     * @tparam T The type that the compared value has
     * @returns True, if the covilax type's value of this `Covilance<T1, T2>` is smaller than `other`
     */
    template< typename T >
    bool operator<( const T& other ) const {
        if ( decltype(T) == decltype(T1) ) return Covilance<T1, T2, compare_cast>::Compare<T>(this->first, other);
        else return Covilance<T1, T2, compare_cast>::Compare<T>(this->second, other);
    }
    
    /**
     * @brief Compare two covilances with the same bivariative types
     * @param other The covilance of the same template parameters' type to compare with.
     * @returns `Covilance<T1, T2, compare_cast>::Compare<T1>( *this, other )`.
     */
    template<>
    bool operator<( const typename Covilance<T1, T2, compare_cast>& other ) {
        return Covilance<T1, T2, compare_cast>::Compare<T1>( *this, other );
    }

    /**
     * @brief The list holding one type in a pointer to a `dscpp::ContainerElement<T>`.
     * @tparam T The type of one of the covilant template parameter types.
     */
    template< typename T >
    using list = typename std::list< dscpp::ContainerElement< T >* >;
    /**
     * @brief The list value of the list holding one type in a pointer to a `dscpp::ContainerElement<T>`.
     * @tparam T The type of one of the covilant template parameter types.
     */
    template< typename T >
    using list_value_type = typename list<T>::value_type;
};





/**
 * @brief An BiEtimorphicSorter sorts by one of `_Kty` or `_Val` covariantly the complete list and is then sorted univariatly.
 *      The covilant values are sorted by one type's comparison operator and sorting classing and also the same.
 * @note Have a look at `dscpp::Covilance< _Kty, _Valty >`.
 * @tparam _Kty The key type, that thus means for data science the (unique) ID of the data of `_Valty`
 * @tparam _Valty The data type or data class you make your data science with
 * @tparam compare_cast For comparison of each either `_Kty` or `_Valty` the functions with use the type `compare_cast` for
 *      comparison linn typecasting
 * @tparam VT The covariant class, e.g. an deriving class of `dscpp::Covilance< _Kty, _Valty, compare_cast >`
 * @tparam _LC The list that holds all covilax value pairs. Defaults to `std::unordered_set< VT >`
 * @tparam _Key The covariance type for the keys of the values. Defaults to `typename VT::Class< _Kty >`
 * @tparam _Val The covariance type for the values. Defaults to `typename VT::Class< _Valty >`
 * @tparam _L The list type for each unique, basically firstly and solily inherent type. Keys and values 
 *      are inherent as long as they are
 *      * not in context of each other or coherence tuples
 *      * not referenced by `_LC`, `_Key.cov`, `_Val.cov`
 *      * in covariant comparison, e.g. for the member variable `BietimorphicSorter<_Kty, _Valty>::all`
 *      * if the `_Kty` is not stored in the type `_Valty`
 *      * or used in context of `VT`.
 * @tparam _LK The list of all keys. Defaults to `_L< _Key >`
 * @tparam _LV The list of all keys. Defaults to `_L< _Val >`
 */
template< typename _Kty, typename _Valty
        , typename compare_cast = std::string
        , typename VT = dscpp::Covilance< _Kty, _Valty, compare_cast >
        , class _LC = std::unordered_set< VT >
        , class _Key = typename VT::Class< _Kty >
        , class _Val = typename VT::Class< _Valty >
        , template<typename T> typename _L = VT::list
        , class _LK = typename _L< _Key > // std::list< dscpp::ContainerElement< _Key >* >
        , class _LV = typename _L< _Val > // std::list< dscpp::ContainerElement< _Val >* >
>
class BietimorphicSorter
{
public:
    /** @brief The type all keys have */
    using key_type = typename _Kty;
    /** @brief The type all values */
    using value_type = typename _Valty;
    /** @brief The pair type consisting of (key_type, value_type) */
    using pair_type = typename std::pair< key_type, value_type >;
    /** @brief The covilant type. Defaults to `typename dscpp::Covilance< key_type, value_type, compare_cast >`. */
    using covilant_type = typename dscpp::Covilance< key_type, value_type, compare_cast >;
    /**
     * @brief The list type
     * @tparam T The type that is inside of the list
     */
    template< typename T >
    using list_type = _L< T >;
    /** @brief The list type, the keys are unherently sorted inside */
    using list_type_keys = _LK;
    /** @brief The list type, the values are unherently sorted inside */
    using list_type_values = _LV;
    /** @brief The list type, the (key_type, value_type) pairs are sorted inside coherently to the endologicaly only sorted list out of `keys` or `values`. */
    using list_type_pairs = _LC;
    /** @brief The covariant type of the keys */
    using key_t = typename _Key;
    /** @brief The covariant type of the values */
    using value_t = typename _Val;
    /** 
     * @brief The compare class or struct, invocable with `operator()`. Defaults to `VT::Compare<T>`
     * @tparam T The type that is to be compared
     */
    template< typename T >
    using compare = typename VT::Compare< T >;
    /** @brief This objects type with the template parameters set in for short abbreviation. */
    using self_t = typename BietimorphicSorter< _Kty, _Valty, compare_cast
                                              , VT, _LC, _Key, _Val, _L, _LK, _LV >;

    /** @brief A reference to all (key, value) pairs */
    _LC& all;
    /** @brief All covariant covilant keys, that are thus covariant to the values */
    _LK& keys;
    /** @brief All covariant covilant values, that are thus covariant to the keys */
    _LV& values;

    /** @brief Set to true, if comparison is to be done by comparing the values. */
    bool compare_by_value;
    /** @brief Set to true, if comparison is to be done by comparing the keys. */
    bool compare_by_key;

    /**
     * @brief Constructor. Places all values of `il` in the lists `keys`, `values` and `all` 
     *      and calls `this->sort()`
     * @param il Pair types of values that are to be inside of the list at construction time
     * @param compare_values Set to false, if comparison isn't to be done by comparing the values.
     * @param compare_keys Set to false, if comparison isn't to be done by comparing the keys.
     */
    BietimorphicSorter( const std::initializer_list<pair_type> il
                      , const bool compare_values = true
                      , const bool compare_keys = true
    )   :   all( *new _LC() )
        ,   keys( *new _LK() )
        ,   values( *new _LV() )
        ,   compare_by_value( compare_values )
        ,   compare_by_key( compare_keys )
    {
        for ( typename pair_type p : il ) {
            this->keys.emplace( *new _Key(p.first) );
            this->values.emplace( *new _Val(p.second) );

            typename VT covilance = new VT( p.first, p.second );
            this->all.emplace( covilance );
        }
        this->sort();
    }

    /**
     * @brief Sort the list with the bicorrelant `Covilance< _Kty, _Valty >` values
     * @tparam CT The current type of the unherent incorrelantly sorted list. Can be any of `{ _Key, _Val }`.
     * @tparam LST The sorted list of covilant values that thus is handed in as parameter. Defaults to
     *      `list_type< CT >`
     * @param sorted_list A reference to the sorted list of covilant strictly unweak and totally ordered values
     *      of the type `Covilance< _Kty, _Valty >::Class<T>`.
     * @returns A reference to a sorted `_LC`. The emplacement into `_LC& new_all` is done in the ordering that
     *      thus `const LST& sorted_list` has. Sets `this->all = new_all`
     */
    template< typename CT = _Key, class LST = list_type< CT > >
    virtual _LC& sortAll( const LST& sorted_list ) {
        _LC& new_all = *new _LC();
        for ( const typename LST::value_type* v : sorted_list ) {
            if ( typename CT == typename VT::type )
                new_all.emplace_back( *new VT(static_cast<CT>(*v), static_cast<typename CT::covariant_type>(v->cov)) );
            else if ( typename CT == typename VT::type_covariant )
                new_all.emplace_back( *new VT(static_cast<typename CT::covariant_type>(v->cov), static_cast<CT>(*v)) );
        }
        this->all = new_all;
        return new_all;
    }

    /**
     * @brief Unherently sort one of the covariant list values. Sorting is done uniquely for one list, so that
     *      the reference to a element e.g. `this->keys[0]->cov` unhides the covariant value and makes a binary bivariative
     *      two-laned sorting order, no partial, such that all elements can be found by the currently preferred ordering and
     *      are also sorted as covariant binerent pairs in the list of `this->all`.
     * @note When the attribute `compare_by_key` is not set to false, it will sort by key, otherwise, if and only if
     *      `compare_by_value` is set to true, it will sort by value. No further sortings will be done, if both are false.
     * @note Each of either sorting preference will call `this->sortAll<>()` after sorting its unherence list.
     */
    virtual void sort() {
        if ( this->compare_by_key ) {
            this->keys.sort<typename compare<key_t>>();
            this->sortAll<_Key>( this->keys );
        } else if ( this->compare_by_value ) {
            this->values.sort<typename compare<value_t>>();
            this->sortAll<_Val>( this->values );
        }
    }
};


/**
 * @brief Like `BietimorphicSorter< _Kty, dscpp::BivariativeType< _Valty... >, compare_cast >`.
 * @note Unlike the base classes covilance design, the values are bivariate, that means like in a
 *      `std::variant<_Valty...>` they have one of many specific types.
 */
template< typename _Kty, typename compare_cast, typename... _Valty >
class BivariativeEtimorphicSorter
    :   public BietimorphicSorter< _Kty, dscpp::BivariativeType< _Valty... >, compare_cast >
{};


namespace details {

template< class T, class Tuple >
using tuple_element_index = []() -> size_t {
    const size_t tplsize = std::tuple_size<Tuple>()::value;
    for ( unsigned int ei = 0; ei < tplsize; ei++ ) {
        if ( typeid(T).name() == typeid(std::tuple_element<ei, Tuple>()::type).name() )
            return ei;
    }
    return tplsize;
};


using covariance_error = std::out_of_range;

} // namespace details


/**
 * @brief Coherence and covilance with more than one bilerent (both value equivalence-reference directions surjetive,
 *      bicoherent, covilax and at least bicoherent or completly coherent) value can be written with an enumeration
 *      of types. One type is always covilant to earch other type, if and only if it is included in `Types...`.
 *      Unlike `Covilance<T1, T2>` we will store all covariant values in a `std::tuple< Types... >`.
 * @tparam Types... All types that covilaxly can appear in the covilance value.
 */
template< typename... Types >
class TupleCovilance
    :   public std::tuple< Types... >
{
public:
    /**
     * @brief Check, if a type `T1` is contained in a list of types `Ts...`
     * @tparam T1 The type to check for
     * @param vals_current The `va_list` to check, if `T1` is inside
     * @returns True, if `T1 \in vals_current`
     */
    template< typename T1, typename... Ts >
    using is_contained = [](va_list vals_current) -> bool {
        
        template< typename TCurrent >
        using in_valist_fi = []() -> bool {
            return typeid(typename T1).name() == typeid(typename TCurrent).name();
        };

        for ( unsigned tsc = 0; tsc < sizeof...(Ts...); tsc++ ) {
            if ( in_valist_fi<Ts...[tsc]>() ) return true;
        }

        return false;
    };

    /**
     * @brief Get every type of a templated `va_list Ts...`, except the one of `T`.
     * @tparam T The type may it be in va_list `Ts...` or not, not to get inside the newly returned `va_list`
     * @tparam Ts... The complete list of types
     * @returns A `va_list` that contains all types of `Ts...` except `T`.
     */
    template< typename T, typename... Ts >
    using the_rest_of = []() -> va_list {
        

        template< typename TNot >
        using get_one_more_fi = [](va_list vals) -> std::add_rvalue_reference<TNot> {
            unsigned int cinner = 0;
            va_start( vals, cinner );
            for ( unsigned int cv = 0; cv < sizeof...(Ts...); cv++ ) {
                if ( is_contained<Ts...[cv]>(vals) ) continue;
                else if ( typeid(Ts...[cv]).name() == typeid(T).name() ) continue;
                else {
                    return decltype(Ts...[cv]);
                }
            }
            va_end( vals );
            return decltype(nullptr_t);
        };

        unsigned int c = 0;
        va_list va;
        va_start( va, c );
        while ( c+1 < sizeof...(Ts...) - 2 ) {
            va[c+1] = decltype( typename (get_one_more_fi(va)::type) );
            ++c;
        }
        va_end( va );
        
        return va;
    };

    /**
     * @brief Get the type following `TCurrent` inside of `Ts...`
     * @tparam TCurrent The current type that is followed by another or may be the last inside of `Ts...`
     * @tparam Ts... The complete list of types.
     * @returns A one-element-long `va_list` or an empty `va_list`.
     */
    template< typename TCurrent, typename... Ts >
    using the_next_of = []() -> va_list {
        for ( unsigned int c = 0; c < sizeof...(Ts...) - 1; c++ ) {
            if ( decltype(Ts...[c]) == decltype(TCurrent) ) {
                return { Ts...[c+1] };
            }
        }
        return {};
    };

    /**
     * @brief Check if a type `TCurrent` is in a set of types `Ts...`
     * @tparam TCurrent The type to check for
     * @tparam Ts... The complete set of types to check for the type `TCurrent`
     * @returns True, if `TCurrent` can be found in `Ts...`
     */
    template< typename TCurrent, typename... Ts >
    using is_in_typeset = []() -> bool {
        return the_rest_of<TCurrent, Ts...>() < sizeof...(Ts...);
    };

    /**
     * @brief The type the univariant covilax value of this class coherently has to all other types
     * @tparam TCls The type the value of the class has
     * @tparam TOthers Defaults to `the_rest_of<TCls, Ts...>()`, thus all coherence types of `TCls`. All covilant
     *      coherence types are stored in a `std::tuple<TOthers...>& cov` 
     * @note Inherits `TCls` for simplicity at type handling and already-defined functions.
     */
    template< typename TCls, typename... TOthers = the_rest_of<TCls, Ts...>() >
    class Class
        :   public TCls
    {
    public:
        /** @brief All covariant types as a `std::tuple< TOthers... >` */
        std::tuple< TOthers... >& cov;

        /** @brief The other correlant and covilax types, this thus means all types of `Ts...` except `TCls`
         *      for generic purposes.
         */
        using covilant_types = TOthers...;

        /**
         * @brief Constructor.
         */
        Class()
            :   TCls()
            ,   cov( *new std::tuple< TOthers... >() )
        {}

        /**
         * @brief A generic typecast operator for the type
         * @tparam Type The type to cast the value of `*this` to.
         * @returns `static_cast<Type>(*this)`
         */
        template< typename Type = TCls >
        virtual operator Type() const { 
            if ( decltype(Type) == decltype(TCls) )
                return static_cast<Type>(*this);
            else if ( is_in_typeset<Type, TOthers...>() )
                std::size_t I = details::tuple_element_index<Type, decltype(std::type_index(typeid(this->cov)))>
                typename Type& obj = std::get<Type, TOthers...>(this->cov);
                return obj;
            throw new details::covariance_error("The type '" + typeid(Type).name() + "' is not be found for this covilance.");
        }

        /**
         * @brief The specific typecast operator that thus casts the class `T`
         *      of  `Covilance<T1, T2>::Class<T>` to a `std::basic_string<char>`.
         * @returns The instances object of the type `T` as `std::string`.
         */
        template<>
        operator std::basic_string<char>() const { return ((std::string) static_cast<typename TCls>(*this)); }

        template< typename Type = T, typename... Ts = the_rest_of<Type, Types...> >
        void set( const typename Type& obj, const std::tuple< Ts... >& obj_coherent_others ) {
            this->swap( obj );
            this->cov.swap( obj_coherent_others );
        }
    };

    /**
     * @brief Declare a member attribute of the type `TupleCovilance< Types... >::Class< TCurrent >&` with the name of the
     *      type `TCurrent` (this thus means `std::tolower(typeid(TCurrent).name())`) and create a new instance with this univariative name.
     * @tparam T The current variadicaly declared type, once out of  `Types...`
     * @tparam TCurrent The type to declare now
     * @tparam TRest Like `TOthers...` in `dscpp::TupleCovilance< Types... >::Class< typename TCurrent, the_rest_of<TCurrent, Types...> >`,
     *      all covilaxly coherent types, each out of `Types...`, except `TCurrent`.
     * @note Can be called by a loop function to declare each covilance type for the class or have all inherent uniquely types, each out
     *      of `Types...` settable as `typename dscpp::TupleCovilance< Types... >::Class< typename TCurrent, TRest... >&` variable with
     *      the variable name of `std::tolower(typeid(TCurrent).name())`
     */
    template< typename T, typename TCurrent = the_next_of<T, Types...>(), typename... TRest = the_rest_of<TCurrent, Types...>() >
    concept next_variadic_covariance_cls = requires () {
        if ( sizeof...(TRest...) > 0 
          && sizeof...(TRest...) < sizeof...(Types...)
          && typeid(typename TCurrent).name() != typeid(typename T).name()
        ) {
            typename dscpp::TupleCovilance< Types... >::Class< typename TCurrent, TRest... >&
                std::declval(std::tolower(typeid(typename TCurrent).name()))
                    = *new dscpp::TupleCovilance< Types... >::Class< TCurrent, TRest... >();
        }
    };

    /**
     * @brief The loop for `next_variadic_covariance_cls()`. Does exactly what is written in the note there, once
     *      per each type of `Types...`
     */
    using decl_each_covilant_cls = [&]() {
        for ( unsigned int t = 0; t < sizeof...(Types...); t++ ) {
            if ( t == 0 ) next_variadic_covariance_cls_decl< Types...[0] >();
            else next_variadic_covariance_cls_decl< Types...[t-1], Types...[t] >();
        }
    };

    /**
     * @brief Declares per each type `T` out of the set of types `Types...` a variable, like
     *      `typename TupleCovilance< Types... >::Class< Tn >& tn
     *              = *new TupleCovilance< Types... >::Class< Tn >();
     */
    decl_each_covilant_cls();

/** 
 * @brief Get the univariat variable's name of a type
 * @param type The coherence type inside this class you look for it's class member attribute.
 * @returns `std::tolower(typeid(type).name())`
 */
#define get_varname(type) std::tolower(typeid(type).name())

/**
 * @brief Set the members values of a member attribute of a coherent covilax type's class of this `TupleCovilance`
 * @param cls A pointer to the class instance holding the member attribute
 * @param value The value to set it to
 * @param other_values The values that are covilant to `value`
 * @param type The type of the value
 * @param other_types The types of all covilax and coherent other values
 */
#define set_member_val(cls, value, other_values, type, other_types) \
    cls->(get_varname(type)).set<type, other_types...>(value, other_values);
    
    /**
     * @brief Get the value of a specific specified type out of a tuple
     * @tparam TCurrent The type to extract
     * @param tpl The `std::tuple<Types...>` to extract the value of the type `TCurrent` from
     * @returns A pointer to the value or, if no value of the type `TCurrent` is found in `tpl`, a nullptr thus.
     */
    template< typename TCurrent >
    using get_only = []( const std::tuple<Types...>& tpl ) -> TCurrent* {
        if ( std::tuple_size_v<Types...> == details::tuple_element_index<TCurrent, Types...>() ) return nullptr;
        return std::get< TCurrent, Types... >(tpl);
    };

/**
 * @brief Get the value in the covilance class `cls` of a specific unherent starting type
 * @param cls The class instance of the type `TupleCovilance<Types...>*`
 * @param type The covariat type out of the set of types `Types...` such that has an univariative
 *      coherence member attribute in the class `cls`
 * @returns `cls->(get_varname(type));`
 */
#define get_univariant_value(cls, type) cls->(get_varname(type));

    /**
     * @brief Get all tuple values of a tuple except the one with the type `TCurrent`.
     * @tparam TCurrent The type to exclude out of the set of types `Types...`
     * @param tpl A reference to a tuple of the type `std::tuple<Types...>`
     * @returns A pointer to a tuple of the type `std::tuple<the_rest_of<TCurrent, Types...>>` on success
     */
    template< typename TCurrent >
    using get_others = []( const std::tuple<Types...>& tpl ) -> std::tuple<the_rest_of<TCurrent, Types...>>* {
        std::tuple<the_rest_of<TCurrent, Types...>>* new_tpl
            = std::tuple<the_rest_of<TCurrent, Types...>>();
        std::tuple& tmp;
        for ( unsigned int t = 0; t < sizeof...(Types...); t++ ) {
            if ( typeid(TCurrent).name() == typeid(Types...[t]).name() ) continue;
            tmp = std::tuple_cat( *new_tpl, std::tie(Types...[t]) );
        }
        new_tpl->swap( tmp );
        return new_tpl;
    }

    /**
     * @brief Set the values of all covilant member attribute classes of this instance
     */
    using set_values_of_member_types = [&]() {
        template< typename TCurrent > 
        using set_value_of_member_fi = [&]() {
            set_member_val(this, get_only<TCurrent>(*this), get_others<TCurrent>(*this), typename TCurrent, the_rest_of<TCurrent>())
        };
        for ( unsigned int t = 0; t < sizeof...(Ts...); t++ ) {
            set_value_of_member_fi<Ts...[t]>();
        }
    };

    /**
     * @brief Constructor.
     * @param objs A reference to the values of this tupled covilance instance.
     */
    TupleCovilance( Types&... objs )
        :   std::tuple< Types... >( objs )
    {
        set_values_of_member_types();
    }

    /**
     * @brief The type of a coherence class of this covilance instance, unherently holding all coherences to the type `T`
     * @tparam T The type out of the set of types `Types...` that you want the coherence class of
     * @note Factically this has the type `typename TupleCovilance<Types...>::Class<T, the_rest_of<T, Types...>()>`.
     */
    template< typename T >
    using coherence_class = typename TupleCovilance<Types...>::Class<T, the_rest_of<T, Types...>()>;

    /**
     * @brief Get the coherence class of a specific type of all types taking apart in this covilance
     * @tparam T The type that you want to have its' coherence class of
     * @returns The coherence class that thus has the type `typename coherence_class<T>`
     */
    template< typename T >
    typename coherence_class<T>* get() const {
        if ( ! is_in_typeset<T, Types...>() ) return nullptr;
        return &(get_univariant_value(this, typename T));
    }
};


/**
 * @brief A sorter and list for compliance with `dscpp::TupleCovilance< _Valty... >`.
 * @tparam _Kty The type of the key/ID values
 * @tparam _Valty... The types that a covilant coherences at the variadic multivariative type
 *      `dscpp::TupleCovilance< _Valty... >`.
 */
template< typename _Kty, class... _Valty >
class MultivariativeEtimorphicSorter
    :   public BietimorphicSorter< _Kty, std::tuple< _Valty... >, std::string
                                , dscpp::TupleCovilance< _Valty... > >
{};

} // namespace dscpp


namespace std {
template< typename T1, typename T2, typename compare_cast = std::string >
using covilance = typename dscpp::Covilance< T1, T2, compare_cast >;

template< typename _Kty, typename _Valty
        , typename compare_cast = std::string
        , typename VT = dscpp::Covilance< _Kty, _Valty, compare_cast >
        , class _LC = std::unordered_set< VT >
        , class _Key = typename VT::Class< _Kty >
        , class _Val = typename VT::Class< _Valty >
        , template<typename T> typename _L = VT::list
        , class _LK = typename _L< _Key > // std::list< dscpp::ContainerElement< _Key >* >
        , class _LV = typename _L< _Val > // std::list< dscpp::ContainerElement< _Val >* >
>
using bisorting_set = dscpp::BietimorphicSorter< _Kty, _Valty, compare_cast
                                               , VT, _LC, _Key, _Val, _L, _LK, _LV >;

template< typename _Kty, typename _Valty >
using covilant_set = typename std::bisorting_set< _Kty, _Valty >;

template< typename _Kty, typename compare_cast = std::string, typename... _Valty >
using bivariate_set = dscpp::BivariativeEtimorphicSorter< _Kty, _Valty, compare_cast >;



template< typename... Types >
using tuple_covilance = typename dscpp::TupleCovilance< Types... >;


template< typename _Kty, typename compare_cast = std::string, typename... _Valty >
using multivariative_set = typename std::bivariative_set< _Kty, compare_cast, std::tuple_covilance< _Valty... > >;
} // namespace std