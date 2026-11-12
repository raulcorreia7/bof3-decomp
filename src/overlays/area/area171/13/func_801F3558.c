#include "area171_13.h"

MATCH void func_801F3558(void) {
    u8* state;

    g_CurrentActor->interaction_flags &= 0xFE;

    if (g_Game.members[0].chr.character_id == CHAR_ID_MOMO) {
        state = &D_80144CAA;
        if (*state != 0x4B) {
            return;
        }
        SYS_SetFlag(state + 0x27E, 115);
        func_801A4BC0(2, 33, 0xC0);
        func_801A4BC0(2, 34, 0xC0);
        func_801A4BC0(3, 33, 0);
        func_801A4BC0(3, 34, 0);
        g_CurrentActor->unk_7E += 1;
    }

    if (g_Game.members[0].chr.character_id == CHAR_ID_RYU_ADULT) {
        Scene_StartEvent(0x30, 0xA);
    }
}
