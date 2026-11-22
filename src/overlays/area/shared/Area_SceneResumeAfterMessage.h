/* Clears the message request and, with no menu selection pending, marks
 * the scene scripted and moves it to step 0x14.
 */
/* func_801F2F40, func_801F2CA8 */
MATCH void Area_SceneResumeAfterMessage(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        Game_SetScriptActive();
        g_ScenarioState.state_04 = 1;
        g_ScenarioState.step     = 0x14;
    }
}
