/* Records the current battle magic trail position. */
/* func_801F02A0 (magic044), func_801F02B0 (magic173) */
MATCH void Effect_RecordTrail(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(BMagic_Trail)
    BMagic_Trail[TASK(PartyMember)->unk_04][TASK(PartyMember)->param.unk_0B].vx = TASK(PartyMember)->screen_x.value;
    BMagic_Trail[TASK(PartyMember)->unk_04][TASK(PartyMember)->param.unk_0B].vy = TASK(PartyMember)->screen_y.value;
}
