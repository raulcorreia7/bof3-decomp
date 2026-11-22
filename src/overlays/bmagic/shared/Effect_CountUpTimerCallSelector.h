/* Marks the selected battlers pending. */
/* func_801EF2EC (magic120), func_801EF1C4 (magic122) */
MATCH void Effect_CountUpTimerCallSelector(void) {
    PartyMember* work;
    u8           timer;

    work               = TASK(PartyMember);
    work->param.unk_0B = work->param.unk_0B - 1;
    work               = TASK(PartyMember);
    timer              = work->unk_09 + 1;
    work->unk_09       = timer;
    if (timer == 24) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        work              = TASK(PartyMember);
        work->header.step = work->header.step + 1;
    }
}
