#ifndef REX_FORWARD_RENDERER_HPP_
#define REX_FORWARD_RENDERER_HPP_

namespace rex
{
	/*
		Sample forward renderer

		Pseudo code to demonstrate forward rendering flow of usage of rex
	*/
	class forward_renderer
	{
	public:

		void prepare()
		{
			foreach(mesh in meshes)
			{
				foreach(light in mesh.lights_affected)
				{
					if (mesh.pipeline != _device.pipeline)
						record_pipeline_change(mesh.pipeline);
					
					record_draw(_commmands, mesh.buffer)
				}
			}
		}

		void render()
		{
			// Produce one frame, just a matter of running a command buffer


		}

		device _device;
		command_buffer _commands;
	};
}

#endif // REX_FORWARD_RENDERER_HPP_