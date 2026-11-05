#include "commu05_07.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The overlay entry: the commu state byte selects the step handler. */
MATCH void func_801D0C10(void) {
    SYS_DISPATCH_BYTE(D_801D1950, D_801F294C);
}

extern u8 D_80145E44;

typedef struct {
    s8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s8 unk_04;
} Commu05State;

extern Commu05State D_801D19F0;

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
    /* FAKE: retail reads D_801448EC as u8[]. */
    ((u8*)&D_801448EC)[0] += 1;
}

INCLUDE_ASM(func_801D0F50);

INCLUDE_ASM(func_801D1048);

INCLUDE_ASM(func_801D129C);

INCLUDE_ASM(func_801D14C8);

INCLUDE_ASM(func_801D1670);

INCLUDE_ASM(func_801D1724);
