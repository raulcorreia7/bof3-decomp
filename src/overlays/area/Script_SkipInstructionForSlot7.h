/* Skips the current script instruction when the game state holds slot
 * index 7.
 */
/* func_801F3D38, func_801F4124 */
MATCH void Script_SkipInstructionForSlot7(void) {
    if (g_GameState->slot_index_79 == 7) {
        g_ScriptState->cursor = (u16)(g_ScriptState->cursor + 3);
    }
}
