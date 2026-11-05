/* Counts byte 0x09 down; at zero it sets work flag 0x20, loads the tint
 * selector with 1, clears the three tint colours and steps the handler.
 */
/* func_801EF448, func_801EF5F0 */
MATCH void Effect_CountDownAndSetTint(void) {
u8 count;

    count                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = count;
    if (!(count & 0xFF)) {
        g_SpadWork->flags_00 |= 0x20;
        g_SpadWork->unk_5C = 1;
        g_SpadWork->unk_5D = 0;
        g_SpadWork->unk_5E = 0;
        g_SpadWork->unk_5F = 0;
        g_SpadWork->unk_02 += 1;
    }
}
