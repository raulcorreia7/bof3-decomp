#include "area108_14.h"

MATCH void func_801F405C(void) {
    u8 value;

    if (*g_ScriptVars == 0xE) {
        value = TASK(Actor)->timer;
        func_801F4160(value, value);
        TASK(Actor)->timer += 1;
        if (TASK(Actor)->timer >= 109U) {
            g_AreaSceneMode = 1;
            *g_ScriptVars   = 0xF;
            TASK(Actor)->header.step += 1;
        }
    }
}
