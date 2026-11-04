/* Counts the pause timer down, calling func_801B0DFC each tick; at zero it
 * clears the panel mode and game flag 0x1000. Runs func_8014D978 on every call.
 * One definition shared by the plchar character programs; every change here
 * must verify every member. */
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
