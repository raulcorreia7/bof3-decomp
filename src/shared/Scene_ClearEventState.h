/* Clears the script-active flag and the three scene event state bytes at g_SceneEventState.mode, g_SceneEventState.step and g_SceneEventState.selection. */
/* func_801F1684 (commu00), func_801F2F1C (area131), func_801F2CA4 (area187) */
MATCH void Scene_ClearEventState(void) {
    Game_ClearScriptActive();
    g_SceneEventState.mode      = SCENE_EVENT_NONE;
    g_SceneEventState.step      = 0;
    g_SceneEventState.selection = 0;
}
