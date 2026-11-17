MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[g_Task->timer].offset.r++;
    g_PaletteFades[g_Task->timer].offset.g++;
    g_PaletteFades[g_Task->timer].offset.b++;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.mode++;
    }
}
