/* Installs the enemy work script, mode and table pointers D_800C1990, func_800C18AC and D_800C199C, raises its 0x8 flag and moves the task work to mode 2. */
MATCH void Boss_InitEnemy(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1990;
    work->unk_E4 = func_800C18AC;
    work->turn.action_flags.value |= BATTLER_ACTION_OWN_MODE;
    work->unk_E8 = D_800C199C;
    ACTOR_SET_MODE(2);
    Script_AnimStepLoop();
}
