#include "start_08.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 76.42%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawEquipStatWindow(s16 x, s16 y, s32 character_slot, s32 equip_slot, u8 item_id) {
    u8          stack_18[4];
    u16         stack_20[4];
    u8          stack_28;
    s16         tmp0;
    s16         tmp1;
    s16         tmp2;
    u16         copy_word;
    u8          copy_byte;
    s16         val0;
    s16         val1;
    s32         val2;
    s32         val3;
    s32         val4;
    s32         val5;
    u8*         val6;
    s32         val7;
    u32         tmp3;
    u8          val8;
    s32         val9;
    s32         val10;
    u8          val11;
    u8*         val12;
    Character*  character;
    u8*         byte_buffer;
    const char* format;

    val1      = x;
    val0      = y;
    val9      = character_slot;
    val5      = equip_slot;
    val4      = 0;
    character = &g_Characters[val9 & BYTE_MASK];
    tmp3      = val5 & BYTE_MASK;
    val11     = item_id;
    switch (tmp3) {
        default:
            val8 = 0;
            break;
        case 1:
            val8 = 1;
            break;
        case 2:
        case 3:
        case 4:
            val8 = 2;
            break;
        case 5:
        case 10:
        case 11:
            val8 = 3;
            break;
    }
    val10    = val9 & BYTE_MASK;
    stack_28 = (((s32)(Item_GetEquipability(val8, val11) & BYTE_MASK) >> val10) ^ 1) & 1;
    val9     = stack_28;
    UI_DrawWindow((val1 + 3) & HALF_MASK, (val0 + 3) & HALF_MASK, 108, 48, (s32)val9, CHARACTER_BLOCK->window_style);
    if (val9 == 0) {
        func_80164D2C(val10, (val5 - 1) & BYTE_MASK, val11, &stack_18[0], &stack_20[0]);
        val10       = 0;
        val6        = g_UiFormatBuffer;
        byte_buffer = stack_18;
        tmp2        = val1 + 0x2C;
        copy_word   = stack_20[3];
        copy_byte   = stack_18[3];
        val7        = tmp2 << 0x10;
        stack_20[2] = copy_word;
        stack_18[2] = copy_byte;
        do {
            val9 = val10 & BYTE_MASK;
            val10 += 1;
            sprintf((char*)val6, g_MenuStatFormat, stack_20[val9]);
            tmp0 = val0 + (val9 * 0xF) + 8;
            UI_DrawGlyphString(val7 >> 16, tmp0, byte_buffer[val9], val6);
        } while ((u32)(val10 & BYTE_MASK) < 3U);
        val2 = val1 + 0x46;
    } else {
        val4   = 7;
        val12  = g_UiFormatBuffer;
        format = g_MenuStatFormat;
        sprintf((char*)val12, format, character->power);
        tmp2 = val1 + 0x2C;
        UI_DrawGlyphString(tmp2, (s16)(val0 + 8), 7U, val12);
        sprintf((char*)val12, format, character->defense);
        UI_DrawGlyphString(tmp2, (s16)(val0 + 23), 7U, val12);
        sprintf((char*)val12, format, character->agility);
        UI_DrawGlyphString(tmp2, (s16)(val0 + 38), 7U, val12);
        val2 = val1 + 0x46;
    }
    val10 = 0;
    Menu_DrawCharacterPortrait(val2 & HALF_MASK, (val0 + 2) & HALF_MASK, character->character_id, stack_28);
    tmp1 = val1 + 5;
    val9 = tmp1 << 0x10;
    val3 = 0 & BYTE_MASK;
    do {
        UI_DrawText(tmp1, (s16)(val0 + (val3 * 15) + 6), val4 & BYTE_MASK, 0xFFU, (D_801ECB2C + (val3 * 6)));
        val10 += 1;
        val3 = val10 & BYTE_MASK;
    } while ((u32)(val10 & BYTE_MASK) < 3U);
    UI_DrawSpriteRun(val1, val0, D_801EC7F8, 0);
}
#else
/* Same body in the shop, start, Bate and Shisu overlays; the shop draft differs from retail in frame size (0x58 against 0x50) and save order, and the retail parameter locals sit in s6, s3, s0 and s4. */
INCLUDE_ASM(Menu_DrawEquipStatWindow);
#endif
