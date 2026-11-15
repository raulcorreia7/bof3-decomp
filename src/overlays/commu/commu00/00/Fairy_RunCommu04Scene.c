#include "commu00_00.h"

/* func_801F2020 */
MATCH void Fairy_RunCommu04Scene(void) {
    SYS_DISPATCH_BYTE(g_FairyCommu04States, g_SceneEventStep);
}
