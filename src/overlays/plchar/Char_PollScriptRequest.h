/* Answers the character's script request once func_8014DAEC reports ready: with
 * an option set it requests the script of the current facing and clears the
 * options; otherwise it clears the marker and the panel mode once the linked
 * actor's slot is free. One definition shared by the plchar character programs;
 * every change here must verify every member. */
MATCH void Char_PollScriptRequest(void) {
    if (g_SpadWork->option_flags != 0) {
        if (func_8014DAEC() & BYTE_MASK) {
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->option_flags = 0;
        }
    } else if ((func_8014DAEC() & BYTE_MASK) && (g_ActorSlots[g_SpadWork->unk_0B].flags_00 == 0)) {
        g_SpadWork->unk_2B             = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
}
