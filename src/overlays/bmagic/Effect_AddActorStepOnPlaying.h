/* Adds the effect's actor and advances the step once the effect is playing. Every change here must verify every member. */
/* func_801EF2A8 (magic046), func_801F043C (magic067), func_801F007C (magic137) */
MATCH void Effect_AddActorStepOnPlaying(void) {
    func_8014D978();
    Area_AddActor();
    if (g_BattleState & BATTLE_STATE_EFFECT_PLAYING) {
        g_SpadWork->unk_02++;
    }
}
