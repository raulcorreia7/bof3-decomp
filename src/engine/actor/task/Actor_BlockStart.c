#include "engine/game/00/game_00.h"

/* func_8019CBD8 */
/* Starts a block: claims its cells and waits for a push. */
MATCH void Actor_BlockStart(void) {
    Actor* other;
    Actor* record;
    Actor* work;
    Actor* counter;

    TASK(Actor)->direction = FACING_UP;
    SYS_InitScratchpad((u8*)(((AreaLoad*)g_AreaLoads[g_GameAreaId])->field_08 + (TASK(Actor)->param.unk_0B * 8)));
    record                          = TASK(Actor);
    record->tint.steps.delta.r      = -0x80;
    other                           = TASK(Actor);
    record->voice_flags.raw         = 1;
    other->tint.steps.delta.g       = -0x80;
    TASK(Actor)->tint.steps.delta.b = -0x80;
    work                            = TASK(Actor);
    setVector(work, 0, 0, 0);
    work->timer = 0;
    Actor_BlockClaimCells();
    TASK(Actor)->param.unk_0B = 0U;
    counter                   = TASK(Actor);
    counter->header.mode      = (counter->header.mode + 1);
    Actor_ProjectForDraw();
}
