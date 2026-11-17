/* Darkens the palette fade of the effect by one step; on the last step frees the fade of the selected battler, tells the battle UI and goes to the next mode. */
/* func_801EF1A4 (magic070), func_801EF1A4 (magic071), func_801EF1A4 (magic072) */
MATCH void func_801EF1A4(void) {
    g_PaletteFades[g_Task->timer].offset.r--;
    g_PaletteFades[g_Task->timer].offset.g--;
    g_PaletteFades[g_Task->timer].offset.b--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        Battle_FadePoisonedBattler(g_Battle.target_selector);
        g_Task->header.mode++;
    }
}
