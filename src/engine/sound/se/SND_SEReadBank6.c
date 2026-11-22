#include "engine/slus/slus.h"

/* Bank 6's SE reader: loads SE g_SndSeRecord of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_80160E38 */
MATCH void SND_SEReadBank6(void) {
    SLUS_READ_BANK_SE(6, g_SndBankSe[6], g_SndBankHeaders[6]);
}
