#include "boss025_13.h"

MATCH void func_800C1CB0(void) {
    Script_Request(0xF);
    TASK(PartyMember)->unk_2A = 0;
    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    TASK(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    TASK(PartyMember)->header.mode = 3;
    TASK(PartyMember)->header.step = 0;
    TASK(PartyMember)->unk_03      = 0;
}
