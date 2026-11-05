#include "start_08.h"

MATCH s32 func_801D70EC(void) {
    s32 record;

    record     = g_CharSlot[D_80144F5A[D_80148510]];
    D_801ED63C = g_Characters[record].equipment.weapon;
    D_801ED63D = g_Characters[record].equipment.shield;
    D_801ED63E = g_Characters[record].equipment.helmet;
    D_801ED63F = g_Characters[record].equipment.armor;
    D_801ED640 = g_Characters[record].equipment.accessories[0];
    D_801ED641 = g_Characters[record].equipment.accessories[1];
    if ((&D_801ED63C)[D_8014850E] != 0) {
        (&D_801ED63C)[D_8014850E] = 0;
        D_80148511                = 0;
        return 1;
    }
    D_80148511 = 1;
    return 0;
}
