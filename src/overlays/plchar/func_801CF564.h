/* Counts down the step byte; while it is nonzero it decrements the byte and
 * calls the step handler, at zero it clears the mode byte and game flag
 * 0x1000, then runs the follow-up call. One definition shared by the plchar
 * character programs; every change here must verify every member image. */
MATCH void func_801CF564(void) {
    if (g_SpadWork->unk_09 == 0) {
        g_GameState->mode_12B.s8_value = 0;
        g_GameFlags &= ~0x1000;
    } else {
        g_SpadWork->unk_09--;
        func_801B0DFC();
    }
    func_8014D978();
}
