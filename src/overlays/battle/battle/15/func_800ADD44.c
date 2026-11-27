/* Dropping the volatile cell changes the code: retail reloads it. */
#define FAKE_DECL_SELF_VOLATILE
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

    SELF(PartyMember)->unk_29 = 1;
    SELF(PartyMember)->unk_25 = 0x1E;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_24 = 0x80;
    SELF(PartyMember)->unk_27 = 0x1B;
    SELF(PartyMember)->unk_28 = 1;
    work                      = SELF(volatile PartyMember);
    work->unk_2B              = 0;
    next                      = SELF(PartyMember);
    work->unk_2C.signed_value = 2;
    next->unk_2A              = 0;
    work                      = SELF(volatile PartyMember);
    work->unk_4B              = 0xFF;
    slotp                     = SELF(PartyMember);
    work->pos.z.fixed         = 0;
    pair                      = &g_UiPanelTasks[19].u.battle.row_base;
    base                      = (u8*)D_80145518;
    row                       = base + ((*pair + slotp->unk_09) * 4);
    slot                      = row[slotp->timer];
    if (slot != GAME_NONE) {
        Script_Select(slot);
    }
    D_801485FA        = *pair;
    work              = SELF(volatile PartyMember);
    work->header.mode = work->header.mode + 1;
}
