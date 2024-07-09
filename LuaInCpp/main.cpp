#include "Lua/Lua.h"


int main() 
{
	LuaVm lua;
	lua.loadFileAndRun("script.lua");

	lua.runFunction("update");
}