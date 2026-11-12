#include "area040_13.h"

MATCH void func_801F2D28(void) {
    MESSAGE_REQUEST_CLEAR();
    if (MENU_SELECTION_IDLE()) {
        SYS_SetFlag(D_80144EA8, 11);
        func_801F2E78();
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
}
