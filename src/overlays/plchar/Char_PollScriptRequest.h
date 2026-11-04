/* Answers the character's script request once ready. Every change here must verify every member. */
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
