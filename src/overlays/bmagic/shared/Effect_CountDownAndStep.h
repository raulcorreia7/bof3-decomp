/* Counts the effect counter (work byte 0x0A) down; at zero it advances the effect step (work byte 0x02). */
/* Effect_CountDownAndStep (magic062, magic067, magic076, magic078, magic082, magic111, magic131, magic137, magic222),
   Effect_CountDownAndStep2 (magic131) */
/* The statements of Effect_CountDownAndStep. */
#define BMAGIC_COUNT_DOWN_AND_STEP()                                             \
    do {                                                                         \
        u8 count;                                                                \
                                                                                 \
        count                    = SELF(PartyMember)->timer - 1;                 \
        SELF(PartyMember)->timer = count;                                        \
        if (count == 0) {                                                        \
            SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1; \
        }                                                                        \
    } while (0)

MATCH void Effect_CountDownAndStep(void) {
    BMAGIC_COUNT_DOWN_AND_STEP();
}
