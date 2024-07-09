#include "Lua.h"
#include <sol/sol.hpp>
#include <spdlog/spdlog.h>

//Do i need this
#include "assert.h"

LuaVm::LuaVm()
{
	spdlog::info("Creating Lua Vm");
	lua.open_libraries(sol::lib::base, sol::lib::package);
	lua.set_exception_handler(&LuaVm::runtime_exception_handler);
}

LuaVm::~LuaVm() {}

int LuaVm::runtime_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description) {
	spdlog::error("An error has occurred in this program");


	if (maybe_exception) {
		const std::exception& ex = *maybe_exception;
		spdlog::error("Exception: {}", ex.what());
	}
	else {
		spdlog::error("Description: ");
		spdlog::error(description.data());
	}

	return sol::stack::push(L, description);
}

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

	if(!res.valid())
	{
		spdlog::error("An Error has occurred:");
		sol::error err = res;
		spdlog::error(err.what());
	}
}