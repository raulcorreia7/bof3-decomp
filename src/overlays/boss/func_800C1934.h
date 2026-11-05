/* One definition shared by the boss overlays; every change here must verify every member. */
MATCH void func_800C1934(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = BOSS_ENEMY_SCRIPT;
    work->unk_E4 = func_800C1998;
    work->flags_104 |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = BOSS_ENEMY_STEP_DATA;
    ACTOR_SET_STEP(2);
    func_8014D978();
}
