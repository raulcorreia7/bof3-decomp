/* Checks the step trigger at (x, y): a step into the trigger band with the scene ready clears the first script
 * variable and runs script entry 0, which starts the area scene and blocks the step. `first_row` is the band's
 * first row. Shared by the area overlays. */
static inline s32 Area_StepIntoTrigger(s32 x, s32 y, s32 first_row) {
    if (D_80143F03 == 2 && SYS_TestFlag(g_SceneEventFlags, 0x33) != 0 && (u32)((x >> 16) - 70) < 3U) {
        if ((u32)((y >> 16) - first_row) < 3U &&
            (g_BattlePartyBattlers[0].facing == FACING_UP_LEFT || (u32)(g_BattlePartyBattlers[0].facing - 6) < 2U)) {
            *g_ScriptVars = 0;
            func_801BE1B0(0);
            return 1;
        }
    }
    return 0;
}
