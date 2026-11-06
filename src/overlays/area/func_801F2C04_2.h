/* One definition shared by the area overlays; every change here must verify every member. */
MATCH s32 func_801F2C04(void) {
    Game_SetScriptActive();
    g_SceneEventMode      = 0x2C;
    g_SceneEventStep      = 0;
    g_SceneEventSelection = AREA_SCRIPT_VARIANT;
}
