#include "area030_04.h"

/* Queues a mode-specific cue when the current local mode changed. */
MATCH void func_801DDD4C(void) {
    if (D_801E31F8 != D_801E31FC) {
        switch (D_801E31F8) {
            case 0:
                SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 3));
                break;
            case 1:
                SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 2));
                break;
            case 2:
                SND_PlaySE(EMI_SE_ID(SND_BANK_AREA, 5));
                break;
        }
    }
}
