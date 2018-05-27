#ifndef REX_MESSAGE_BUS_HPP_
#define REX_MESSAGE_BUS_HPP_

#include "command_buffer.hpp"
#include "vertex_data.hpp"

namespace rex
{
    class message_bus
    {
    public:
        void load_geometry(const vertex_data& data, handle& h);

    private:
        //rc_command_buffer _rc_commands;
        command_buffer    _commands;
    };
}

#endif // REX_MESSAGE_BUS_HPP_
