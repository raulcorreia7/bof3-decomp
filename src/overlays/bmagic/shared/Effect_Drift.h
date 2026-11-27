/* Moves the effect's actor one drift step and releases the ticker when the timer runs out. */
/* func_801EF59C (magic067), func_801EF2C4 (magic137) */
MATCH void Effect_Drift(void) {
    PartyMember* work;
    u8           timer;
    u8           ticks;

    ticks                          = SELF(PartyMember)->param.phase + 1;
    SELF(PartyMember)->param.phase = ticks + (SELF(PartyMember)->unk_09 >> 6);
    if (g_FrameCount & 1) {
        SELF(PartyMember)->timer -= 1;
    }
    SELF(PartyMember)->unk_0C = 0x2000;
    SELF(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Self);
    work         = SELF(PartyMember);
    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (timer == 48) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}
