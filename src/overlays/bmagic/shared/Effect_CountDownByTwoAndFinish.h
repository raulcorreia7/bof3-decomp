/* Counts the wait down by two and finishes the effect at zero. */
/* func_801EF488 (magic097), func_801EF498 (magic098), func_801EF100 (magic143), func_801F1380 (magic151) */
MATCH void Effect_CountDownByTwoAndFinish(void) {
    PartyMember* active;

    TASK(PartyMember)->param.unk_0B = TASK(PartyMember)->param.unk_0B + 1;
    TASK(PartyMember)->timer        = TASK(PartyMember)->timer - 2;
    if (TASK(PartyMember)->timer == 0) {
        active               = BATTLE_ACTIVE_WORK;
        active->param.unk_0B = active->param.unk_0B - 1;
        Effect_Reset();
    }
}
