#include "engine/slus/slus.h"

/* Bank 3's SE reader: loads SE g_SndSeRecord of the bank into layer 0,
 * fills one more layer on each next voice (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015FBE4 */
MATCH void SND_SEReadBank3(void) {
    SLUS_READ_BANK_SE_HEAD(3, g_SndBankSe[3], g_SndBankHeaders[3])
    if (g_SndSeAliasBank != 0) {
        g_SndSeVabId = g_SndSeAliasBank & EMI_SE_ALIAS_MASK;
        switch (g_SndSeVabId) {
            SLUS_SE_ALIAS_ARM(1, g_SndBankHeaders[1], g_SndBankSe[1])
            SLUS_SE_ALIAS_ARM(2, g_SndBankHeaders[2], g_SndBankSe[2])
            SLUS_SE_ALIAS_ARM(4, g_SndBankHeaders[4], g_SndBankSe[4])
        }
    }
}
