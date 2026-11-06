/* Publishes the area entry points Boss_ChooseBattleEnding2, Boss_EndBattle2 and Boss_HandleBattleEvent2 into
 * g_BattleChooseEndingHook, g_BattleEndHook and g_BossBattleEventHook. One definition shared by the boss overlays;
 * each includes this file where the function sits. */
/* func_800C1A88 (boss040), func_800C1A88 (boss049), func_800C1A94 (boss014), func_800C1AB0 (boss024), func_800C1C70
   (boss035), func_800C1E0C (boss036), func_800C1E3C (boss002), func_800C1FB0 (boss004), func_800C2088 (boss008),
   func_800C23F8 (boss018) */
MATCH void Boss_InstallBattleHooks2(void) {
    g_BattleChooseEndingHook = Boss_ChooseBattleEnding2;
    g_BattleEndHook          = Boss_EndBattle2;
    g_BossBattleEventHook    = Boss_HandleBattleEvent2;
}
