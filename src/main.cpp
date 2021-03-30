#include <Arduino.h>
#include "ESP32_OTA.h"
#include "luainc.h"

static lua_State *L = luaL_newstate();
const char* errmsg = NULL;

int execLua(const char *s) {
    luaL_loadstring(L, s);
    if (lua_pcall(L, 0, 0, 0)) {
        errmsg = lua_tostring(L, -1);
        Serial.println(errmsg);
        return -1;
    }
    return 0;
}

void setup() {
    Serial.begin(115200);
    Serial.println("Booting");
    // low-rise house workshop (낮은집 작업실)
    setupWPS_OTA("LRH_Workshop");
    luaL_openlibs(L);
    execLua("gpio.mode(4, 2); ");
}

void loop() {
    execLua( "gpio.digital_write(4, 1); ");
    delay(1000);

    execLua("gpio.digital_write(4, 0); ");
    delay(1000);
}