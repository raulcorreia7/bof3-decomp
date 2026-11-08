#include "engine/slus/slus.h"

/* Bank 6's cue reader: loads cue D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_80160E38 */
MATCH void SND_ReadCueBank6(void) {
    SLUS_READ_BANK_CUE(6, g_SndBankCues[6], g_SndBankHeaders[6]);
}
