/* Lowers the counter and raises the ticker and timer; when the timer reaches 0x10, sets the
 * battler's ticker to 0xFF and runs the effect step. One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EF1B8 (magic055), func_801EF1B8 (magic091) */
MATCH void func_801EF1B8(void) {
    u8 timer;

    g_Task->unk_09 -= 1;
    g_Task->param.unk_0B += 2;
    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if ((timer & 0xFF) == 0x10) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        func_801E5988();
    }
}
