MATCH void func_800C1934(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = BOSS_ENEMY_SCRIPT;
    work->unk_E4 = func_800C1998;
    work->turn.action_flags.value |= BATTLER_ACTION_OWN_MODE;
    work->unk_E8 = BOSS_ENEMY_STEP_DATA;
    ACTOR_SET_MODE(2);
    Script_AnimStepLoop();
}
