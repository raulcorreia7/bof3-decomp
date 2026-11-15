/* Steps each scan bar through its claim, rise and fall states, and returns whether one is live. */
/* Scene_UpdateScanBars (sce15ef2, sce15ef3) */
MATCH u8 Scene_UpdateScanBars(s32 y) {
    MATRIX   matrix;
    ScanBar* bar;
    u8       live;
    u8       i;

    live = 0;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x380, 0x100), 0);
    GFX_AddPrim(7u, sizeof(DR_MODE));
    Area_SetCameraMatrix(&matrix);
    bar = g_ScanBars;
    i   = 0;
    do {
        if (bar->in_use != 0) {
            live = 1;
            switch (bar->state) {
                case 0:
                    bar->unk_01      = 4;
                    bar->half_height = 4;
                    bar->y           = y;
                    bar->state += 1;
                    break;
                case 1:
                    bar->state += 1;
                    break;
                case 2:
                    bar->y -= 8;
                    if (bar->y < 0) {
                        bar->in_use = 0;
                    }
                    break;
            }
            if (bar->state != 0) {
                Scene_DrawScanBar(bar);
            }
        }
        bar += 1;
        i += 1;
    } while (i < SCAN_BAR_COUNT);
    return live;
}
