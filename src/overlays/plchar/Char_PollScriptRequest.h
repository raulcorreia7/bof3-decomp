/* Polls the character script request once func_8014DAEC reports ready: a
 * pending request (work byte +0x07) starts its script and clears itself;
 * otherwise a free actor slot at the work byte +0x0B clears the +0x2B marker
 * and the panel mode byte in the game state record. One definition shared by
 * the plchar character programs; each program includes it where the function
 * sits, and a change must keep every member matching.
 */
MATCH void Char_PollScriptRequest(void) {
    if (g_SpadWork->unk_07 != 0) {
        if (func_8014DAEC() & BYTE_MASK) {
            Actor_RequestScript(g_SpadWork->direction_08);
            g_SpadWork->unk_07 = 0;
        }
    } else if ((func_8014DAEC() & BYTE_MASK) && (g_ActorSlots[g_SpadWork->unk_0B].flags_00 == 0)) {
        g_SpadWork->unk_2B             = 0;
        g_GameState->mode_12B.s8_value = 0;
    }
}
