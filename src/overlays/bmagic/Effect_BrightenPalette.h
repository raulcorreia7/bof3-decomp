MATCH void Effect_BrightenPalette(void) {
    g_PaletteFades[g_Task->timer].offset.red++;
    g_PaletteFades[g_Task->timer].offset.green++;
    g_PaletteFades[g_Task->timer].offset.blue++;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.mode++;
    }
}
