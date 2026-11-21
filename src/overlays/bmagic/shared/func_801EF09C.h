/* Raises the ticker and timer, lowers the counter by two and advances the step when it reaches 0x10. */
/* func_801EF09C (magic055), func_801EF09C (magic091) */
MATCH void func_801EF09C(void) {
    u8 counter;

    g_Task->param.unk_0B += 1;
    g_Task->timer += 2;
    counter        = g_Task->unk_09 - 2;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x10) {
        g_Task->header.mode += 1;
    }
}
