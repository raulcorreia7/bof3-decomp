#include "commu00_00.h"

/* func_801F1F10 */
MATCH void Fairy_RunCommu02Events(void) {
    SYS_DISPATCH_BYTE(g_FairyCommu02Events, g_SceneEventSelection);
}
