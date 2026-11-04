/* Moves the panel height at +0x2E up by 0x10 and clears the actor state at
 * +0x02 below -0x2F, sets that state to 1 unless D_801454F2 is 2, then draws
 * the HUD at x 0x10 with the new height. One definition shared by the area
 * overlays; every change here must verify every member. */
/* func_801F3608 (area016), func_801F3608 (area045) */
MATCH void func_801F3608(void) {
    Actor* scratch;
    u8     mode;

    scratch = g_SpadWork;
    scratch->unk_2E -= 0x10;
    if ((s16)scratch->unk_2E < -0x2F) {
        scratch->state_02 = 0;
    }

    if (D_801454F2 != 2) {
        mode              = 1;
        scratch           = g_SpadWork;
        scratch->state_02 = mode;
    }

    Area_DrawHud(0x10, g_SpadWork->unk_2E);
}
