#include "commu00_00.h"

/* func_801F1E74 */
MATCH void Fairy_RunCommu02Scene(void) {
    SYS_DISPATCH_BYTE(g_FairyCommu02States, g_SceneEventState.step);
}
