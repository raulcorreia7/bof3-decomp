/* Clears scene event flag 0x46 and returns the area scene mode to its idle
 * value. One body shared by the members below; every change must verify every
 * member.
 */
/* func_801F39A4 (area148), func_801F3F28 (area167) */
MATCH void Area_ClearSceneFlag46AndResetMode(void) {
    SYS_ClearFlag(g_SceneEventFlags, 0x46);
    g_AreaSceneMode = 0;
}
