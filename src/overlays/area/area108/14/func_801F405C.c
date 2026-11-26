#include "area108_14.h"

MATCH void func_801F405C(void) {
    u8 value;

    if (*g_ScriptVars == 0xE) {
        value = SELF(Actor)->timer;
        func_801F4160(value, value);
        SELF(Actor)->timer += 1;
        if (SELF(Actor)->timer >= 109U) {
            g_AreaSceneMode = 1;
            *g_ScriptVars   = 0xF;
            SELF(Actor)->header.step += 1;
        }
    }
}
