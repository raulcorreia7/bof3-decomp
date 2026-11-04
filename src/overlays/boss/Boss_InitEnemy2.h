/* Installs the enemy work script, mode and table pointers D_800C1B1C, func_800C18AC and D_800C1B28, raises its 0x8 flag
 * and moves the task work to mode 2. One definition shared by the boss overlays; each includes this file where the
 * function sits. */
MATCH void Boss_InitEnemy2(void) {
    EnemyBattler* work;

    work         = g_BattleCurrentEnemy;
    work->script = D_800C1B1C;
    work->unk_E4 = func_800C18AC;
    work->flags_104 |= COMBATANT_FLAG_MODE_HANDLER_ACTION;
    work->unk_E8 = D_800C1B28;
    ACTOR_SET_STEP(2);
    func_8014D978();
}
