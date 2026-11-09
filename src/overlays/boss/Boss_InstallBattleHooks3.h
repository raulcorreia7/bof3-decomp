/* Publishes the area entry points Boss_ChooseBattleEnding3, Boss_EndBattle3 and Boss_HandleBattleEvent3 into g_Battle.choose_ending_hook, g_Battle.end_hook and g_Battle.boss_event_hook. each includes this file where the function sits. */
/* func_800C1F08 (boss002), func_800C2184 (boss008), func_800C234C (boss004), func_800C26DC (boss018) */
MATCH void Boss_InstallBattleHooks3(void) {
    g_Battle.choose_ending_hook = Boss_ChooseBattleEnding3;
    g_Battle.end_hook           = Boss_EndBattle3;
    g_Battle.boss_event_hook    = Boss_HandleBattleEvent3;
}
