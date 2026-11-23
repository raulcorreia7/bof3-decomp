#include "engine/slus/slus.h"

/* arms the scratch task for a panel record: marks it in use and ready with its reset flag set and
 * full scale, links the panel as its range record, takes its step list from the panel's +4 word,
 * clears two angle words and seeds the third from g_ActorFacingAngles by the facing direction.
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
    work->angle_y             = 0;
    work->angle_x             = 0;
    work->script              = (u8*)value;
    work->angle_z             = g_ActorFacingAngles[index];
}
