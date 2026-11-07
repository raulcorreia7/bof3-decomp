#include "area171_13.h"

MATCH void func_801F3558(void) {
    u8* state;

    g_CurrentActor->interaction_flags &= 0xFE;

    if (D_80145F09[0][0] == 5) {
        state = &D_80144CAA;
        if (*state != 0x4B) {
            return;
        }
        SYS_SetFlag(state + 0x27E, 0x73);
        func_801A4BC0(2, 0x21, 0xC0);
        func_801A4BC0(2, 0x22, 0xC0);
        func_801A4BC0(3, 0x21, 0);
        func_801A4BC0(3, 0x22, 0);
        g_CurrentActor->unk_7E += 1;
    }

    if (D_80145F09[0][0] == 7) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x30;
        g_SceneEventStep = 0xA;
    }
}
