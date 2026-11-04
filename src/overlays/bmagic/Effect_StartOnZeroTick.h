/* Raises the effect-playing flag and runs the effect step once the effect ticker
 * (work byte 0x0B) is zero. One definition shared by the bmagic effect modules;
 * every change here must verify every member. */
/* func_801F01E4 (magic008), func_801EEF84 (magic013), func_801EF084 (magic038), func_801EEEFC (magic040), func_801EEE58 (magic045), func_801EEEE4 (magic063), func_801EF284 (magic067), func_801EEF50 (magic074), func_801EF354 (magic082), func_801EF080 (magic083), func_801EF300 (magic088), func_801EEFB4 (magic092), func_801EEF38 (magic097), func_801EEF38 (magic098), func_801EF61C (magic131), func_801EED24 (magic143), func_801EEE50 (magic144), func_801EEF74 (magic213) */
MATCH void Effect_StartOnZeroTick(void) {
    u16* flags;

    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}
