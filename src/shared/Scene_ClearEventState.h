/* Clears the script-active flag and the three scene event state bytes at
 * D_801448EB, D_801448EC and D_801448ED. One definition shared by the commu
 * and area overlays; every change here must verify every member.
 */
/* func_801F1684 (commu00), func_801F2F1C (area131), func_801F2CA4 (area187) */
MATCH void Scene_ClearEventState(void) {
    Game_ClearScriptActive();
    D_801448EB = 0;
    D_801448EC = 0;
    D_801448ED = 0;
}
