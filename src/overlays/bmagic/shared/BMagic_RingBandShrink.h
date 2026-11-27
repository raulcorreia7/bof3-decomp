/* Ring band mode 1: raises the phase (byte 0x0B) by 1 and the wave height (byte 0x0A) by 2 per frame while the radius step falls by 2; at BMAGIC_RING_BAND_SHRINK_LIMIT advances header.mode. */
/* func_801EF09C (magic055), func_801EF09C (magic091) */
MATCH void BMagic_RingBandShrink(void) {
    u8 counter;

    SELF(PartyMember)->param.unk_0B += 1;
    SELF(PartyMember)->timer += 2;
    counter                   = SELF(PartyMember)->unk_09 - 2;
    SELF(PartyMember)->unk_09 = counter;
    if ((counter & BYTE_MASK) == BMAGIC_RING_BAND_SHRINK_LIMIT) {
        SELF(PartyMember)->header.mode += 1;
    }
}
