/* Skips the next script instruction when the current character is adult Ryu. */
/* func_801F3D38, func_801F4124 */
MATCH void Area_SkipScriptIfAdultRyu(void) {
    if (g_Game.current->chr.character_id == CHAR_ID_RYU_ADULT) {
        g_ScriptState->cursor = (u16)(g_ScriptState->cursor + 3);
    }
}
