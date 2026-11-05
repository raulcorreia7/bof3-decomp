/* Selects the battler in g_BattleSelectedActor, runs its selection hook, stores the result in the effect ticker byte (work byte 0x0B), clears the effect timer (work byte 0x09) and advances the effect step (work byte 0x01). One definition shared by the bmagic effect modules; every change here must verify every member. */
MATCH void Effect_SelectTargetAndAdvance(void) {
    PartyBattler** actor;

    actor = &g_BattleSelectedActor;
    func_80196718(*actor);
    g_SpadWork->word_08.byte.unk_0B = func_8019651C(*actor, 0, 0, 0, 1);
    g_SpadWork->word_08.byte.unk_09 = 0;
    g_SpadWork->step_01 += 1;
}
