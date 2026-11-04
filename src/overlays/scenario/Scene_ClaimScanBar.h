/* Starts the first free scan bar. Shared by the two scenario effect overlays;
 * each image header places g_ScanBars. Every change here must verify every
 * member. */
/* func_801D15DC (sce15ef2), func_801D25EC (sce15ef3) */
MATCH void Scene_ClaimScanBar(void) {
    s32      index;
    ScanBar* bar;

    bar   = g_ScanBars;
    index = 0;
    do {
        if (bar->in_use == 0) {
            bar->in_use = 1;
            bar->state  = 0;
            return;
        }
        index += 1;
        bar += 1;
    } while ((u32)(index & BYTE_MASK) < SCAN_BAR_COUNT);
}
