/* Counts the work counter at byte 0x09 down by 2 and raises the timer at byte 0x0A on odd frames; when the counter reaches 1 the active battler's effect ticker byte drops by one and the effect work record is cleared. */
/* func_801EF738 (magic144), func_801EFA24 (magic092) */
MATCH void Effect_CountDownByTwoFinishAtOne(void) {
    SELF(PartyMember)->unk_09 -= 2;
    if (g_FrameCount & 1) {
        SELF(PartyMember)->timer += 1;
    }
    if (SELF(PartyMember)->unk_09 == 1) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        SELF(PartyMember)->header.flags = 0;
        SELF(PartyMember)->header.mode  = 0;
        SELF(PartyMember)->header.step  = 0;
        SELF(PartyMember)->unk_03       = 0;
        SELF(PartyMember)->unk_04       = 0;
    }
}
