/* Raises BATTLE_STATE_EFFECT_PLAYING and runs the battle effect helpers when func_801E30F8 is ready.
 * One definition shared by the boss overlays; every change here must verify every member. */
/* Boss_RaiseEffectPlaying (boss028 0x800C1AA0, boss055 0x800C1BF0) */
MATCH void Boss_RaiseEffectPlaying(void) {
    u16* flags;

    if (func_801E30F8() != 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5704();
        func_801E567C();
    }
}
