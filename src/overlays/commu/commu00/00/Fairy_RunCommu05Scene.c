#include "commu00_00.h"

/* func_801F228C */
MATCH void Fairy_RunCommu05Scene(void) {
    SYS_DISPATCH_BYTE(g_FairyCommu05Steps, g_SceneEventState.step);
}
