/* Runs func_801DDED8 and sets g_SceneState.step_05 to 5 after a victory, and runs func_801DDF00 otherwise. One definition shared by the boss overlays; every change here must verify every member. */
/* func_800C1A34 (boss040), func_800C1A34 (boss049), func_800C2380 (boss034), func_800C1BBC (boss038), func_800C193C (boss042) */
MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_SceneState.step_05 = 5;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
