#include "boss004_13.h"

MATCH void func_800C1A04(void) {
    Battle_RequestEnemyScript(4);
    SELF(PartyMember)->unk_09 = 60;
    SELF(PartyMember)->header.step++;
}
