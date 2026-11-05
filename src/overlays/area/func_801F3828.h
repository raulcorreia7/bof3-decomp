/* Counts the step timer up and moves the stage byte on after 0x5A frames,
 * steps the actor state when the game script is active or the state index is 2,
 * then draws panel 0x5C. One definition shared by the area overlays; every
 * change here must verify every member. */
/* func_801F3828 (area016), func_801F3828 (area045) */
MATCH void func_801F3828(void) {
    Actor* scratch;

    scratch = g_SpadWork;
    if (((u8*)scratch)[0xB] == 0) {
        ((u8*)scratch)[9]++;
        scratch = g_SpadWork;
        if (((u8*)scratch)[9] >= 0x5A) {
            ((u8*)scratch)[0xB]++;
        }
    }

    if (D_801454F2 != 0 && ((u8*)g_SpadWork)[0x0B] != 0) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the advance: panel `0x5C` draws next */
    }
bump:
    ((u8*)g_SpadWork)[3]++;
done:
    func_801F40C4(0x5C, g_SpadWork->unk_30);
}
