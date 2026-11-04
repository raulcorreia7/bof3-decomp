/* Counts the effect timer (work byte 0x09) down; at zero it queues the
 * selection effect 0x100 and advances the step byte (work byte 0x01). One
 * definition shared by the bmagic effect modules; every change here must
 * verify every member. */
/* func_801EEDB0 (magic048), func_801EEE20 (magic222) */
MATCH void Effect_CountDownTimerQueueFx(void) {
    PartyBattler* work;

    work                      = g_SpadWork;
    work->word_08.byte.unk_09 = work->word_08.byte.unk_09 - 1;
    if (work->word_08.byte.unk_09 == 0) {
        SND_QueueSelectionFx(0x100);
        g_SpadWork->step_01 = g_SpadWork->step_01 + 1;
    }
}
