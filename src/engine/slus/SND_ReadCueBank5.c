#include "engine/slus/slus.h"

/* Bank 5's cue reader: loads cue D_8018B404 of the bank into voice slot 0, fills one more slot per layer on the next voices (wrapping at 24). */
/* func_8016081C */
MATCH void SND_ReadCueBank5(void) {
    SLUS_READ_BANK_CUE(5, g_SndBankCues[5], g_SndBankHeaders[5]);
}
