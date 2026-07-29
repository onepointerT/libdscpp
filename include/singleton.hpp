
#pragma once

#include <memory>


namespace dscpp {
namespace intern {


template< class A >
class Singleton final
{
protected:
    static std::unique_ptr< A > _cls;

    friend class Singleton<A>;

    Singleton() = delete;
    ~Singleton() = delete;

public:
    static A& get() noexcept {
        if ( Singleton<A>::_cls.get() == nullptr ) {
            Singleton<A>::_cls.reset( new A() );
        }
        return *(Singleton<A>::_cls.get());
    }
};


template< class A >
using singleton_get_f = A& (*)(void);

#define register_singleton(type, varname) \
            typedef typename type& varname; \
            inline static type& get_##varname \
                        =  dscpp::intern::Singleton<type>::get();




} // namespace intern
} // namespace dscpp