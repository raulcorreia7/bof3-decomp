#include "start_08.h"

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 70.90%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawCharacterWindow(u16 x, u16 y, u8 character_index, u8 shaded, s32 unused) {
    s16        val0;
    s16        val1;
    s16        val2;
    s32        tmp0;
    s32        val3;
    s32        val4;
    s32        val5;
    s32        val6;
    s32        val7;
    u16        tmp1;
    u16        tmp2;
    u16        tmp3;
    u16        val8;
    u32        val9;
    u8*        val10;
    u8         val11;
    Character* character;

    val5 = x;
    val1 = y;
    val4 = shaded;
    val6 = val4 & BYTE_MASK;
    val9 = -(val6 != 0) & 7;
    UI_DrawWindow((val5 + 3) & HALF_MASK, (val1 + 3) & HALF_MASK, MENU_CHARACTER_WINDOW_WIDTH,
                  MENU_CHARACTER_WINDOW_HEIGHT, val6, CHARACTER_BLOCK->window_style);
    val7 = val5;
    val2 = val1;
    val5 += 0x56;
    tmp1 = val5 & HALF_MASK;
    val1 += 2;
    character = &g_Characters[character_index];
    if (val6 == 0) {
        val11 = (character->status >> 6) & 2;
    } else {
        val11 = 1;
    }
    val5 = val9 & BYTE_MASK;
    Menu_DrawCharacterPortrait(tmp1, val1 & HALF_MASK, character->character_id, val11);
    UI_DrawText((s16)(val7 + 20), (s16)(val2 + 3), val5, 5U, (u8*)character);
    val10 = g_UiFormatBuffer;
    val10 = g_UiFormatBuffer;
    TEXT_Format(g_UiFormatBuffer, g_MenuStatFormat, character->level);
    val1 = val2 + 0x17;
    UI_DrawGlyphString((s16)(val7 + 22), val1, (u32)val5, g_UiFormatBuffer);
    if ((character->status & (STATUS_CONFUSED | STATUS_POISONED)) == (STATUS_CONFUSED | STATUS_POISONED)) {
        val3 = 1;
        if (g_FrameCount & 0x20) {
            val0 = val7 + 0x2E;
            if (val5 != 0) {
                val3 = val5;
            }
        } else {
            goto block_13; /* retail branch */
        }
        goto block_16; /* retail branch */
    }
    tmp2 = character->status;
    val3 = 1;
    if (tmp2 & STATUS_POISONED) {
        val0 = val7 + 0x2E;
        if (val5 != 0) {
            val3 = val5;
        }
        goto block_16; /* retail branch */
    }
    if (tmp2 & STATUS_CONFUSED) {
    block_13:
        val3 = 1;
        val0 = val7 + 0x2E;
        if (val5 != 0) {
            val3 = val5;
        }
    block_16:
        UI_DrawTextString(val0, val1, val3, 0x10, D_801EC938);
    }
    if (character->hp < (u32)(character->stats.max_hp >> 2)) {
        val8 = character->status | STATUS_LOW_HP;
    } else {
        val8 = character->status & ~STATUS_LOW_HP;
    }
    character->status = val8;
    if (!(val4 & BYTE_MASK)) {
        if (character->status & STATUS_LOW_HP) {
            val9 = 4;
        }
        if (character->hp < 2U) {
            val9 = 2;
        }
    } else {
        val9 = 7;
    }
    val10 = g_UiFormatBuffer;
    val10 = g_UiFormatBuffer;
    TEXT_Format(g_UiFormatBuffer, g_MenuCurrentValueFormat, character->hp);
    UI_DrawGlyphString((s16)(val7 + 22), (s16)(val2 + 31), val9, g_UiFormatBuffer);
    if (!(val4 & BYTE_MASK)) {
        val9 = (character->fatigue != 0) * 4;
    } else {
        val9 = 7;
    }
    val10 = g_UiFormatBuffer;
    val10 = g_UiFormatBuffer;
    TEXT_Format(g_UiFormatBuffer, g_MenuMaxValueFormat, character->stats.max_hp);
    UI_DrawGlyphString((s16)(val7 + 22), (s16)(val2 + 31), val9, g_UiFormatBuffer);
    tmp0 = val4 & BYTE_MASK;
    val9 = -(tmp0 != 0) & 7;
    if (tmp0 == 0) {
        tmp3 = character->ap;
        if (tmp3 < (u32)(character->stats.max_ap >> 2)) {
            val9 = 4;
        }
        if (tmp3 == 0) {
            val9 = 2;
        }
    } else {
        val9 = 7;
    }
    val1 = (s16)g_UiFormatBuffer;
    val1 = (s16)g_UiFormatBuffer;
    TEXT_Format(val1, g_MenuCurrentValueFormat, character->ap);
    val5 = val7 + 0x16;
    val5 <<= 0x10;
    val5  = val5 >> 0x10;
    val10 = val2 + 0x27;
    val10 = (u8*)((s32)val10 << 0x10);
    val10 = (u8*)((s32)val10 >> 0x10);
    UI_DrawGlyphString((s16)val5, (s16)val10, val9, (u8*)val1);
    val9 = -((val4 & BYTE_MASK) != 0) & 7;
    TEXT_Format(val1, g_MenuMaxValueFormat, character->stats.max_ap);
    UI_DrawGlyphString((s16)val5, (s16)val10, val9, (u8*)val1);
    UI_DrawSpriteRun((s16)val7, val2, &D_801EC598, 0);
    Menu_DrawExperienceLine((val7 + 0x14) & HALF_MASK, (val2 + 0x12) & HALF_MASK, character_index, character->level,
                            character->exp);
}
#else
/* blocker: register homes (py in s2, shaded byte in s3). */
INCLUDE_ASM(Menu_DrawCharacterWindow);
#endif
