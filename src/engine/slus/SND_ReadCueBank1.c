#include "engine/slus/slus.h"

/* Bank 1's cue reader: loads cue D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015EFAC */
MATCH void SND_ReadCueBank1(void) {
    SLUS_READ_BANK_CUE_HEAD(1, g_SndBankCues[1], g_SndBankHeaders[1])
    if (D_8018B3E0 != 0) {
        D_8018B30C = D_8018B3E0 & EMI_CUE_ALIAS_MASK;
        switch (D_8018B30C) {
            SLUS_CUE_ALIAS_ARM(2, g_SndBankHeaders[2], g_SndBankCues[2])
            SLUS_CUE_ALIAS_ARM(3, g_SndBankHeaders[3], g_SndBankCues[3])
            SLUS_CUE_ALIAS_ARM(4, g_SndBankHeaders[4], g_SndBankCues[4])
        }
    }
}
