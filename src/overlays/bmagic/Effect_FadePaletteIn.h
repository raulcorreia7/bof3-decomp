/* Brightens the palette fade row indexed by the effect timer (work byte 0x0A) by one on each colour channel. */
/* func_801EF3D4 (magic073), func_801EF3C0 (magic074) */
MATCH void Effect_FadePaletteIn(void) {
    g_PaletteFades[g_Task->timer].offset.red++;
    g_PaletteFades[g_Task->timer].offset.green++;
    g_PaletteFades[g_Task->timer].offset.blue++;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.step++;
    }
}
