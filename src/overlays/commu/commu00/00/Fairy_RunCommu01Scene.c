#include "commu00_00.h"

/* func_801F16BC */
MATCH void Fairy_RunCommu01Scene(void) {
    SYS_DISPATCH_BYTE(g_FairyCommu01States, g_SceneEventStep);
}
