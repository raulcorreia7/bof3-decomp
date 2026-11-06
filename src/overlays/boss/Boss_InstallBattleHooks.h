/* Publishes the area entry points Boss_ChooseBattleEnding, Boss_EndBattle and Boss_HandleBattleEvent into
 * g_BattleChooseEndingHook, g_BattleEndHook and g_BossBattleEventHook. One definition shared by the boss overlays;
 * each includes this file where the function sits. */
/* func_800C18F0 (boss015), func_800C18F0 (boss029), func_800C18FC (boss037), func_800C18FC (boss042), func_800C1908
   (boss050), func_800C1930 (boss054), func_800C1984 (boss023), func_800C19C4 (boss017), func_800C19C8 (boss031),
   func_800C19C8 (boss032), func_800C19DC (boss030), func_800C19E8 (boss014), func_800C19E8 (boss024), func_800C19F4
   (boss040), func_800C19F4 (boss049), func_800C1A08 (boss022), func_800C1A0C (boss007), func_800C1A14 (boss051),
   func_800C1AD0 (boss021), func_800C1B0C (boss052), func_800C1B40 (boss028), func_800C1B4C (boss035), func_800C1B68
   (boss012), func_800C1B7C (boss038), func_800C1C0C (boss004), func_800C1D50 (boss002), func_800C1D70 (boss033),
   func_800C1D78 (boss036), func_800C1E50 (boss001), func_800C1F9C (boss008), func_800C200C (boss013), func_800C2114
   (boss018), func_800C2340 (boss034), func_800C24A0 (boss055), func_800C2B60 (boss025) */
MATCH void Boss_InstallBattleHooks(void) {
    g_BattleChooseEndingHook = Boss_ChooseBattleEnding;
    g_BattleEndHook          = Boss_EndBattle;
    g_BossBattleEventHook    = Boss_HandleBattleEvent;
}
