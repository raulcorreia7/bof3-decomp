/* Chooses the battle ending: on a victory sets g_ScriptVars[0] to 0x0A and runs the victory path, else runs the defeat
 * path. One definition shared by the boss overlays; every change here must verify every member. */
/* Boss_ChooseBattleEnding (boss021 0x800C1C18, boss023 0x800C19C4) */
MATCH void Boss_ChooseBattleEnding(void) {
    if BATTLE_IS_VICTORY () {
        g_ScriptVars[0] = 0x0A;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
