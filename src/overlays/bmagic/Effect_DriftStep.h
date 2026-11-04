/* One drift step of the effect: the ticker (work byte 0x0B) grows by one plus
 * the timer (0x09) / 64, the effect counter (0x0A) drops every second frame,
 * the actor moves by unk_0C and unk_10 (set to 0x2000 and 0 before
 * func_801DD350 reads them), and the timer drops by two until it reaches 0x30,
 * where the effect releases its ticker and runs func_801E5988. One definition
 * shared by the bmagic effect modules; every change here must verify every
 * member. */
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
