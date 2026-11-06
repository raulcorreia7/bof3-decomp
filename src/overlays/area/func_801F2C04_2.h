/* One definition shared by the area overlays; every change here must verify every member. */
MATCH s32 func_801F2C04(void) {
    Game_SetScriptActive();
    g_SaveData.scene_event.mode      = 0x2C;
    g_SaveData.scene_event.step      = 0;
    g_SaveData.scene_event.selection = AREA_SCRIPT_VARIANT;
}
