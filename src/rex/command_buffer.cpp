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
    command c;
    c.type = command_type::LOAD_GEOMETRY;
    c.vertexUpload.vbo = vbo;
    c.vertexUpload.data = data;
    c.vertexUpload.size = size;
    _cmds.push_back(c);
}

void command_buffer::drawBuffer(vertex_buffer* vbo)
{
    command c;
    c.type = command_type::DRAW;
    c.arrayDraw.vbo = vbo;
    c.arrayDraw.offset = 0;
    c.arrayDraw.size = 6;
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

void command_buffer::uploadTexture(texture* tex, const bitmap& data)
{
    command c;
    c.type = command_type::UPLOAD_IMAGE;
    _cmds.push_back(c);
}

}
