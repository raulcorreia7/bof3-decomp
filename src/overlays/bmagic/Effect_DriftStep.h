/* Moves the effect's actor one drift step and releases the ticker when the timer runs out. Every change here must verify every member. */
/* func_801EF59C (magic067), func_801EF2C4 (magic137) */
MATCH void Effect_DriftStep(void) {
    PartyBattler* work;
    u8            timer;
    u8            ticks;

    ticks                           = g_SpadWork->word_08.byte.unk_0B + 1;
    g_SpadWork->word_08.byte.unk_0B = ticks + (g_SpadWork->word_08.byte.unk_09 >> 6);
    if (g_FrameCount & 1) {
        g_SpadWork->word_08.byte.timer_0A -= 1;
    }
    g_SpadWork->unk_0C = 0x2000;
    g_SpadWork->unk_10 = 0;
    func_801DD350(g_SpadWork);
    work                      = g_SpadWork;
    timer                     = work->word_08.byte.unk_09 - 2;
    work->word_08.byte.unk_09 = timer;
    work->coord_x_34.raw += work->unk_0C;
    work->coord_y_38.raw += work->unk_10;
    if (timer == 0x30) {
        D_801EB4E0->word_08.byte.unk_0B -= 1;
        func_801E5988();
    }
}
