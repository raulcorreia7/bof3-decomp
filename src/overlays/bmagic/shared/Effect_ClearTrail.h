/* Clears the current battle magic trail slot. */
/* func_801F0390 (magic044), func_801F03A0 (magic173) */
MATCH void Effect_ClearTrail(void) {
    s32 i;

    BMAGIC_SHIFT_TRAIL(BMagic_Trail)
    BMagic_Trail[SELF(PartyMember)->unk_04][SELF(PartyMember)->param.unk_0B].vx = -1;
    BMagic_Trail[SELF(PartyMember)->unk_04][SELF(PartyMember)->param.unk_0B].vy = -1;
}
