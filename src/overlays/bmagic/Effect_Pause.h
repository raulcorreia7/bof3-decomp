/* Advances the step while the ticker is under 2. */
/* func_801EEE68 (magic013), func_801EF070 (magic088), func_801EF048 (magic167) */
MATCH void Effect_Pause(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B < 2) {
        work->header.mode++;
    }
}
