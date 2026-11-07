/* Darkens the palette fade row indexed by the effect timer (work byte 0x0A) by one on each
 * colour channel; when the effect ticker (work byte 0x09) reaches zero it frees the fade of
 * the selected battler, tells the battle UI and advances the mode. One definition shared by
 * the bmagic effect modules; every change here must verify every member. */
/* func_801EF1A0 (magic162), func_801EF1A0 (magic168) */
MATCH void Effect_FadePaletteOut(void) {
    D_80145BD6[g_Task->timer].red_offset--;
    D_80145BD6[g_Task->timer].green_offset--;
    D_80145BD6[g_Task->timer].blue_offset--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        g_Task->header.mode++;
    }
}
