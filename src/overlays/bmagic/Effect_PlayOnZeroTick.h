/* Plays the effect the target selector chose once the effect ticker (work byte
 * 0x0B) is zero. One definition shared by the bmagic effect modules; every change
 * here must verify every member. */
/* func_801EEDA4 (magic006), func_801EEEDC (magic039), func_801EF130 (magic041), func_801EED44 (magic042), func_801EF300 (magic043), func_801EEDA0 (magic044), func_801EEF10 (magic046), func_801EEE10 (magic048), func_801EEEA8 (magic050), func_801EF004 (magic053), func_801EEE30 (magic069), func_801EF2DC (magic070), func_801EF2DC (magic071), func_801EF2DC (magic072), func_801EF288 (magic076), func_801EED38 (magic079), func_801EF048 (magic087), func_801EEE40 (magic096), func_801EEDF8 (magic100), func_801EEF6C (magic101), func_801EEF18 (magic105), func_801EEE80 (magic106), func_801EEFF4 (magic115), func_801EEF0C (magic118), func_801EF064 (magic123), func_801EF050 (magic124), func_801EEE60 (magic125), func_801EEE70 (magic126), func_801EEF20 (magic129), func_801EEE74 (magic130), func_801EF060 (magic154), func_801EEE90 (magic158), func_801EED84 (magic159), func_801EF2D8 (magic162), func_801EEE90 (magic166), func_801EF1C8 (magic167), func_801EF2D8 (magic168), func_801EEDD8 (magic172), func_801EED90 (magic173), func_801EEDB8 (magic218), func_801EEFC4 (magic219), func_801EEF18 (magic220), func_801EEE80 (magic222), func_801EF278 (magic225), func_801EEFA4 (magic226) */
MATCH void Effect_PlayOnZeroTick(void) {
    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}
