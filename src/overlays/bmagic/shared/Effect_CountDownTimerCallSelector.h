/* Counts the timer down; at zero selects the target (0x20) and advances the step. */
/* func_801EEF3C (magic067), func_801EEEFC (magic137) */
MATCH void Effect_CountDownTimerCallSelector(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x20);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}
