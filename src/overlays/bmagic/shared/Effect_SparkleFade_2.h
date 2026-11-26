/* Sparkle step 2: sways the current sparkle, shrinks its radius every fourth frame and counts its timer down; at zero lowers the task's count of live sparkles and clears the record. */
/* func_801EF728 (magic162), func_801EF728 (magic168) */
MATCH void Effect_SparkleFade(void) {
    u16 phase;
    u8  timer;

    BMAGIC_SWAY_EFFECT_WORK(g_BMagicSparkle, Effect_SparkleClear)
}
