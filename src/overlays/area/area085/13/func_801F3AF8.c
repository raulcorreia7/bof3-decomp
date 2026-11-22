#include "area085_13.h"

MATCH void func_801F3AF8(void) {
    g_Task->active_flags &= 0xFE;
    Area_SceneSelectRecord(0x184);
    Script_Select(0);
    g_Task->mirror = 1;
    g_Task->header.flags |= ACTOR_FLAG_STEP_MOVE;
}
