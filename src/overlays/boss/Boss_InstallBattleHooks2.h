/* Publishes the area entry points Boss_ChooseBattleEnding2, Boss_EndBattle2 and Boss_HandleBattleEvent2 into g_Battle.choose_ending_hook, g_Battle.end_hook and g_Battle.boss_event_hook. */
/* func_800C1A88 (boss040), func_800C1A88 (boss049), func_800C1A94 (boss014), func_800C1AB0 (boss024), func_800C1C70
   (boss035), func_800C1E0C (boss036), func_800C1E3C (boss002), func_800C1FB0 (boss004), func_800C2088 (boss008),
   func_800C23F8 (boss018) */
MATCH void Boss_InstallBattleHooks2(void) {
    g_Battle.choose_ending_hook = Boss_ChooseBattleEnding2;
    g_Battle.end_hook           = Boss_EndBattle2;
    g_Battle.boss_event_hook    = Boss_HandleBattleEvent2;
}
