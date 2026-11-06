/* Clears the script-active flag and the three scene event state bytes at
 * g_SceneEventMode, g_SceneEventStep and g_SceneEventSelection. One definition shared by the commu
 * and area overlays; every change here must verify every member.
 */
/* func_801F1684 (commu00), func_801F2F1C (area131), func_801F2CA4 (area187) */
MATCH void Scene_ClearEventState(void) {
    Game_ClearScriptActive();
    g_SceneEventMode      = SCENE_EVENT_NONE;
    g_SceneEventStep      = 0;
    g_SceneEventSelection = 0;
}
