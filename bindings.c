#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "mylib.h"

static int lua_myfunction(lua_State *L)
{
	int arg1 = luaL_checkint(L, 1);

	myfunction(arg1);

	return 0;
}

int luaopen_mylib(lua_State *L)
{
	luaL_Reg functions[] = {
		{ "myfunction", lua_myfunction },
		{ NULL, NULL }
	};

	luaL_register(L, "mylib", functions);

	return 1;
}
