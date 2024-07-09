#include "Lua/Lua.h"

int main(int argc, char** argv)
{
	std::string path;
	if (!argv[1]) 
	{
		spdlog::warn("No file specified defualting to script.lua");
		path = "script.lua";
	}
	else {
		path = argv[1];
	}
	if (path == "")
	{
		spdlog::warn("No file specified defualting to script.lua");
		path = "script.lua";
	}


	spdlog::debug(path);
	Lua::LuaVm lua;
	lua.loadFileAndRun(path);
}