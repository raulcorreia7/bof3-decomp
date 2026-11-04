#include "area108_14.h"

MATCH void func_801F405C(void) {
    u8 value;

    if (*g_ScriptVars == 0xE) {
        value = g_SpadWork->unk_09;
        func_801F4160(value, value);
        g_SpadWork->unk_09 += 1;
        if ((u8)g_SpadWork->unk_09 >= 0x6DU) {
            g_AreaSceneMode = 1;
            *g_ScriptVars   = 0xF;
            g_SpadWork->state_02 += 1;
        }
    }
}
