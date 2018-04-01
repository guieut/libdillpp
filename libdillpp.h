#include <functional>
#include <system_error>
#include <vector>

extern "C"
{
#include "libdill.h"
#undef coroutine
#undef go
}

namespace dill
{

class coroutine {
private:
    int32_t m_handle;

public:
    
    coroutine(coroutine&& coro) noexcept;

    template<typename C, typename... Args> 
    coroutine(const C & obj, Args&&... args)
    : m_handle(-2)
    {
        try
        {
            m_handle = go_(obj.operator()(args...), NULL, 0, -1);
        }
        catch(...)
        {
        }

        if (m_handle == -1)
        {
            switch( errno )
            {
                case ECANCELED:
                break;
                default:
                throw std::system_error( errno, std::generic_category() );
            }
        }
    };

    ~coroutine();

    void cancel();

};

template<typename C, typename... Args> void go(const C & obj, Args&&... args) {
    static std::vector<dill::coroutine> vec;
    vec.emplace_back(obj, args...);
}

}
