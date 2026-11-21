/* Counts the step timer up and moves the stage byte on after 0x5A frames, steps the actor state when the game script is active or the state index is 2, then draws panel 0x5C. */
/* func_801F3828 (area016), func_801F3828 (area045) */
MATCH void func_801F3828(void) {
    Actor* scratch;

    scratch = g_Task;
    if (scratch->param.unk_0B == 0) {
        scratch->timer++;
        scratch = g_Task;
        if (scratch->timer >= 0x5A) {
            scratch->param.unk_0B++;
        }
    }

    if (D_801454F2 != 0 && g_Task->param.unk_0B != 0) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump; /* skips the 0x100 test: advance state byte 0x03 */
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done; /* skips the advance: panel `0x5C` draws next */
    }
bump:
    g_Task->unk_03++;
done:
    func_801F40C4(0x5C, g_Task->screen_y);
}
