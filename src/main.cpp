#include <Arduino.h>
#include "ESP32_OTA.h"
#include "luainc.h"
#include "./gpio.c"
//#include "Adafruit_MCP23017.h"


LUAMOD_API int (luaopen_gpio) (lua_State *L);



static lua_State *L = luaL_newstate();
const char* errmsg = NULL;
//Adafruit_MCP23017 mcp;


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

//    mcp.begin(0x21, &Wire);

//    mcp.pinMode(0, INPUT);
//    mcp.pullUp(0, HIGH);  //

    // low-rise house workshop (낮은집 작업실)
    setupWPS_OTA("LRH_Workshop");
    luaL_openlibs(L);

    luaL_requiref(L, "gpio", luaopen_gpio, 1);
    lua_pop(L, 1);  /* remove lib */

//    execLua("gpio.mode(4, 2); ");

    pinMode(35, INPUT);

    int rawValue = analogRead(35);

}

void loop() {
//    execLua( "gpio.digital_write(4, 1); ");
//    delay(1000);
//
//    execLua("gpio.digital_write(4, 0); ");
//    delay(1000);
    int lightMeter = analogRead(35);
    print("light: ");
    println(lightMeter);
    delay(500);
}