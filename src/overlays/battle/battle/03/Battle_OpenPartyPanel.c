#include "battle_03.h"

/* func_801D9304 */
MATCH void Battle_OpenPartyPanel(u8 index) {
    u8 count;

    Menu_OpenPanelTask(1, 3);
    count      = g_Battle.party_count;
    D_80148356 = 0;
    D_80148357 = index;
    D_8014835E = count;
    D_80148358 = D_801EAF27[count & BYTE_MASK];
    D_8014835A = 0xF0;
    D_8014835C = 0;
    D_8014835D = 0;
}
