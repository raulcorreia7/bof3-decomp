#include "start_08.h"

/* Text label the item row draws. */

/* nonmatching 60.11%: the panel's item table is the typed member now; the unit still needs a lever that closes the
 * first mismatch. resume: the record's layout is proven, so the remaining diff is code shape. */
#ifdef NON_MATCHING
NON_MATCHING void func_801EAA14(MenuPanelTask* task) {
    MenuPanelTask* stack_18;
    u8*            stack_20;
    u8             stack_28;
    s32            stack_30;
    s32            stack_38;
    s32            stack_40;
    s16            tmp0;
    s16            val0;
    s32            val1;
    s32            val2;
    s32            val3;
    s32            val4;
    s32            val5;
    u16            tmp1;
    u16            tmp2;
    u16            tmp3;
    u16            val6;
    u32            val7;
    u8*            val8;
    u8             val9;
    u8             val10;
    void*          val11;

    stack_18 = task;
    stack_28 = 0;
    Menu_DrawWindowFrame((s16)task->x, (s16)stack_18->y, 0x12, 0x15);
    tmp1     = stack_18->x;
    stack_20 = (u8*)stack_18->item_table;
    val5     = tmp1 + 7;
    val4     = stack_18->y + 6;
    if (stack_18->unk_0A != 0) {
        val8     = g_UiFormatBuffer;
        val8     = g_UiFormatBuffer;
        stack_30 = (tmp1 + 0x5D) & HALF_MASK;
        val0     = tmp1 + 0x37;
        tmp0     = tmp1 + 0x1F;
        stack_38 = tmp0 << 0x10;
        stack_40 = (s32)tmp0;
        do {
            val11 = &g_Characters[g_CharSlot[*stack_20]];
            val10 = 1;
            if (FIELD(u8, val11, 0x7u) & 2) {
                val7 = 7;
            } else {
                val10 = 0;
                val7  = 0;
            }
            val6 = val4 & HALF_MASK;
            UI_DrawWindow(val5 & HALF_MASK, val6, 125, 48, (val10 + 0x80) & BYTE_MASK, (s32)D_80144952);
            if (!(val10 & BYTE_MASK)) {
                val9 = (FIELD(u16, val11, 0xCu) >> 6) & 2;
            } else {
                val9 = 1;
            }
            val3 = val7 & BYTE_MASK;
            Menu_DrawCharacterPortrait((u16)stack_30, val6, FIELD(u8, val11, 0x5u), val9);
            UI_DrawText((s16)(val5 + 20), (s16)(val4 + 1), val3, 5U, val11);
            val6 = val4 + 0x15;
            Menu_DrawIcon((val5 + 2) & HALF_MASK, val6 & HALF_MASK, 3U, val10);
            sprintf((s8*)g_UiFormatBuffer, &D_801D0F18, FIELD(u8, val11, 0x6u));
            val6 <<= 0x10;
            val6 = (u16)((s32)val6 >> 0x10);
            UI_DrawGlyphString((s16)(stack_38 >> 16), (s16)val6, (u32)val3, g_UiFormatBuffer);
            if ((FIELD(u16, val11, 0xCu) & (STATUS_CONFUSED | STATUS_POISONED)) ==
                (STATUS_CONFUSED | STATUS_POISONED)) {
                if (g_FrameCount & 0x20) {
                    val2 = 1;
                    if (val3 != 0) {
                        val2 = val3;
                    }
                } else {
                    goto block_18; /* retail branch */
                }
                goto block_21; /* retail branch */
            }
            tmp2 = FIELD(u16, val11, 0xCu);
            if (tmp2 & STATUS_POISONED) {
                val2 = 1;
                if (val3 != 0) {
                    val2 = val3;
                }
                goto block_21; /* retail branch */
            }
            val1 = val5 + 2;
            if (tmp2 & 0x20) {
            block_18:
                val2 = 1;
                if (val3 != 0) {
                    val2 = val3;
                }
            block_21:
                UI_DrawTextString(val0, val6, val2, 0x10, D_801ED5DC);
                val1 = val5 + 2;
            }
            val6 = val10 & BYTE_MASK;
            Menu_DrawIcon(val1 & HALF_MASK, (val4 + 0x1D) & HALF_MASK, 0U, (u8)val6);
            if (val6 == 0) {
                if (FIELD(u16, val11, 0xCu) & 0x2000) {
                    val7 = 4;
                }
                if (FIELD(u16, val11, 0x14u) < 2U) {
                    val7 = 2;
                }
            } else {
                val7 = 7;
            }
            sprintf((s8*)g_UiFormatBuffer, &D_801D0F1C, FIELD(u16, val11, 0x14u));
            UI_DrawGlyphString((s16)(stack_38 >> 16), (s16)(val4 + 29), val7, g_UiFormatBuffer);
            if (!(val10 & BYTE_MASK)) {
                val7 = (FIELD(u8, val11, 0x1Au) != 0) * 4;
            } else {
                val7 = 7;
            }
            sprintf((s8*)g_UiFormatBuffer, &D_801D0F24, FIELD(u16, val11, 0x1Cu));
            UI_DrawGlyphString((s16)(stack_38 >> 16), (s16)(val4 + 29), val7, g_UiFormatBuffer);
            val6 = val10 & BYTE_MASK;
            Menu_DrawIcon((val5 + 2) & HALF_MASK, (val4 + 0x25) & HALF_MASK, 1U, (u8)val6);
            val7 = -(s32)val6 & 7;
            if (val6 == 0) {
                tmp3 = FIELD(u16, val11, 0x16u);
                if ((u32)(FIELD(u16, val11, 0x1Eu) >> 2) >= tmp3) {
                    val7 = 4;
                }
                if (tmp3 == 0) {
                    val7 = 2;
                }
            } else {
                val7 = 7;
            }
            stack_20 += 1;
            stack_28 += 1;
            sprintf((s8*)g_UiFormatBuffer, &D_801D0F1C, FIELD(u16, val11, 0x16u));
            val6 = val4 + 0x25;
            val6 <<= 0x10;
            val6 = (u16)((s32)val6 >> 0x10);
            UI_DrawGlyphString((s16)stack_40, (s16)val6, val7, g_UiFormatBuffer);
            val7 = -(s32)val10 & 7;
            sprintf((s8*)g_UiFormatBuffer, &D_801D0F24, FIELD(u16, val11, 0x1Eu));
            UI_DrawGlyphString((s16)stack_40, (s16)val6, val7, g_UiFormatBuffer);
            val4 += 0x34;
        } while (stack_28 < (u8)stack_18->unk_0A);
    }
}
#else
INCLUDE_ASM(func_801EAA14);
#endif
