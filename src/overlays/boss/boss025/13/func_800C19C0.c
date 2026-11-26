#include "boss025_13.h"

MATCH void func_800C19C0(void) {
    Script_Request(0xFU);
    SELF(PartyMember)->unk_2A = 0;
    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF(PartyMember)->header.mode = 3;
    SELF(PartyMember)->header.step = 0;
    SELF(PartyMember)->unk_03      = 0;
    if (g_Battle.encounter == 0x19) {
        g_UiPanelMode = 2;
        UI_MessageStartArea(MSG_BOSS025_032);
    }
}
