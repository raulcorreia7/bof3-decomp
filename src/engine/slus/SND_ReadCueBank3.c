#include "engine/slus/slus.h"

/* Bank 3's cue reader: loads cue D_8018B404 of the bank into voice slot 0,
 * fills one more slot per layer on the next voices (wrapping at 24), then lets
 * an alias bank supply the tone and voice. */
/* func_8015FBE4 */
MATCH void SND_ReadCueBank3(void) {
    SLUS_READ_BANK_CUE_HEAD(3, D_80148814, D_80148A24)
    if (D_8018B3E0 != 0) {
        D_8018B30C = D_8018B3E0 & EMI_CUE_ALIAS_MASK;
        switch (D_8018B30C) {
            SLUS_CUE_ALIAS_ARM(1, D_80148A1C, D_8014871C)
            SLUS_CUE_ALIAS_ARM(2, D_80148A20, D_80148798)
            SLUS_CUE_ALIAS_ARM(4, D_80148A28, D_80148890)
        }
    }
}
