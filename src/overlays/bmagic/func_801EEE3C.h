/* Advances the effect counters and moves to the next step when the first reaches 0x10.
 * One definition shared by the images that include it;
 * every change here must verify every member. */
/* func_801EEE3C (magic055), func_801EEE3C (magic091) */
MATCH void func_801EEE3C(void) {
    g_Task->unk_09 += 1;
    g_Task->timer += 1;
    if (g_Task->unk_09 == 0x10) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}
