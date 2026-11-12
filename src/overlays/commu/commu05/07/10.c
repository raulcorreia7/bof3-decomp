#include "commu05_07.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The overlay entry: the commu state byte selects the step handler. */
MATCH void func_801D0C10(void) {
    SYS_DISPATCH_BYTE(g_Commu05States, D_801F294C);
}

MATCH void func_801D0C4C(void) {
    if (D_80145E44 != 0) {
        D_801D19F0.unk_00 = ((D_80145E44 - 1) / 7) + 1;
    } else {
        D_801D19F0.unk_00 = 0;
    }
    if (g_FairyVillagePendingQueueCount != 0) {
        D_801D19F0.unk_01 = ((g_FairyVillagePendingQueueCount - 1) / 20) + 1;
    } else {
        D_801D19F0.unk_01 = 0;
    }
    if (g_FairyVillageUpdateCount != 0) {
        D_801D19F0.unk_02 = ((g_FairyVillageUpdateCount - 1) / 8) + 1;
    } else {
        D_801D19F0.unk_02 = 0;
    }
    D_801D19F0.unk_04 = 0;
    D_801F294C += 1;
}

INCLUDE_ASM(func_801D0D4C);

MATCH void func_801D0F34(void) {
    /* FAKE: retail reads g_SceneEventStep as u8[]. */
    ((u8*)&g_SceneEventStep)[0] += 1;
}

INCLUDE_ASM(func_801D0F50);

INCLUDE_ASM(func_801D1048);

INCLUDE_ASM(func_801D129C);

INCLUDE_ASM(func_801D14C8);

INCLUDE_ASM(func_801D1670);

INCLUDE_ASM(func_801D1724);
