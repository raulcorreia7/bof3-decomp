#include "engine/slus/slus.h"

/* Bank 0's SE reader: loads SE D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015E994 */
MATCH void SND_SEReadBank0(void) {
    SLUS_READ_BANK_SE(0, g_SndBankSe[0], g_SndBankHeaders[0]);
}
