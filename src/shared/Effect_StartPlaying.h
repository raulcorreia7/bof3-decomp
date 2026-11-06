/* Raises the effect-playing battle state and clears the effect work record. One
 * definition shared by images of several overlay groups; every change here
 * must verify every member.
 */
/* Effect_StartPlaying (boss051, boss054, magic001, magic002, magic008, magic015, magic020, magic021, magic054,
   magic056, magic103, magic110, magic111, magic150, magic161, magic169), Effect_StartPlaying_801EFA84 (magic001),
   Effect_StartPlaying_801EF728 (magic008), Effect_StartPlaying_801EFA40 (magic008), Effect_StartPlaying_801EFCFC
   (magic008), Effect_StartPlaying_801EF610 (magic015), Effect_StartPlaying_801EF9B0 (magic015) */
/* The statements of Effect_StartPlaying; each member declares flags. */
#define BATTLE_RAISE_EFFECT_PLAYING()                \
    BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING); \
    func_801E5988()

MATCH void Effect_StartPlaying(void) {
    u16* flags;

    BATTLE_RAISE_EFFECT_PLAYING();
}
