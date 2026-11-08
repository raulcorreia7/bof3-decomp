/* Sets the current boss enemy script, mode handler and action table and starts task mode 2.
 * One definition shared by the boss overlays; every change here must verify every member. */
/* func_800C1980 (boss038), func_800C1858 (boss051) */
MATCH void Boss_SetEnemyScript(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = g_BossEnemyScript;
    work->unk_E4 = Boss_EnemyScriptMode;
    work->turn.action_flags.value |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8        = g_BossEnemyActionTable;
    g_Task->header.mode = 2;
    func_8014D978();
}
