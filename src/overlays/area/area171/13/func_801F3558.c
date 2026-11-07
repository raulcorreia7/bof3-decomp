#include "area171_13.h"

MATCH void func_801F3558(void) {
    u8* state;

    g_CurrentActor->interaction_flags &= 0xFE;

    if (g_BattlePartyBattlers[0].chr.character_id == 5) {
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

    if (g_BattlePartyBattlers[0].chr.character_id == 7) {
        Game_SetScriptActive();
        g_SceneEventMode = 0x30;
        g_SceneEventStep = 0xA;
    }
}
