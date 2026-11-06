#include "sisyou_00.h"

MATCH void func_801D39CC(u32 entry) {
    s32 i;
    u8* name;

    i    = 0;
    name = g_SaveData.characters[entry & BYTE_MASK].name;
    do {
        g_TextVariables[0][i] = name[i];
        i += 1;
    } while (i < 5);
    D_801490DD = 0;
}
