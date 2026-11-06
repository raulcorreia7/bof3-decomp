/* Counts byte 0x09 down; at zero it loads byte 0x0B with a random value
 * below 16, clears bytes 0x09 and 0x0A and steps the handler.
 */
/* func_801EF114, func_801EF124 */
MATCH void Effect_CountDownAndPickRandom(void) {
    u8 counter;

    counter        = g_Task->unk_09 - 1;
    g_Task->unk_09 = counter;
    if (!(counter & 0xFF)) {
        g_Task->unk_0B = rand() & 0xF;
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->header.step += 1;
    }
}
