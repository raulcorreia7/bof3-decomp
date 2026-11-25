#include "engine/slus/slus.h"

/* Bank 2's SE reader: loads SE g_SndSeRecord of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015F5C8 */
MATCH void SND_SEReadBank2(void) {
    SLUS_READ_BANK_SE_HEAD(2, g_SndBankSe[2], g_SndBankHeaders[2])
    if (g_SndSeAliasBank != 0) {
        g_SndSeVabId = g_SndSeAliasBank & EMI_SE_ALIAS_MASK;
        switch (g_SndSeVabId) {
            SLUS_SE_ALIAS_ARM(1, g_SndBankHeaders[1], g_SndBankSe[1])
            SLUS_SE_ALIAS_ARM(3, g_SndBankHeaders[3], g_SndBankSe[3])
            SLUS_SE_ALIAS_ARM(4, g_SndBankHeaders[4], g_SndBankSe[4])
        }
    }
}
