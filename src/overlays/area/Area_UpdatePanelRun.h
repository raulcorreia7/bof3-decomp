/* Sets the panel step counter to 4 while the run button (WORLD_INPUT_RUN)
 * is held within 0x40 of the actor, and back to 3 otherwise. One body shared
 * by the members below; every change must verify every member.
 */
/* func_801F51F0 (area104), func_801F5734 (area121) */
MATCH void Area_UpdatePanelRun(void) {
    if ((g_InputHeld & g_InputMasks[WORLD_INPUT_RUN]) && g_Task->param.unk_0B < 0x40) {
        g_GameState->u.field.counter_11C.u8_value = 4;
    } else {
        g_GameState->u.field.counter_11C.u8_value = 3;
    }
}
