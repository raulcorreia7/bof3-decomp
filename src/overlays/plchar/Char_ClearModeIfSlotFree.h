/* Clears the panel mode byte in the game state record once the actor slot at
 * the work byte +0x0B is free, then runs func_8014D978. One definition shared
 * by the plchar character programs; each program includes it where the
 * function sits, and a change must keep every member matching.
 */
MATCH void Char_ClearModeIfSlotFree(void) {
    if (g_ActorSlots[g_SpadWork->unk_0B].flags_00 == 0) {
        g_GameState->mode_12B.s8_value = 0;
    }
    func_8014D978();
}
