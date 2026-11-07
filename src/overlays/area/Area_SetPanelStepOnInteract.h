/* Sets the panel step counter to 4 while the interact input from g_InputMasks[INPUT_SLOT_DASH]
 * is held within 0x40 of the actor, and back to 3 otherwise. One body shared
 * by the members below; every change must verify every member.
 */
/* func_801F51F0 (area104), func_801F5734 (area121) */
MATCH void Area_SetPanelStepOnInteract(void) {
    if ((g_InputHeld & g_InputMasks[INPUT_SLOT_DASH]) && g_Task->param.unk_0B < 0x40) {
        g_GameState->counter_11C.u8_value = 4;
    } else {
        g_GameState->counter_11C.u8_value = 3;
    }
}
