/* Counts the effect timer (work byte 0x09) down; at zero it advances the step byte (work byte 0x01) the bmagic dispatcher indexes. */
/* func_801EF01C (magic009), func_801EEED4 (magic101), func_801EEEC0 (magic118) */
MATCH void Effect_CountDownTimerNextStep(void) {
    u8 timer;

    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}
