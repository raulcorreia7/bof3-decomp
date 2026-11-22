#include "area030_04.h"

/* Copies current AREA030 settings into the active scratch record.
 * Mode 1 clears its flag and returns; otherwise a signed world value at least
 * 0x39 sets the flag to 3 before the remaining fields are copied. */
/* FAKE: retail stores the +0x54..+0x5A fields through byte-pointer views; typed stores let gcc hoist the later loads.
 */
MATCH void func_801D11C0(void) {
    if (D_80145E92[0] == 1) {
        ACTOR_CLEAR_STEP();
        return;
    }
    if (g_AreaTargetCellY >= 0x39) {
        TASK(Actor)->header.step = 3;
    }
    TASK(Actor)->mirror         = g_Game.members[0].unk_2A;
    TASK(Actor)->unk_49         = g_Game.members[0].unk_49;
    TASK(Actor)->unk_4A         = g_Game.members[0].unk_4A;
    TASK(Actor)->script_record  = g_Game.members[0].unk_4B;
    *(s32*)&TASK(Actor)->script = g_Game.members[0].unk_50;
    *(s32*)(TASK(u8) + 0x54)    = g_Game.members[0].unk_54;
    *(u16*)(TASK(u8) + 0x58)    = g_Game.members[0].unk_58;
    *(u16*)(TASK(u8) + 0x5A)    = g_Game.members[0].unk_5A;
    Area_AddActor();
}
