#include "sisyou_00.h"

/* Panel-lock flag owned by the main executable. */

/* FAKE: retail materializes the byte address at each read; the record member reuses one. */
MATCH void func_801D2614(void) {
    s32 step;

    if (SYS_TestFlag(D_8014554F, g_SceneEventSelection) != 0) {
        step = 5;
    } else if (g_SceneEventSelection == MASTER_DEIS) {
        MESSAGE_START_WAIT(MASTER_MESSAGE_DEIS_UNAVAILABLE);
        step = 6;
    } else {
        step = 1;
    }
    g_MenuMasterStep = step;
}
