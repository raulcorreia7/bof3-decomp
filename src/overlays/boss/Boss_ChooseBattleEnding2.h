/* Chooses the battle ending: on a victory result sets the scenario continuation
 * and runs the victory path, else runs the defeat path. Shared by the boss
 * modules; every change here must verify every member. */
/* func_800C1AD4 (boss014), func_800C1AF0 (boss024), func_800C1CB0 (boss035), func_800C1E4C (boss036) */
MATCH void Boss_ChooseBattleEnding2(void) {
    if (g_BattleResult & BATTLE_RESULT_VICTORY) {
        g_SceneState.step_05 = 5;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
