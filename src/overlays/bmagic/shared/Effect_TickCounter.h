/* Counts the work counter at byte 0x09 down; at zero the active battler's effect ticker byte drops by one and the effect work record is cleared. */
/* func_801F0134 (magic144), func_801F0420 (magic092) */
MATCH void Effect_TickCounter(void) {
    u8 counter;

    counter                   = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        TASK(PartyMember)->header.flags = 0;
        TASK(PartyMember)->header.mode  = 0;
        TASK(PartyMember)->header.step  = 0;
        TASK(PartyMember)->unk_03       = 0;
        TASK(PartyMember)->unk_04       = 0;
    }
}
