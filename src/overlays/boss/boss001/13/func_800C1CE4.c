#include "boss001_13.h"

MATCH void func_800C1CE4(void) {
    PartyMember* work;

    Battle_RequestEnemyScript(4);
    work       = SELF(PartyMember);
    D_801463BE = 0x3C;
    work->header.step++;
}
