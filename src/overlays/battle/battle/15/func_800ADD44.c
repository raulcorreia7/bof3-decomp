/* Dropping the volatile cell changes the code: retail reloads it. */
#define TASK_VOLATILE
#include "battle_15.h"

MATCH void func_800ADD44(void) {
    volatile PartyMember* work;
    /* FAKE: retail holds the armed work pointer in a0. */
    FAKE_REG(PartyMember*, next, "a0");
    PartyMember* slotp;
    u8*          base;
    s16*         pair;
    u8*          row;
    u8           slot;

    BATTLE_WORK->unk_29      = 1;
    BATTLE_WORK->unk_25      = 0x1E;
    BATTLE_WORK->unk_26      = 0;
    BATTLE_WORK->unk_24      = 0x80;
    BATTLE_WORK->unk_27      = 0x1B;
    BATTLE_WORK->unk_28      = 1;
    work                     = (volatile PartyMember*)g_Task;
    work->unk_2B             = 0;
    next                     = (PartyMember*)g_Task;
    work->unk_2C.signed_half = 2;
    next->unk_2A             = 0;
    work                     = (volatile PartyMember*)g_Task;
    work->unk_4B             = 0xFF;
    slotp                    = (PartyMember*)g_Task;
    work->pos.z.fixed        = 0;
    pair                     = &D_801485EE;
    base                     = (u8*)D_80145518;
    row                      = base + ((*pair + slotp->unk_09) * 4);
    slot                     = row[slotp->timer];
    if (slot != GAME_NONE) {
        Actor_SelectScript(slot);
    }
    D_801485FA        = *pair;
    work              = (volatile PartyMember*)g_Task;
    work->header.mode = work->header.mode + 1;
}
