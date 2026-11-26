/* Claims the first free record of the sparkle pool and returns its index, or GAME_NONE when the pool is full. */
/* func_801F0000 (magic070), func_801F0000 (magic071), func_801F0000 (magic072) */
MATCH u8 Effect_SparkleAlloc(void) {
    u8 i;

    for (i = 0; i < EFFECT_SPARKLE_COUNT; i++) {
        if (!(g_BMagicSparkles[i].header.flags & EFFECT_SPARKLE_IN_USE)) {
            g_BMagicSparkles[i].header.flags |= EFFECT_SPARKLE_IN_USE;
            return i;
        }
    }
    return GAME_NONE;
}
