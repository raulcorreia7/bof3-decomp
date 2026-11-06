/* Clears the script-active flag and the three scene event state bytes at
 * g_SaveData.scene_event.mode, g_SaveData.scene_event.step and g_SaveData.scene_event.selection. One definition shared by the commu
 * and area overlays; every change here must verify every member.
 */
/* func_801F1684 (commu00), func_801F2F1C (area131), func_801F2CA4 (area187) */
MATCH void Scene_ClearEventState(void) {
    Game_ClearScriptActive();
    g_SaveData.scene_event.mode      = 0;
    g_SaveData.scene_event.step      = 0;
    g_SaveData.scene_event.selection = 0;
}
