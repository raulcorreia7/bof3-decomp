/* Darkens the palette fade row indexed by the effect timer (work byte 0x0A) by one on each colour channel. */
/* func_801EF1A0 (magic162), func_801EF1A0 (magic168) */
MATCH void Effect_FadePaletteOut(void) {
    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode++;
    }
}
