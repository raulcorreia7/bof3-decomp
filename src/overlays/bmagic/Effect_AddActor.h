/* Adds the effect's actor and advances the step once the effect is playing. Every change here must verify every member.
*/
/* func_801EF2A8 (magic046), func_801F043C (magic067), func_801F007C (magic137) */
MATCH void Effect_AddActor(void) {
    func_8014D978();
    Area_AddActor();
    if (g_Battle.state & BATTLE_STATE_EFFECT_PLAYING) {
        g_Task->header.step++;
    }
}
