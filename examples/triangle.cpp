#include <rex/rex.hpp>

int main(int argc, char** argv)
{
	rex::glfw_window window;
	rex::context     ctx;
	rex::surface     sfc;
	rex::device      device;
	rex::pipeline    simple_pipeline;

	rex::command_buffer commands;
	rex::buffer         mesh;

	while (true)
	{
		// Submit one command to draw a mesh
		commands.clear();
		commands.push_back(rex::command_type::DRAW, mesh);
		device.submit(commands);

		// present the image we just rendered to
		device.present(sfc);
	}

	return 0;
}