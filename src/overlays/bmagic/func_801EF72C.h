/* Sways the effect work record: phase_0C advances and its low six bits set the
 * wave (also stored in the scratchpad halfword at 0x1F800006), which moves
 * unk_20 around unk_08 by 0x18 * sin; unk_22 grows by unk_0A; unk_06 drops every
 * fourth frame; at timer_05 zero the effect steps and the work record clears.
 * One definition shared by the bmagic overlays; every change here must verify
 * every member. */
/* func_801EF72C (magic070), func_801EF72C (magic071), func_801EF72C (magic072) */
MATCH void func_801EF72C(void) {
    u16 phase;
    u8  timer;

    phase                = D_801F17B4->phase_0C + 1;
    D_801F17B4->phase_0C = phase;
    phase                = phase & 0x3F;
    SP_REF(s16, 6)       = phase << 6;
    D_801F17B4->unk_20   = D_801F17B4->unk_08 + ((rsin(phase << 6) * 0x18) >> 0xC);
    D_801F17B4->unk_22   = D_801F17B4->unk_22 + D_801F17B4->unk_0A;
    if ((g_FrameCount & 3) == 0) {
        D_801F17B4->unk_06 = D_801F17B4->unk_06 - 1;
    }
    timer                = D_801F17B4->timer_05 - 1;
    D_801F17B4->timer_05 = timer;
    if (timer == 0) {
        D_801EB4E0->unk_0B -= 1;
        func_801F006C();
    }
}
