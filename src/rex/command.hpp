#ifndef REX_COMMAND_HPP_
#define REX_COMMAND_HPP_

namespace rex
{
	enum struct command_type
	{
		ACTIVATE_PIPELINE,
		DRAW_BUFFER
	};

	struct command
	{
		command_type type;
		handle       hnd;
	};

	struct command_buffer
	{
		void draw()
		{
			_cmds.emplace_back({});
		}

		std::vector<command> _cmds;
	};
}

#endif // REX_COMMAND_HPP_