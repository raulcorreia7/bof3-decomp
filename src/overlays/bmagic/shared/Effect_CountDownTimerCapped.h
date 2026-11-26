/* Raises the effect timer (work byte 0x09) by one up to 0x2E, counts the effect counter (0x0A) down, and finishes the effect at zero like Effect_CountDownTimer. */
/* Effect_CountDownTimerCapped (magic056, magic103) */
MATCH void Effect_CountDownTimerCapped(void) {
    PartyMember* first;
    PartyMember* work;
    PartyMember* active;
    u8           timer;
    u8           count;

    first = SELF(PartyMember);
    timer = first->unk_09;
    if (timer != 0x2E) {
        first->unk_09 = timer + 1;
    }
    work        = SELF(PartyMember);
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Effect_Reset();
    }
}
