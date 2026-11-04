#include "magic216_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

INCLUDE_ASM(func_801EEC70);

INCLUDE_ASM(func_801EECDC);

INCLUDE_ASM(func_801EEF58);

MATCH void func_801EEF98(s32 index, s32 category) {
    switch (category & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            SYS_CopyString(g_TextVariables, g_Items[index & BYTE_MASK].name, 0xC);
            break;
        case ITEM_CAT_WEAPON:
            SYS_CopyString(g_TextVariables, g_Weapons[index & BYTE_MASK].name, 0xC);
            break;
        case ITEM_CAT_ARMOR:
            SYS_CopyString(g_TextVariables, g_Armors[index & BYTE_MASK].name, 0xC);
            break;
        case ITEM_CAT_ACCESSORY:
            SYS_CopyString(g_TextVariables, g_Accessories[index & BYTE_MASK].name, 0xC);
            break;
    }
}
