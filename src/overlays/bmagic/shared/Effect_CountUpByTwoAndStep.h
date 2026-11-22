/* Counts the effect timer (work byte 0x09) up by two; at 0x10 it advances the effect step (work byte 0x02). */
/* func_801EF750 (magic021), func_801EF4D4 (magic041), func_801EF8C4 (magic111), func_801F01A8 (magic131), func_801F061C
   (magic222) */
MATCH void Effect_CountUpByTwoAndStep(void) {
    u8 timer;

    timer               = BMAGIC_WORK->unk_09 + 2;
    BMAGIC_WORK->unk_09 = timer;
    if (timer == 16) {
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;
    }
}
