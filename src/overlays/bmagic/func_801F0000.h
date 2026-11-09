/* Takes the first free record of the sparkle pool and marks it in use. */
/* func_801F0000 (magic070), func_801F0000 (magic071), func_801F0000 (magic072) */
MATCH u8 func_801F0000(void) {
    u8 i;

    for (i = 0; i < EFFECT_SPARKLE_COUNT; i++) {
        if (!(D_801F01B4[i].header.flags & EFFECT_SPARKLE_IN_USE)) {
            D_801F01B4[i].header.flags |= EFFECT_SPARKLE_IN_USE;
            return i;
        }
    }
    return GAME_NONE;
}
