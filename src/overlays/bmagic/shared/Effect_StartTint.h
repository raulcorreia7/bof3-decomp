/* Counts byte 0x09 down; at zero it sets work flag 0x20, loads the tint
 * selector with 1, clears the three tint colours and steps the handler.
 */
/* func_801EF448, func_801EF5F0 */
MATCH void Effect_StartTint(void) {
    u8 count;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        BMAGIC_WORK->header.flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        BMAGIC_WORK->unk_5C = 1;
        BMAGIC_WORK->unk_5D = 0;
        BMAGIC_WORK->unk_5E = 0;
        BMAGIC_WORK->unk_5F = 0;
        BMAGIC_WORK->header.step += 1;
    }
}
