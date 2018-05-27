#include "command_buffer.hpp"

namespace rex {

void command_buffer::clear()
{
    _cmds.clear();
}

void command_buffer::bind(pipeline* p)
{
    command c;
    c.type = command_type::SET_PIPELINE;
    c.pipe = p;
    _cmds.push_back(c);
}

void command_buffer::uploadVertices(vertex_buffer* vbo, void* data, std::size_t size)
{

}

void command_buffer::drawBuffer(vertex_buffer* vbo)
{
    command c;
    c.type = command_type::DRAW;
    c.vbo = vbo;
    _cmds.push_back(c);
}

void command_buffer::clearColor()
{
    command c;
    c.type = command_type::CLEAR_COLOR;
    _cmds.push_back(c);
}

void command_buffer::setUniform(const std::string& name, int elem)
{
    // Just for API mocking
}

}
