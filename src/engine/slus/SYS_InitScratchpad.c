#include "engine/slus/slus.h"

/* initializes the scratch work record for a new panel: marks it active, sets the mode (+0x24) and state
 * (+0x48) bytes, seeds the +0x40/+0x44 scroll pair with 0x1000, links the panel record at +0x54, clears the
 * +0x64/+0x68 angles and seeds +0x6C from D_801C8424 by the +8 route byte.
 */
/* func_8015AC8C */
MATCH void SYS_InitScratchpad(u8* panel) {
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
