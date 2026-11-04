/* Counts the effect timer (work byte 0x09) down; at zero it ticks the effect
 * ticker (work byte 0x0B) of the battler D_801EB4E0 and runs the effect step.
 * One definition shared by the bmagic effect modules; every change here must
 * verify every member. */
/* Effect_TickOnTimerZero (magic172 and magic173 through EFFECT_TIMER_TICK, magic006, magic041, magic060, magic062, magic067, magic076, magic082, magic088, magic110, magic111, magic126, magic131, magic137, magic167, magic222, magic223), Effect_TickOnTimerZero_801F0684 (magic006), Effect_TickOnTimerZero_801EF914 (magic111 by 2) */
/* The effect timer's drop per tick in the member the header defines; an image header
 * sets it, the default is 1. */
#ifndef EFFECT_TIMER_TICK
#define EFFECT_TIMER_TICK 1
#endif
/* The statements of Effect_TickOnTimerZero; each member declares work and
 * passes the amount the effect timer drops per tick. */
#define BMAGIC_TICK_ON_TIMER_ZERO(step)                             \
    work                      = g_SpadWork;                         \
    work->word_08.byte.unk_09 = work->word_08.byte.unk_09 - (step); \
    if (work->word_08.byte.unk_09 == 0) {                           \
        work                      = (PartyBattler*)D_801EB4E0;      \
        work->word_08.byte.unk_0B = work->word_08.byte.unk_0B - 1;  \
        func_801E5988();                                            \
    }

MATCH void Effect_TickOnTimerZero(void) {
    PartyBattler* work;

    BMAGIC_TICK_ON_TIMER_ZERO(EFFECT_TIMER_TICK);
}
