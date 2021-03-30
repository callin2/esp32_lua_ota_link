//
// Created by  changjin on 2021/03/29.
//

#define LUA_LIB

#include "lua.h"
#include "lauxlib.h"
#include "Arduino.h"

// Lua: mode( pin, mode, pullup )
static int lgpio_mode( lua_State* L )
{
    unsigned pin = luaL_checkinteger( L, 1 );
    unsigned mode = luaL_checkinteger( L, 2 );

    pinMode(pin, mode);

    return 0;
}

// Lua: read( pin )
static int lgpio_digital_read( lua_State* L )
{
    unsigned pin = luaL_checkinteger( L, 1 );
    lua_pushinteger( L, digitalRead(pin) );
    return 1;
}

// Lua: write( pin, level )
static int lgpio_digital_write( lua_State* L )
{
    unsigned pin = luaL_checkinteger( L, 1 );
    unsigned level = luaL_checkinteger( L, 2 );

    digitalWrite(pin, level);
    return 0;
}

static const luaL_Reg gpiolib[] = {
        {"digital_write",   lgpio_digital_write},
        {"digital_read",  lgpio_digital_read},
        {"mode",  lgpio_mode},
        {NULL, NULL}
};

LUAMOD_API int luaopen_gpio (lua_State *L) {
    luaL_newlib(L, gpiolib);
    return 1;
}





