/* Raises the effect and clears the actor when the counter ends; verify every image after a change. */
MATCH void Effect_RiseUntilTimerZero(void) {
    PartyMember* work = SELF(PartyMember);
    u8           timer;

    work->unk_14 += 0x20;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}
