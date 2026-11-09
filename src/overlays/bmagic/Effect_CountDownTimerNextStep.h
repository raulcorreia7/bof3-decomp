/* Counts the effect timer (work byte 0x09) down. */
/* func_801EF01C (magic009), func_801EEED4 (magic101), func_801EEEC0 (magic118) */
MATCH void Effect_CountDownTimerNextStep(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}
