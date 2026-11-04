#include "boss018_16.h"

MATCH void Boss_EndBattle(void) {
    u8* row;

    row = D_801EB6B2;
    if ((*(u16*)row & 0x4000) == 0) {
        func_800AC870(0, (PartyBattler*)(row - 0x82), 1);
        func_800AC844(0);
    }
    func_800AC870(3, (PartyBattler*)(row + 0x96), 0);
    func_800AC844(3);
    func_800AC870(4, (PartyBattler*)(row + 0x1AE), 0);
    func_800AC844(4);
}
