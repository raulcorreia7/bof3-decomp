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
