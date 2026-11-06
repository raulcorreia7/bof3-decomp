/* Moves the effect's actor one drift step and releases the ticker when the timer runs out. Every change here must
   verify every member. */
/* func_801EF59C (magic067), func_801EF2C4 (magic137) */
MATCH void Effect_DriftStep(void) {
    PartyBattler* work;
    u8            timer;
    u8            ticks;

    ticks          = g_Task->unk_0B + 1;
    g_Task->unk_0B = ticks + (g_Task->unk_09 >> 6);
    if (g_FrameCount & 1) {
        g_Task->timer -= 1;
    }
    g_Task->unk_0C = 0x2000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    work         = g_Task;
    timer        = work->unk_09 - 2;
    work->unk_09 = timer;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (timer == 0x30) {
        D_801EB4E0->unk_0B -= 1;
        func_801E5988();
    }
}
