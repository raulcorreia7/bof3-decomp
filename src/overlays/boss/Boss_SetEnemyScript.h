/* Sets the current boss enemy script, mode handler and action table and starts task mode 2.
 * One definition shared by the boss overlays; every change here must verify every member. */
/* func_800C1980 (boss038), func_800C1858 (boss051) */
MATCH void Boss_SetEnemyScript(void) {
    Boss_StartEnemyScriptAction(g_BossEnemyScript, Boss_EnemyScriptMode, g_BossEnemyActionTable);
}
