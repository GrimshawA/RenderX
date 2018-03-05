#ifndef REX_COMMAND_HPP_
#define REX_COMMAND_HPP_

#include <vector>
#include "handle.hpp"

namespace rex
{
	enum struct command_type
	{
        BIND_INDEX_BUFFER,
        BIND_VERTEX_BUFFER,
        CLEAR_COLOR,
        CLEAR_DEPTH,
        DISPATCH,
        DISPATCH_INDIRECT,
        DRAW,
        DRAW_INDEXED,
        DRAW_INDEXED_INDIRECT,
        DRAW_INDIRECT,
        SET_PIPELINE,
        SET_BLEND_CONSTANTS,
        SET_LINE_WIDTH,
        SET_SCISSOR,
        SET_VIEWPORT
	};

    enum struct rc_command_type
    {
        LOAD_GEOMETRY,
        UPLOAD_IMAGE,
    };

    template<typename type_t>
	struct command
	{
        type_t       type;
		handle       hnd;
	};

    /*
     *  Sequential buffer with rendering orders
     */
	struct command_buffer
	{
        std::vector<command<command_type>> _cmds;
	};

    /*
     *  Resource related commands are kept separated because they are only done
     *  rarely and they don't need to be overhead for the rendering loop.
     */
    struct rc_command_buffer
    {
        std::vector<command<rc_command_type>> _cmds;
    };
}

#endif // REX_COMMAND_HPP_
