#include "commu00_00.h"

/* func_801F1F9C */
MATCH void Fairy_RunCommu03Scene(void) {
    SYS_DISPATCH_BYTE(g_FairyCommu03States, g_SceneEventState.step);
}
