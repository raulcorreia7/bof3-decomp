#include "boss021_16.h"

MATCH void Boss_EndBattle(void) {
    u8* work;

    Battle_ShowActorEntry(0);
    work = (u8*)func_800AC754(0);
    SELF_SET(work);
    work[0x2A] = 0;
    Script_Select(4);
    func_800AC934(1);
    func_800AC934(2);
}
