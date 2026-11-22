/* Runs Battle_EndVictory and sets g_ScenarioState.step to 5 after a victory, and runs Battle_EndDefeat otherwise. */
/* func_800C1A34 (boss040), func_800C1A34 (boss049), func_800C2380 (boss034), func_800C1BBC (boss038), func_800C193C
   (boss042) */
MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScenarioState.step = 5;
        Battle_EndVictory();
    } else {
        Battle_EndDefeat();
    }
}
