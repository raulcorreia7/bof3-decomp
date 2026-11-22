#include "engine/slus/slus.h"

/* arms the scratch task for a panel record: marks it in use and ready with its reset flag set and
 * full scale, links the panel as its range record, takes its step list from the panel's +4 word,
 * clears two angle words and seeds the third from D_801C8424 by the facing direction.
 */
/* func_8015AC8C */
MATCH void SYS_InitScratchpad(u8* panel) {
    Actor* work;
    s32    value;
    u8     index;

    TASK(Actor)->header.flags = ACTOR_FLAG_IN_USE;
    TASK(Actor)->active_flags = ACTOR_ACTIVE_READY;
    TASK(Actor)->unk_48       = 1;
    work                      = TASK(Actor);
    work->scale.x             = ONE;
    work->scale.y             = ONE;
    value                     = FIELD(s32, panel, 0x4u);
    index                     = work->direction;
    work->range_54.table      = panel;
    work->unk_68              = 0;
    work->unk_64              = 0;
    work->script              = (u8*)value;
    work->unk_6C              = D_801C8424[index];
}
