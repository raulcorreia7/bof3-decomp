/* Raises the effect ticker, lowers the work byte at +0x04 and counts the counter at +0x09; at 136 it sets the active battler's ticker to 0xFF and clears the effect. */
/* func_801EF3C4 (magic120), func_801EF29C (magic122) */
MATCH void Effect_CountUpAndFinishAt136(void) {
    u8 counter;

    g_Task->param.unk_0B += 1;
    g_Task->unk_04 -= 1;
    counter        = g_Task->unk_09 + 1;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x88) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        func_801E5988();
    }
}
