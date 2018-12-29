#ifndef REX_COMMAND_HPP_
#define REX_COMMAND_HPP_

#include <vector>
#include <string>
#include "handle.hpp"

namespace rex
{
    class pipeline;
    class vertex_buffer;

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
        SET_VIEWPORT,
        LOAD_GEOMETRY,
        UPLOAD_IMAGE,
    };

	struct command
	{
        command_type       type;

        union {
            pipeline* pipe;
            void* userData;

            struct {
                vertex_buffer* vbo;
                void* data;
                std::size_t size;
            } vertexUpload;

            struct {
                vertex_buffer* vbo;
                std::size_t offset;
                std::size_t size;
            } arrayDraw;
        };
	};

    /*
     *  Sequential buffer with rendering orders
     */
    class command_buffer
	{
    public:
        void clear();

        void bind(pipeline* p);
        void uploadVertices(vertex_buffer* vbo, void* data, std::size_t size);
        void drawBuffer(vertex_buffer* vbo);
        void clearColor();
        void setUniform(const std::string& name, int elem);

    //private:
        std::vector<command> _cmds;
	};
}

#endif // REX_COMMAND_HPP_
