/* Task mode 1: raises the disc radius step (byte 0x09) and the shade level (byte 0x0A) by one per frame; at BMAGIC_RING_EXPAND_LIMIT advances header.mode. */
/* func_801EEE3C (magic055), func_801EEE3C (magic091) */
MATCH void BMagic_RingExpand(void) {
    SELF(PartyMember)->unk_09 += 1;
    SELF(PartyMember)->timer += 1;
    if (SELF(PartyMember)->unk_09 == BMAGIC_RING_EXPAND_LIMIT) {
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}
