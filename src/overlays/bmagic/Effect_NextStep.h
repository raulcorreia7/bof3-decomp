/* Advances the effect step and reloads the effect timer while the effect
 * ticker is under EFFECT_STEP_LIMIT. One definition shared by the bmagic effect
 * modules; each image header sets the limit. Every change here must verify every
 * member. */
/* func_801EF078 (magic062), func_801EF0C4 (magic082), func_801EF158 (magic162), func_801EF158 (magic168), func_801EF15C (magic070), func_801EF15C (magic071), func_801EF15C (magic072) */
MATCH void Effect_NextStep(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->unk_0B < EFFECT_STEP_LIMIT) {
        work->unk_09      = 8;
        work              = g_Task;
        work->header.mode = work->header.mode + 1;
    }
}
