/* Reloads the effect timer and advances the effect step while the effect ticker is under 5. */
/* func_801EF4D0 (magic074), func_801EF4E4 (magic073), func_801EF640 (magic169) */
MATCH void Effect_NextStepUnderTickLimit(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B < 5) {
        work->unk_09      = 8;
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}
