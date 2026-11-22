/* Advances the effect counters and moves to the next step when the first reaches 0x10. */
/* func_801EEE3C (magic055), func_801EEE3C (magic091) */
MATCH void func_801EEE3C(void) {
    TASK(PartyMember)->unk_09 += 1;
    TASK(PartyMember)->timer += 1;
    if (TASK(PartyMember)->unk_09 == 0x10) {
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}
