MATCH void Effect_BrightenPalette(void) {
    D_80145BD6[g_Task->timer].red_offset++;
    D_80145BD6[g_Task->timer].green_offset++;
    D_80145BD6[g_Task->timer].blue_offset++;
    if (--g_Task->unk_09 == 0) {
        g_Task->mode++;
    }
}
