#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EAF98(MenuPanelTask* task) {
    u8             stack_20;
    u8             stack_21;
    MenuPanelTask* val0;
    s16            tmp0;
    s16            val1;
    s16            val2;
    s32            tmp1;
    s32            tmp2;
    s32            tmp3;
    s32            tmp4;
    s32            tmp5;
    s32            val3;
    s32            val4;
    s32            val5;
    s32            val6;
    u32            val7;
    u8*            flags;
    s32*           level;

    val0 = task;
    val3 = 0;
    val4 = 0;
    do {
        tmp5 = val3;
        if (D_80145548 & (1 << val4)) {
            val3 += 1;
            *(&D_801ED878 + (tmp5 & BYTE_MASK)) = val4 + 1;
        }
        val4 += 1;
        val7 = val3 & BYTE_MASK;
    } while ((u32)(val4 & BYTE_MASK) < 0x12U);
loop_6:
    val3 += 1;
    if (val7 < 0x12U) {
        *(&D_801ED878 + val7) = 0;
        val7                  = val3 & BYTE_MASK;
        goto loop_6; /* retail branch */
    }
    UI_DrawWindow((val0->pos.x + 3) & HALF_MASK, (val0->pos.y + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_WINDOW_HEIGHT, 0, (s32)g_WindowStyle);
    val4 = func_801AFD10(&val0->unk_0A, &stack_20, &stack_21, &val0->unk_08);
    val5 = val4 & BYTE_MASK;
    val1 = (s8)stack_20 + (val0->pos.y + 0x1A);
    if (val5 < (val5 + (stack_21 + 9))) {
        val6 = val5;
    loop_9:
        if (*(&D_801ED878 + val5) != 0) {
            val2 = val1 + 2;
            if (val0->unk_0B == val5) {
                func_801AEA80((val0->pos.x + 7) & HALF_MASK, (val1 + 2) & HALF_MASK, 6, 1);
                tmp0 = val1;
                val1 -= 2;
                UI_DrawText((s16)(val0->pos.x + 17), tmp0, 7, 0xFFU, Message_GetText(*(&D_801ED878 + val5) + 0x4171));
                val2 = val1 + 2;
            }
            func_801AEA80((val0->pos.x + 7) & HALF_MASK, val2 & HALF_MASK, 6, 0);
            UI_DrawText((s16)(val0->pos.x + 17), val1, 0, 0xFFU, Message_GetText(*(&D_801ED878 + val5) + 0x4171));
            if (val0->unk_0B == val5) {
                val1 = val2;
            }
            val4 += 1;
            val5 = val4 & BYTE_MASK;
            val1 += 0xD;
            if (val5 >= (val6 + (stack_21 + 9))) {
            } else {
                goto loop_9; /* retail branch */
            }
        }
    }
    val4         = 0;
    flags        = &g_WindowStyle;
    val0->unk_0C = *(&D_801ED878 + val0->unk_0B);
    UI_DrawWindow((val0->pos.x + 3) & HALF_MASK, (val0->pos.y + 3) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_TOP_HEIGHT, 0, (s32)*flags);
    UI_DrawWindow((val0->pos.x + 3) & HALF_MASK, (val0->pos.y + 146) & HALF_MASK, MENU_INVENTORY_WINDOW_WIDTH, MENU_INVENTORY_BOTTOM_HEIGHT, 0, (s32)*flags);
    level = &D_801ED608;
    UI_DrawText((s16)(val0->pos.x - (((Game_ReadCommand(level) & BYTE_MASK) * 4) - 78)), (s16)(val0->pos.y + 7), 0, 0x10U, level);
    UI_DrawSpriteRun((s16)val0->pos.x, (s16)val0->pos.y, &D_801ED5F0, 1);
    UI_DrawSpriteRun((s16)val0->pos.x, (s16)val0->pos.y, &D_801ED5FC, 1);
    do {
        tmp1 = val4 & BYTE_MASK;
        val4 += 1;
        UI_DrawSprite((s16)(val0->pos.x + ((tmp1 + 5) * 8)), (s16)val0->pos.y, 1, 1);
    } while ((u32)(val4 & BYTE_MASK) < 0xAU);
    val4 = 0;
    do {
        tmp2 = val4 & BYTE_MASK;
        val4 += 1;
        UI_DrawSprite((s16)val0->pos.x, (s16)(val0->pos.y + ((tmp2 + 3) * 8)), 4, 1);
    } while ((u32)(val4 & BYTE_MASK) < 0xFU);
    val4 = 0;
    UI_DrawSprite((s16)(val0->pos.x + 144), (s16)(val0->pos.y + 24), 0x16, 1);
    do {
        tmp3 = val4 & BYTE_MASK;
        val4 += 1;
        UI_DrawSprite((s16)(val0->pos.x + 144), (s16)(val0->pos.y + ((tmp3 + 5) * 8)), 0x17, 1);
    } while ((u32)(val4 & BYTE_MASK) < 0xCU);
    val4 = 0;
    UI_DrawSprite((s16)(val0->pos.x + 144), (s16)(val0->pos.y + 136), 0x18, 1);
    UI_DrawSprite((s16)val0->pos.x, (s16)(val0->pos.y + 144), 0x19, 1);
    do {
        tmp4 = val4 & BYTE_MASK;
        val4 += 1;
        UI_DrawSprite((s16)(val0->pos.x + ((tmp4 + 1) * 8)), (s16)(val0->pos.y + 144), 0x1A, 1);
    } while ((u32)(val4 & BYTE_MASK) < 0x11U);
    UI_DrawSprite((s16)(val0->pos.x + 8), (s16)val0->pos.y, 0x32, 1);
    UI_DrawSprite((s16)(val0->pos.x + 144), (s16)val0->pos.y, 0x33, 1);
    func_801AFA1C(&D_801ED878, val0->unk_0A, (s16)(val0->pos.x + 0x90), (s16)(val0->pos.y + 0x18), 9, 0x12, 0x74);
}
#else
INCLUDE_ASM(func_801EAF98);
#endif
