/* Advances the effect step when the active effect ticker is one. */
/* func_801EF524 (magic041), func_801F0644 (magic006) */
MATCH void Effect_NextStepOnLastTick(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 1) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}
