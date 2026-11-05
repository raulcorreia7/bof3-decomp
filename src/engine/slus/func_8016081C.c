#include "engine/slus/slus.h"

/* Bank 5's cue reader: loads cue D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
MATCH void func_8016081C(void) {
    SLUS_READ_BANK_CUE(5, D_8014890C, D_80148A2C);
}
