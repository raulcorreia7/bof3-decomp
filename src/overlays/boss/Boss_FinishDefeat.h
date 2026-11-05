/* Finishes the boss's defeat: banks the spoils, stops the enemy script tick and
 * parks the task in the knock-out step. One definition shared by the boss
 * modules; every change here must verify every member. */
/* func_800C1938 (boss022), func_800C1940 (boss004), func_800C1B88 (boss002), func_800C18E4 (boss017) */
MATCH void Boss_FinishDefeat(void) {
    EnemyBattler* work;

    func_8014DAEC();
    func_801E54EC();
    work = g_BattleCurrentEnemy;
    work->flags_100 |= COMBATANT_FLAG_SKIP_ACTION_STEP;
    SPAD_WORK_BYTES[0] &= 0xBF;
    ACTOR_SET_STEP(3);
    SPAD_WORK_BYTES[2] = 0;
    SPAD_WORK_BYTES[3] = 0;
}
