/* Counts the pause timer down and ends the pause at zero. Every change here must verify every member. */
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
