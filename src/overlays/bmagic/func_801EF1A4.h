/* Darkens the palette fade of the effect by one step; on the last step frees
 * the fade of the selected battler, tells the battle UI and goes to the next
 * mode. One definition shared by the bmagic overlays; every change here must
 * verify every member. */
/* func_801EF1A4 (magic070), func_801EF1A4 (magic071), func_801EF1A4 (magic072) */
MATCH void func_801EF1A4(void) {
    D_80145BD6[g_Task->timer].red_offset--;
    D_80145BD6[g_Task->timer].green_offset--;
    D_80145BD6[g_Task->timer].blue_offset--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_BattleSelectedActor);
        func_800AF814(g_BattleTargetSelector);
        g_Task->header.mode++;
    }
}
