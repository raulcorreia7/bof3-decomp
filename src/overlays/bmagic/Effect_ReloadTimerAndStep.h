/* Reloads the effect timer (work byte 0x09) with the value EFFECT_TIMER_RELOAD returns
 * and advances the effect step (work byte 0x02). One definition shared by the
 * bmagic effect modules; every change here must verify every member. */
/* Effect_ReloadTimerAndStep (magic009 through EFFECT_TIMER_RELOAD, magic004, magic008, magic021, magic065, magic154, magic161), Effect_ReloadTimerAndStep_801F17BC (magic008) */
/* The function whose return value reloads the timer; an image header sets it,
 * the default is func_800AFF98 (magic009 uses func_800B0058, the second table). */
#ifndef EFFECT_TIMER_RELOAD
#define EFFECT_TIMER_RELOAD func_800AFF98
#endif
/* The statements of Effect_ReloadTimerAndStep; each member has no locals. */
#define BMAGIC_RELOAD_TIMER_AND_STEP()                       \
    g_SpadWork->word_08.byte.unk_09 = EFFECT_TIMER_RELOAD(); \
    g_SpadWork->unk_02              = g_SpadWork->unk_02 + 1

MATCH void Effect_ReloadTimerAndStep(void) {
    BMAGIC_RELOAD_TIMER_AND_STEP();
}
