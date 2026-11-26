/* Sparkle step 1: sways the current sparkle while its radius grows by 1 per frame until it reaches its rise, then advances the step. */
/* func_801EF67C (magic070), func_801EF67C (magic071), func_801EF67C (magic072) */
MATCH void Effect_SparkleGrow(void) {
    s32 wave;
    u16 phase;
    u8  tick;

    BMAGIC_SWAY_ADVANCE_WORK(g_BMagicSparkle)
}
