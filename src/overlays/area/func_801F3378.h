/* One definition shared by the ten world04 area request overlays
 * (emi/world04/area176/13 through emi/world04/area185/13) at 0x801F3378;
 * every change here must verify every member address. */
MATCH s32 func_801F3378(u16 handler_x, u16 handler_y) {
    if (handler_x == 0x3F && handler_y == 0xE && g_Game.members[0].facing == FACING_UP) {
        if (g_SceneState.scenario_id >= 8) {
            g_SceneEventMode = 0x1A;
        } else {
            g_SceneEventMode = SCENE_EVENT_MESSAGE;
        }
        return 1;
    }
    return 0;
}
