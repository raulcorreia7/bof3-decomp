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

#ifdef NON_MATCHING
NON_MATCHING void func_801D1048(s16 x, s16 y, u8 count) {
    s16 row_y;
    s32 i;

    UI_DrawText((s16)(x + 40), (s16)y, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 55));
    row_y = (s16)(y + 20);
    func_801D0F50((s16)(x + 8), row_y, 1);
    UI_DrawText((s16)(x + 24), row_y, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 56));
    sprintf(g_UiFormatBuffer, D_801D0C0C, D_80145E44);
    UI_DrawAsciiString((s16)(x + 108), row_y, 0, g_UiFormatBuffer);
    UI_DrawText((s16)(x + 132), row_y, 0, 7, D_80145E44 == 1 ? D_801D1964 : D_801D195C);
    for (i = 0; i < 7; i++) {
        if (i + count * 7 >= D_80145E44) {
            break;
        }
        UI_DrawText((s16)(x + 20), (s16)(y + i * 16 + 44), 0, 5, D_801457E8 + (D_80145E30[i + count * 7] & 0x7F) * 5);
        UI_DrawText((s16)(x + 72), (s16)(y + i * 16 + 44), 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, (D_80145E30[i + count * 7] & 0x80) ? 58 : 57));
    }
}
#else
INCLUDE_ASM(func_801D1048);
#endif

INCLUDE_ASM(func_801D129C);

INCLUDE_ASM(func_801D14C8);

INCLUDE_ASM(func_801D1670);

INCLUDE_ASM(func_801D1724);
