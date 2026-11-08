#include "area144_13.h"

MATCH void func_801F2CA4(void) {
    if (func_801F34FC() == 0) {
        func_801F30CC();
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        g_Task->header.mode++;
    }
}
