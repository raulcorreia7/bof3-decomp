/* Counts the effect timer (work byte 0x09) up; at 0x10 it advances the effect step (work byte 0x02). */
/* Effect_CountUpAndStep (magic062, magic067, magic079, magic082, magic086, magic088, magic111, magic137, magic167,
   magic223, magic225), Effect_CountUpAndStep2 (magic079) */
/* The statements of Effect_CountUpAndStep. */
#define BMAGIC_COUNT_UP_AND_STEP()                                               \
    do {                                                                         \
        u8 timer;                                                                \
                                                                                 \
        timer                     = SELF(PartyMember)->unk_09 + 1;               \
        SELF(PartyMember)->unk_09 = timer;                                       \
        if (timer == 16) {                                                       \
            SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1; \
        }                                                                        \
    } while (0)

MATCH void Effect_CountUpAndStep(void) {
    BMAGIC_COUNT_UP_AND_STEP();
}
