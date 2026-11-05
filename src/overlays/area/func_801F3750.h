/* Lowers the panel height by 0xA, advances the actor state when it drops below
 * 0xC9, forces the state to 3 when the game script is active or the state index
 * is 2, then draws panel 0x5C. One definition shared by the area overlays;
 * every change here must verify every member. */
/* func_801F3750 (area016), func_801F3750 (area045) */
MATCH void func_801F3750(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    scratch->unk_30 -= 0xA;
    if ((s16)scratch->unk_30 < 0xC9) {
        scratch->unk_03++;
    }

    if (D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) {
        goto force; /* skips the 0x100 test: force state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force; /* skips the 0x100 test: force state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the forced write: panel `0x5C` draws next */
    }
force:
    ((u8*)g_SpadWork)[0x03] = 3;
done:
    func_801F40C4(0x5C, g_SpadWork->unk_30);
}
