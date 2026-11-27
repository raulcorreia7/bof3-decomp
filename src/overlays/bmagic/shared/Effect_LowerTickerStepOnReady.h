/* Lowers the ticker and advances the step once Script_AnimStepOnce reports ready. */
/* func_801EFA70 (magic004), func_801EF158 (magic161) */
MATCH void Effect_LowerTickerStepOnReady(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        SELF(PartyMember)->header.step++;
    }
}
