#include <functional>

extern "C"
{
#include "libdill.h"
#undef coroutine
#undef go
}

namespace dill
{

template <typename CT, typename ... A> struct coroutine_t
: public coroutine_t<decltype(&CT::operator())(A...)> {};

template <typename C> struct coroutine_t<C> {
private:
    C mObject;
    int32_t m_handle;

public:
    template<typename... Args> 
    coroutine_t(const C & obj, Args&&... args)
        : mObject(obj), m_handle(-2) {
            go(args...);
        }

private:
    template<typename... Args> typename
    std::result_of<C(Args...)>::type __attribute__((noinline)) go(Args... a) {
        m_handle = go_(this->mObject.operator()(a...), NULL, 0, -1);
    }

    template<typename... Args> typename
    std::result_of<const C(Args...)>::type __attribute__((noinline)) go(Args... a) const {
        m_handle = go_(this->mObject.operator()(a...), NULL, 0, -1);
    }
};

template<typename C, typename... Args> auto go(const C & obj, Args&&... args) {
    auto c = coroutine_t<C>(obj, args...);
    //c.go( args... );
    return c;
}

}
