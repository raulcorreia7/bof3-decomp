/* Lowers the ticker and advances the step once func_8014DAEC reports ready. Every change here must verify every member.
*/
/* func_801EFA70 (magic004), func_801EF158 (magic161) */
MATCH void Effect_LowerTickerStepOnReady(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->unk_0B--;
        g_Task->header.step++;
    }
}
