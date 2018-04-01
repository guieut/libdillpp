
#include "libdillpp.h"


namespace dill
{
    coroutine::coroutine(coroutine&& coro) noexcept
    :m_handle(coro.m_handle)
    {
        coro.m_handle = -2;
    }

    coroutine::~coroutine()
    {
        if(m_handle>=0)
            cancel();
    }

    void coroutine::cancel()
    {
        if(m_handle>=0)
        {
            hclose( m_handle );
            m_handle = -1;
        }
    }
}
