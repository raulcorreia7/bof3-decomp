/* Adds the effect's actor and advances the step once the effect is playing. */
/* func_801EF2A8 (magic046), func_801F043C (magic067), func_801F007C (magic137) */
MATCH void Effect_AddActor(void) {
    Script_AnimStepLoop();
    Area_AddActor();
    if (g_Battle.flags & BATTLE_STATE_EFFECT_PLAYING) {
        SELF(PartyMember)->header.step++;
    }
}
