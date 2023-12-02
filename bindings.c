#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
#include "mylib.h"
#include <string.h>

static int lua_myfunction(lua_State *L)
{
	int arg1 = luaL_checkint(L, 1);

	myfunction(arg1);

	return 0;
}

static int lua_create_struct(lua_State *L)
{
	lua_newuserdata(L, sizeof(struct mydata));
	struct mydata *udata = lua_touserdata(L, -1);
	udata->msg = "Hello world!";
	udata->number = 1337;
	udata->bignumber = 0xdeadbeefdeadc0de;
	
	luaL_getmetatable(L, "mydata");
	lua_setmetatable(L, -2);
	
	return 1;
}

static int lua_print_struct(lua_State *L)
{
	struct mydata *udata = luaL_checkudata(L, 1, "mydata");

	print_struct(udata);

	return 0;
}

static int lua_mydata_index(lua_State *L)
{
	struct mydata *udata = (struct mydata *)luaL_checkudata(L, 1, "mydata");
	const char *str = luaL_checkstring(L, 2);
	
	if (!strcmp(str, "msg")) {
		lua_pushstring(L, udata->msg);
	} else if (!strcmp(str, "number")) {
		lua_pushinteger(L, udata->number);
	} else if (!strcmp(str, "bignumber")) {
		lua_pushinteger(L, udata->bignumber);
	} else {
		lua_pushnil(L);
	}

	return 1;
}

static int lua_mydata_tostring(lua_State *L)
{
	struct mydata *udata = (struct mydata *)luaL_checkudata(L, 1, "mydata");
	lua_pushfstring(L, "mydata(msg: %s, number: %d, bignumber: %p)", udata->msg, udata->number, udata->bignumber);
	return 1;
}

int luaopen_mylib(lua_State *L)
{
	luaL_Reg functions[] = {
		{ "myfunction", lua_myfunction },
		{ "print_struct", lua_print_struct },
		{ "create_struct", lua_create_struct },
		{ NULL, NULL }
	};

	luaL_newmetatable(L, "mydata");
	lua_pushcfunction(L, lua_mydata_index);
	lua_setfield(L, -2, "__index");
	lua_pushcfunction(L, lua_mydata_tostring);
	lua_setfield(L, -2, "__tostring");
	lua_pop(L, 1);

	luaL_register(L, "mylib", functions);

	return 1;
}
