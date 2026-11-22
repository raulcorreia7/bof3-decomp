#include "engine/slus/slus.h"

/* Bank 5's SE reader: loads SE g_SndSeRecord of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8016081C */
MATCH void SND_SEReadBank5(void) {
    SLUS_READ_BANK_SE(5, g_SndBankSe[5], g_SndBankHeaders[5]);
}
