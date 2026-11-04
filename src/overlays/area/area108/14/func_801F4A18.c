#include "area108_14.h"

MATCH void func_801F4A18(void) {
    if (SYS_TestFlag(g_SceneEventFlags, 0x1E)) {
        g_CurrentActor->unk_77 = 0x12;
    } else if (SYS_TestFlag(g_SceneEventFlags, 0x1F)) {
        g_CurrentActor->unk_77 = 0x11;
    }
    g_CurrentActor->unk_7E = 0xFFFE;
}
