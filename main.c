#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

extern "C" {
    #include <lua.h>
    #include <lualib.h>
    #include <lauxlib.h>
}

void* run_lua_thread(void* arg) {
    // 5 seconds ka wait taaki game memory load ho jaye
    sleep(5);

    lua_State *L = luaL_newstate();
    if (L == NULL) return NULL;
    
    luaL_openlibs(L);

    const char *lua_code = R"(
        local logic_profile_get_wrap = require("client.network.Protocol.FriendApplyHandler")

        local ids = {
            523442956,
            5587557062,
            5818541383,
            5249981642,
            5216804941,
            5148652918,
            5102101549,
            5466455258,
            5216953998,
            5249175905,
            559804335,
            5194623653,
            5143921876,
            5120239889,
            5586965216,
            5339192620,
            5200865910,
            5210029111,
            5123160209
        }

        for _, PlayerID in ipairs(ids) do
            logic_profile_get_wrap.on_auto_add_inner_friend_notify(PlayerID)
        end
    )";

    if (luaL_dostring(L, lua_code) != LUA_OK) {
        const char *err = lua_tostring(L, -1);
        printf("Lua Error: %s\n", err);
        lua_pop(L, 1);
    }

    lua_close(L);
    return NULL;
}

__attribute__((constructor))
void initializer() {
    // Game crash na ho isliye alag background thread me 5s delay chalega
    pthread_t thread;
    pthread_create(&thread, NULL, run_lua_thread, NULL);
}
