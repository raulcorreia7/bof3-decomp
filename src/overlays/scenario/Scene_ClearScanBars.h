/* Clears every scan bar. Every change here must verify every member. */
/* func_801D15B0 (sce15ef2), func_801D25C0 (sce15ef3) */
MATCH void Scene_ClearScanBars(void) {
    s32      index;
    ScanBar* bar;

    bar   = g_ScanBars;
    index = 0;
    do {
        bar->in_use = 0;
        index += 1;
        bar += 1;
    } while ((u32)(index & BYTE_MASK) < SCAN_BAR_COUNT);
}
