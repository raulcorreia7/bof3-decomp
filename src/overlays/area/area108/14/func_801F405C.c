#include "area108_14.h"

MATCH void func_801F405C(void) {
    u8 value;

    if (*g_ScriptVars == 0xE) {
        value = g_Task->unk_09;
        func_801F4160(value, value);
        g_Task->unk_09 += 1;
        if (g_Task->unk_09 >= 0x6DU) {
            g_AreaSceneMode = 1;
            *g_ScriptVars   = 0xF;
            g_Task->step += 1;
        }
    }
}
