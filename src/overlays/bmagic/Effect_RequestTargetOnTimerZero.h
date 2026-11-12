/* Counts the effect timer (work byte 0x09) down; at zero it requests the target selector for the effect with Battle_ApplyDamageFlags and advances the step (work byte 0x01). */
/* func_801EEF9C (magic053), func_801EEF88 (magic124), func_801EEEB8 (magic129), func_801EEE0C (magic130), func_801EF03C
   (magic132), func_801EEEB0 (magic220), func_801EEF4C (magic223), func_801EEF3C (magic226) */
MATCH void Effect_RequestTargetOnTimerZero(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}
