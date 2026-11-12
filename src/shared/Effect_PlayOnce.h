/* Plays the effect the target selector chose and clears it. */
/* Effect_PlayOnce (boss050, magic008, magic010, magic015, magic020, magic117, magic145, magic146),
   Effect_PlayOnce2 (magic117) */
/* The statements of Effect_PlayOnce; each member has no locals. */
#define BATTLE_PLAY_ONCE()                                  \
    Battle_MarkDamaged(g_Battle.target_selector);           \
    /* FAKE: keeps the flag load after the request call. */ \
    FAKE_BARRIER();                                         \
    g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;          \
    func_801E5988()

MATCH void Effect_PlayOnce(void) {
    BATTLE_PLAY_ONCE();
}
