/* Marks the work flags, looks up scene record 0x158, loads byte 0x29
 * with 5, clears the tint bytes and moves the handler to state 1.
 */
/* func_801F3124 (area104), func_801F3078 (area121) */
MATCH void Area_FindSceneRecordAndClearTint(void) {
g_SpadWork->flags_24 = 0x80;
    Area_FindSceneRecord(0x158);
    g_SpadWork->unk_29            = 5;
    g_SpadWork->unk_2A            = 0;
    g_SpadWork->tint.bytes.unk_5D = 0;
    g_SpadWork->tint.bytes.unk_5E = 0;
    g_SpadWork->tint.bytes.unk_5F = 0;
    g_SpadWork->unk_01            = 1;
}
