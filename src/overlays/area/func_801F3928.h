/* Raises the panel height at +0x30 by 0xA and clears state byte 0x03 once it
 * reaches 0xF0; sets that byte to 1 when D_801454F2 is 0, the state index is
 * not 2 and the game script is inactive, then draws panel 0x5C. One definition
 * shared by the area overlays; every change here must verify every member. */
/* func_801F3928 (area016), func_801F3928 (area045) */
MATCH void func_801F3928(void) {
    Actor* scratch;
    s32    armed;

    scratch = g_SpadWork;
    scratch->unk_30 += 0xA;
    if ((s16)scratch->unk_30 >= 0xF0) {
        scratch->unk_03 = 0;
    }
    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        armed              = 1;
        g_SpadWork->unk_03 = armed;
    }
    func_801F40C4(0x5C, g_SpadWork->unk_30);
}
