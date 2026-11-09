/* Advances the step when the ticker is zero. */
/* func_801EF068 (magic009), func_801EEEA8 (magic039), func_801EEDB0 (magic145), func_801EEFD0 (magic146) */
MATCH void Effect_NextStepOnZeroTick(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B == 0) {
        work->header.mode++;
    }
}
