#include "area106_13.h"

MATCH void func_801F3940(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 81)) {
        g_Task->pos.x.fixed = 0x128000;
        g_Task->pos.y.fixed = 0xB8000;
        if (SYS_TestFlag(g_SceneEventFlags, 79)) {
            COORD_INT(g_Task->pos.z) = 2128;
            g_ScriptState->cursor += 2;
        } else {
            COORD_INT(g_Task->pos.z) = 1536;
            g_ScriptState->cursor += 4;
        }
        return;
    }
    if (SYS_TestFlag(g_SceneEventFlags, 79)) {
        g_Task->pos.x.fixed      = 0x128000;
        g_Task->pos.y.fixed      = 0x238000;
        COORD_INT(g_Task->pos.z) = 2128;
        return;
    }
    g_Task->pos.x.fixed      = 0x118000;
    g_Task->pos.y.fixed      = 0x1F8000;
    COORD_INT(g_Task->pos.z) = 768;
    g_ScriptState->cursor += 4;
}
