#include "engine/game/00/game_00.h"

/* func_8019CBD8 */
/* Starts a block: claims its cells and waits for a push. */
MATCH void Actor_BlockStart(void) {
    Actor* other;
    Actor* record;
    Actor* work;
    Actor* counter;

    SELF(Actor)->direction = FACING_UP;
    SYS_InitScratchpad((u8*)(((AreaLoad*)g_AreaLoads[g_GameAreaId])->field_08 + (SELF(Actor)->param.unk_0B * 8)));
    record                          = SELF(Actor);
    record->tint.steps.delta.r      = -0x80;
    other                           = SELF(Actor);
    record->voice_flags.raw         = 1;
    other->tint.steps.delta.g       = -0x80;
    SELF(Actor)->tint.steps.delta.b = -0x80;
    work                            = SELF(Actor);
    setVector(work, 0, 0, 0);
    work->timer = 0;
    Actor_BlockClaimCells();
    SELF(Actor)->param.unk_0B = 0U;
    counter                   = SELF(Actor);
    counter->header.mode      = (counter->header.mode + 1);
    Actor_ProjectForDraw();
}
