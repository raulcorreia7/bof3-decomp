/* Runs func_8014D978 and Area_AddActor; once the effect-playing flag is raised
 * it advances the effect step (work byte 0x02). One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* func_801EF2A8 (magic046), func_801F043C (magic067), func_801F007C (magic137) */
MATCH void Effect_AddActorStepOnPlaying(void) {
    func_8014D978();
    Area_AddActor();
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        g_SpadWork->unk_02++;
    }
}
