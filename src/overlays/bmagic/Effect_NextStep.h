/* Advances the effect step and reloads the effect timer while the effect
 * ticker is under `limit`. One definition shared by the bmagic effect
 * modules; each member passes the limit. Every change here must verify every
 * member. */
static inline void BMagic_AdvanceEffectStep(u8 limit) {
    PartyBattler* work;

    work = g_Task;
    if (work->param.unk_0B < limit) {
        work->unk_09      = 8;
        work              = g_Task;
        work->header.mode = work->header.mode + 1;
    }
}
