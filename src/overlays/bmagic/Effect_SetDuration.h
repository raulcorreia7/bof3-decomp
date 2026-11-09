/* Reloads the effect timer (work byte 0x09) with the value EFFECT_TIMER_RELOAD returns and advances the effect step (work byte 0x02). */
/* Effect_SetDuration (magic009 through EFFECT_TIMER_RELOAD, magic004, magic008, magic021, magic065, magic154,
   magic161), Effect_ReloadTimerAndStep2 (magic008) */
/* The function whose return value reloads the timer; an image header sets it,
 * the default is func_800AFF98 (magic009 uses func_800B0058, the second table). */
#ifndef EFFECT_TIMER_RELOAD
#define EFFECT_TIMER_RELOAD func_800AFF98
#endif
/* The statements of Effect_SetDuration; each member has no locals. */
#define BMAGIC_RELOAD_TIMER_AND_STEP()            \
    g_Task->unk_09      = EFFECT_TIMER_RELOAD();  \
    g_Task->header.step = g_Task->header.step + 1

MATCH void Effect_SetDuration(void) {
    BMAGIC_RELOAD_TIMER_AND_STEP();
}
