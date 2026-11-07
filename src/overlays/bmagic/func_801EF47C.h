/* Waits out the launch delay of the current sparkle D_801F17B4, then places it
 * at a random offset from the screen point of its battler, picks its drift,
 * sway phase and rise, and goes to the rise step. One definition shared by the
 * bmagic overlays; every change here must verify every member. */
/* func_801EF47C (magic070), func_801EF47C (magic071), func_801EF47C (magic072) */
MATCH void func_801EF47C(void) {
    PartyBattler* battler;

    if (--D_801F17B4->timer_05 == 0) {
        battler            = D_801EB4E0;
        D_801F17B4->pos.x  = battler->pos.x;
        D_801F17B4->pos.y  = battler->pos.y;
        D_801F17B4->pos.z  = battler->pos.z;
        D_801F17B4->unk_20 = battler->unk_2E.half;
        D_801F17B4->unk_22 = battler->unk_30.half;
        if (D_801F00BC[D_801F17B4->unk_07 & 0x1F].x < 0) {
            D_801F17B4->unk_20 += D_801F00BC[D_801F17B4->unk_07 & 0x1F].x - (rand() & 7);
        } else {
            D_801F17B4->unk_20 += D_801F00BC[D_801F17B4->unk_07 & 0x1F].x + (rand() & 7);
        }
        D_801F17B4->unk_22 -= D_801F00BC[D_801F17B4->unk_07 & 0x1F].y + (rand() & 7);
        /* FAKE: reread the work pointer after the y store. */
        MATCH_FAKE_BARRIER();
        D_801F17B4->unk_08   = D_801F17B4->unk_20;
        D_801F17B4->unk_0A   = rand() & 1;
        D_801F17B4->phase_0C = rand();
        D_801F17B4->unk_07   = D_801F01A8[D_801F17B4->unk_04] + (rand() & 6);
        D_801F17B4->timer_05 = 16;
        D_801F17B4->unk_06   = 0;
        D_801F17B4->header.step++;
    }
}
