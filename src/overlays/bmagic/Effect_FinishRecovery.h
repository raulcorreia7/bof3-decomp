/* Finishes the effect on its targets. */
MATCH void Effect_FinishRecovery(void) {
    if (g_Task->param.unk_0B == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        Battle_MarkDamaged(g_Task->unk_04);
        func_801E5988();
    }
}
