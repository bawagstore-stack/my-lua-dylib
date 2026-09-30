#include <stdio.h>
#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

// Dynamic library initialize hone par ye run hoga
__attribute__((constructor))
void initializer() {
    lua_State *L = luaL_newstate();
    if (L == NULL) return;
    
    luaL_openlibs(L);

    // Aapka Lua code yahan string mein aayega
    const char *lua_code = 
        "print('Hello! Lua code dylib se run ho gaya!')\n";

    // luaL_dostring se Lua code execute hota hai
    luaL_dostring(L, lua_code);

    lua_close(L);
}
