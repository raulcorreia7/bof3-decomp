/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F3378;
 * every change here must verify every member address. */
MATCH s32 func_801F3378(u16 handler_x, u16 handler_y) {
    if (handler_x == 0x3F && handler_y == 0xE && g_BattlePartyBattlers[0].facing == 1) {
        if (g_SceneState.scenario_id >= 8) {
            D_801448EB = 0x1A;
        } else {
            D_801448EB = 6;
        }
        return 1;
    }
    return 0;
}
