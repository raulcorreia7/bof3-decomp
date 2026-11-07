#include "area008_13.h"

MATCH void func_801F32AC(void) {
    Actor* e;
    u8     index;

    if ((g_ScriptVars[3] & 0x80u) != 0u) {
        g_Task->header.mode = 0x0E;
        return;
    }
    if (g_ScriptVars[2] == 1) {
        index = TASK_BYTES[0x0B];
        e     = &g_Actors[index];
        e->header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->header.mode = 2;
    }
}
