/* Counts byte 0x09 down; at zero it sets work flag 0x20, loads the tint
 * selector with 1, clears the three tint colours and steps the handler.
 */
/* func_801EF448, func_801EF5F0 */
MATCH void Effect_StartTint(void) {
    u8 count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(PartyMember)->unk_5C = 1;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->header.step += 1;
    }
}
