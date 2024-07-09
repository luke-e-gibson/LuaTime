#include <sol/sol.hpp>
#include <spdlog/spdlog.h>
#include "assert.h"

namespace Lua
{
	enum LuaLibs
	{
		Base,
		Package,
		Os,
		Coroutine,
		Table,
		String,
		Math,
		IO,
		Utf8
	};


	class LuaVm
	{
	private:
		sol::state lua;
		static int runtime_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description);

	public:
		LuaVm(LuaLibs... libs);
		~LuaVm();

		void loadFileAndRun(std::string file);
		sol::state* getLua();
		sol::protected_function_result runFunction(std::string name);
	};
}