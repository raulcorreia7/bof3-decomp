#include "area085_13.h"

MATCH void func_801F3AF8(void) {
    g_Task->active_flags &= 0xFE;
    Area_SelectSceneRecord(0x184);
    Actor_SelectScript(0);
    g_Task->unk_2A = 1;
    g_Task->header.flags |= ACTOR_FLAG_STEP_MOVE;
}
