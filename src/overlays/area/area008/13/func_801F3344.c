#include "area008_13.h"

MATCH void func_801F3344(void) {
    Actor* s;
    Actor* e;
    u8     idx;

    s      = g_Task;
    idx    = ((u8*)s)[0x0B];
    e      = &g_Actors[idx];
    g_Task = (Actor*)e;
    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        s->mode = 0x0E;
    } else if (g_ScriptVars[2] == 2) {
        Actor_SelectScript(3);
        s->mode = 3;
    } else if (g_ScriptVars[2] == 5) {
        Actor_SelectScript(3);
        s->mode = 0x0A;
    }
    g_Task = s;
}
