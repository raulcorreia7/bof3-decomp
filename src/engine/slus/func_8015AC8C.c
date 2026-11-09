#include "engine/slus/slus.h"

/* initializes the scratch record for a new panel. */
MATCH void func_8015AC8C(u8* panel) {
    Actor* work;
    s32    value;
    u8     index;

    g_Task->header.flags = ACTOR_FLAG_IN_USE;
    g_Task->active_flags = ACTOR_FLAG_ACTIVE;
    g_Task->unk_48       = 1;
    work                 = g_Task;
    work->scale.x        = ONE;
    work->scale.y        = ONE;
    value                = FIELD(s32, panel, 0x4u);
    index                = work->direction_08;
    work->range_54.table = panel;
    work->unk_68         = 0;
    work->unk_64         = 0;
    work->script         = (u8*)value;
    work->unk_6C         = D_801C8424[index];
}
