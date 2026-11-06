#include "battle_03.h"

MATCH void func_801D9304(u8 arg0) {
    u8 count;

    Menu_ArmPanelTask(1, 3);
    count      = g_BattlePartyCount;
    D_80148356 = 0;
    D_80148357 = arg0;
    D_8014835E = count;
    D_80148358 = D_801EAF27[count & 0xFF];
    D_8014835A = 0xF0;
    D_8014835C = 0;
    D_8014835D = 0;
}
