#include <sol/sol.hpp>
#include "assert.h"


class LuaVm 
{
private:
	sol::state lua;
	int runtime_exception_handler(lua_State* L, sol::optional<const std::exception&> maybe_exception, sol::string_view description);

public:
	LuaVm();
	~LuaVm();

	sol::state* getLua();

	void loadFileAndRun(std::string file);
	sol::protected_function_result runFunction(std::string name);
};