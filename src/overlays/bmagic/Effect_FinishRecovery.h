/* Finishes the effect on its targets. Every change must verify every member. */
MATCH void Effect_FinishRecovery(void) {
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        func_800A9820(g_Task->unk_04);
        func_801E5988();
    }
}
