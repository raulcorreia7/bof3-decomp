#include "engine/slus/slus.h"

/* Bank 0's cue reader: loads cue D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
MATCH void func_8015E994(void) {
    SLUS_READ_BANK_CUE(0, D_801486A0, D_80148A18);
}
