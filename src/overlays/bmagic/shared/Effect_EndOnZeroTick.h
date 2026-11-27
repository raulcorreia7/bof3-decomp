/* Finishes the effect once its ticker (work byte 0x0B) is zero: the side mask at work byte 0x04 goes to Battle_MarkDamaged, the active battler's effect ticker byte is lowered by one and the effect work is cleared. */
/* func_801EF2E4 (magic063), func_801EF2A0 (magic146) */
MATCH void Effect_EndOnZeroTick(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        Battle_MarkDamaged(SELF(PartyMember)->unk_04);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Effect_Reset();
    }
}
