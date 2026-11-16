#include "commu00_00.h"

/* func_801F18BC */
MATCH void Fairy_RunGiftScene(void) {
    SYS_DISPATCH_BYTE(g_FairyGiftSteps, g_SceneEventState.step);
}
