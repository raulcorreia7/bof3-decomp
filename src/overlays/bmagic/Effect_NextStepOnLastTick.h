/* Advances the effect step when the active effect ticker is one. One
 * definition shared by the two bmagic effect modules; every change here must
 * verify every member. */
/* func_801EF524 (magic041), func_801F0644 (magic006) */
MATCH void Effect_NextStepOnLastTick(void) {
    PartyBattler* active;
    PartyBattler* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 1) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}
