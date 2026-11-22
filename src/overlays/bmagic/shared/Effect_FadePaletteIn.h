/* Brightens the palette fade row indexed by the effect timer (work byte 0x0A) by one on each colour channel; when the effect ticker (work byte 0x09) reaches zero it advances the effect step. */
/* func_801EF3D4 (magic073), func_801EF3C0 (magic074) */
MATCH void Effect_FadePaletteIn(void) {
    g_PaletteFades[BMAGIC_WORK->timer].offset.r++;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g++;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b++;
    if (--BMAGIC_WORK->unk_09 == 0) {
        BMAGIC_WORK->header.step++;
    }
}
