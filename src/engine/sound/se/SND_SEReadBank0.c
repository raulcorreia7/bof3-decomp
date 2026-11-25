#include "engine/slus/slus.h"

/* Bank 0's SE reader: loads SE g_SndSeRecord of the bank into layer 0,
 * fills one more layer on each next voice (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015E994 */
MATCH void SND_SEReadBank0(void) {
    SLUS_READ_BANK_SE(0, g_SndBankSe[0], g_SndBankHeaders[0]);
}
