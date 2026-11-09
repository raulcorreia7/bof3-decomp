/* When the effect ticker (work byte 0x0B) is zero, ticks the effect ticker of
 * the g_BattleEffectBattler down and runs the effect step. One definition shared
 * by the bmagic effect modules; every change here must verify every member. */
/* func_801EF954 (magic038), func_801EF1A0 (magic046), func_801F033C (magic067), func_801EF2A0 (magic081), func_801EF744
   (magic083), func_801EF2A0 (magic105), func_801EF490 (magic213) */
MATCH void Effect_TickOnZeroTick(void) {
    PartyMember* work;

    if (g_Task->param.unk_0B == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}
