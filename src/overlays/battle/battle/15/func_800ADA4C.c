#include "battle_15.h"

MATCH void func_800ADA4C(void) {
    PartyMember* work;
    /* FAKE: retail holds the armed work pointer in a0. */
    FAKE_REG(PartyMember*, next, "a0");
    /* FAKE: retail holds the queued work pointer in a1 for the slot lookup. */
    FAKE_REG(PartyMember*, slotp, "a1");
    u8*  base;
    s16* pair;
    u8*  row;
    u8   slot;

    SELF(PartyMember)->unk_29 = 1;
    SELF(PartyMember)->unk_25 = 0x1E;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_24 = 0x80;
    SELF(PartyMember)->unk_27 = 0x1B;
    SELF(PartyMember)->unk_28 = 1;
    work                      = SELF(PartyMember);
    work->unk_2B              = 0;
    next                      = SELF(PartyMember);
    work->unk_2C.signed_value = 2;
    next->unk_2A              = 0;
    work                      = SELF(PartyMember);
    work->unk_4B              = 0xFF;
    slotp                     = SELF(PartyMember);
    work->pos.z.fixed         = 0;
    pair                      = &D_801485CA;
    base                      = (u8*)g_BattleTargetRows;
    row                       = base + ((*pair + slotp->unk_09) * 4);
    slot                      = row[slotp->timer];
    if (slot != GAME_NONE) {
        Script_Select(slot);
    }
    D_801485D6        = *pair;
    work              = SELF(PartyMember);
    work->header.mode = work->header.mode + 1;
}
