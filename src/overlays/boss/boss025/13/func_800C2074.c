#include "boss025_13.h"

MATCH void func_800C2074(void) {
    Script_Request(0xD);
    SELF(PartyMember)->unk_2A = 0;
    Script_AnimStepOnce();
    Battle_DefeatEnemy();
    SELF(PartyMember)->header.flags &= ~ACTOR_FLAG_HIDDEN;
    SELF(PartyMember)->header.mode = 3;
    SELF(PartyMember)->header.step = 0;
    SELF(PartyMember)->unk_03      = 0;
}
