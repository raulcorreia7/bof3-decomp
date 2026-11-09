/* Raises the effect ticker, drops the effect counter by three and counts the wait down by two. */
/* func_801EF124 (magic055), func_801EF124 (magic091) */
MATCH void func_801EF124(void) {
    u8 count;

    g_Task->param.unk_0B += 1;
    g_Task->timer -= 3;
    count          = g_Task->unk_09 - 2;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}
