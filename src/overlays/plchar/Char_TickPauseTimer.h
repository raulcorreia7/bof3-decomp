/* Counts the work byte +0x09 down and calls func_801B0DFC each tick; at zero
 * it clears the panel mode byte and game flag 0x1000, then runs func_8014D978.
 * One definition shared by the plchar character programs; each program
 * includes it where the function sits, and a change must keep every member
 * matching.
 */
MATCH void Char_TickPauseTimer(void) {
    if (g_SpadWork->unk_09 == 0) {
        g_GameState->mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_SpadWork->unk_09--;
        func_801B0DFC();
    }
    func_8014D978();
}
