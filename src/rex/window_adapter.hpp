#ifndef REX_WINDOW_ADAPTER_HPP_
#define REX_WINDOW_ADAPTER_HPP_

namespace rex
{
    /**
        \brief window_adapter

        The window adapter is the abstraction through which
        rex interacts with an operative system window
    */
    class window_adapter
    {
    public:
        virtual void display() = 0;
    };
}

#endif // REX_WINDOW_ADAPTER_HPP_