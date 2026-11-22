MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[BMAGIC_WORK->timer].offset.r++;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g++;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b++;
    if (--BMAGIC_WORK->unk_09 == 0) {
        BMAGIC_WORK->header.mode++;
    }
}
