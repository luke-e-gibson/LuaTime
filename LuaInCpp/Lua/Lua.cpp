#include "Lua.h"
#include <thread>
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

//Do i need this
#include "assert.h"

namespace Lua 
{
	LuaVm::LuaVm(LuaLibs... libs)
	{
		spdlog::info("Creating Lua Vm");


		lua.open_libraries(sol::lib::base, sol::lib::package);


		lua.set_exception_handler(&LuaVm::runtime_exception_handler);
	}

	LuaVm::~LuaVm() {}

	int LuaVm::runtime_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description)
	{
		if (maybe_exception)
		{
			spdlog::error("An Error has occurred: {}", maybe_exception.value().what());
		}
		return 0;
	};

	sol::state* LuaVm::getLua()
	{
		return &lua;
	}

	sol::protected_function_result LuaVm::runFunction(std::string name)
	{
		auto value = lua[name]();
		return value;
	}

	void LuaVm::loadFileAndRun(std::string file)
	{
		spdlog::info("Starting File: {}", file);
		sol::protected_function_result res = lua.safe_script_file(file, &sol::script_pass_on_error);

		if (!res.valid())
		{
			spdlog::error("An Error has occurred:");
			sol::error err = res;
			spdlog::error(err.what());
		}
	}
}