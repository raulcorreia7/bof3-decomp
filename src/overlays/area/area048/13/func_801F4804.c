#include "area048_13.h"

MATCH void func_801F4804(void) {
    ((Actor*)g_CurrentActor)->interaction_flags &= 0xFE;
    if (g_CharSlot[D_80145F09] == 1) {
        SYS_ToggleFlag(g_SceneEventFlags, 0xD);
    }
}
