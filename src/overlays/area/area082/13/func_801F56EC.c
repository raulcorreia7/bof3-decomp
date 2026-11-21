#include "area082_13.h"

MATCH void func_801F56EC(void) {
    UI_MessageStartArea(SYS_TestFlag(g_SceneFlags, 4) ? MSG_AREA082_ENTRY_DENIED_HOLY_GROUND : MSG_AREA082_ENTRY_DENIED_PERMIT);
    g_GameStateIndex = 2;
}
