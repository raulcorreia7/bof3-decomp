/* Counts the effect timer (work byte 0x09) down. */
/* Effect_TickOnTimerZero (magic172 and magic173 through EFFECT_TIMER_TICK, magic006, magic041, magic060, magic062, magic067, magic076, magic082, magic088, magic110, magic111, magic126, magic131, magic137, magic167, magic222, magic223), Effect_TickOnTimerZero3 (magic006), Effect_TickOnTimerZero2 (magic111 by 2). */
/* The effect timer's drop per tick in the member the header defines; an image header sets it, the default is 1. */
#ifndef EFFECT_TIMER_TICK
#define EFFECT_TIMER_TICK 1
#endif
/* The statements of Effect_TickOnTimerZero. */
#define BMAGIC_TICK_ON_TIMER_ZERO(step)                           \
    work         = g_Task;                                        \
    work->unk_09 = work->unk_09 - (step);                         \
    if (work->unk_09 == 0) {                                      \
        work               = (PartyMember*)g_BattleEffectBattler; \
        work->param.unk_0B = work->param.unk_0B - 1;              \
        func_801E5988();                                          \
    }

MATCH void Effect_TickOnTimerZero(void) {
    PartyMember* work;

    BMAGIC_TICK_ON_TIMER_ZERO(EFFECT_TIMER_TICK);
}
