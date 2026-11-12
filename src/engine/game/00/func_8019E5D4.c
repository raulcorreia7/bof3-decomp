#include "game_00.h"

MATCH void func_8019E5D4(void) {
    s32 value;
    u8  sel;

    Area_SelectSceneRecord(0x18);

    g_Task->active_flags = 0;
    g_Task->unk_2A       = 0;
    g_Task->unk_2B++;
    g_Task->unk_48 = 0;

    value = rand();
    {
        Actor* coord = g_Task;
        coord->pos.x.fixed += value & HALF_MASK;
    }
    value = rand();
    {
        Actor* record   = g_Task;
        record->gravity = -8;
        record->vz      = 0;
        record->pos.y.fixed += value & HALF_MASK;
    }
    value = RANDOM_MASK(3);

    if (value >= 0) {
        sel = value;
        if (value >= 3) {
            sel = 2;
        }
    } else {
        sel = 0;
    }

    ACTOR_CLEAR_TINT();
    Actor_SelectScript(sel + 0xB);
    g_Task->header.step++;
}
