/* Counts byte 0x09 down; at zero it loads byte 0x0B with a random value
 * below 16, clears bytes 0x09 and 0x0A and steps the handler.
 */
/* func_801EF114, func_801EF124 */
MATCH void Effect_CountDownAndPickRandom(void) {
    u8 counter;

    counter                   = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = counter;
    if (!(counter & BYTE_MASK)) {
        SELF(PartyMember)->param.unk_0B = RANDOM_MASK(0xF);
        SELF(PartyMember)->unk_09       = 0;
        SELF(PartyMember)->timer        = 0;
        SELF(PartyMember)->header.step += 1;
    }
}
