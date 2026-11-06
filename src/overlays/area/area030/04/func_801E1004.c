#include "area030_04.h"

/* Draws the item name, count and label in one column. */
MATCH void func_801E1004(s32 item, s32 count, s32 column) {
    FishingAnchors anchors;
    s32            i;
    u8*            dst;
    u8*            src;

    anchors = D_801D0C30;
    func_801E0C80(0, 1);
    for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
        s32 x;
        s32 y;
        if (i == 0) {
            x = (u8)anchors.anchor[0].x;
            y = (u8)anchors.anchor[0].y - ((column & BYTE_MASK) * 20);
        } else if (i == 1) {
            x = (u8)anchors.anchor[1].x - ((column & BYTE_MASK) * 25);
            y = (u8)anchors.anchor[1].y;
        } else {
            const u8* pair = (const u8*)&anchors + (i << 1);
            x              = pair[0] + ((column & BYTE_MASK) * 25);
            y              = pair[1];
        }
        func_801E0DCC((i + 3) & BYTE_MASK, 1, x, y);
    }

    dst = g_UiFormatBuffer;
    if ((item & BYTE_MASK) == 0x16) {
        for (i = 0; i < 12; i++) {
            *dst++ = D_801E28C4[i];
        }
    } else if ((item & BYTE_MASK) == GAME_NONE) {
        for (i = 0; i < 12; i++) {
            *dst++ = D_801E28D0[i];
        }
    } else {
        i   = 0;
        src = (u8*)g_Items + (((item & BYTE_MASK) + 0x38) * 18);
        while (i < 12) {
            *dst = *src;
            if (*src == 0) {
                i++;
                break;
            }
            i++;
            dst++;
            src++;
        }
    }
    *dst = 0;
    UI_DrawText(0x70, 0x45 - ((u8)column * 20), 0, 0xF, g_UiFormatBuffer);

    if ((item & BYTE_MASK) != GAME_NONE) {
        sprintf((char*)g_UiFormatBuffer, D_801D0C38, count & BYTE_MASK);
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            if (g_UiFormatBuffer[i] == ' ') {
                g_UiFormatBuffer[i] = STRING_SPACE;
            }
        }
        UI_DrawText(0x2F - ((u8)column * 25), 0x73, 0, 3, g_UiFormatBuffer);
        sprintf((char*)g_UiFormatBuffer, D_801D0C38, func_801E0ABC(item & BYTE_MASK, count & BYTE_MASK) & HALF_MASK);
        for (i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++) {
            if (g_UiFormatBuffer[i] == ' ') {
                g_UiFormatBuffer[i] = STRING_SPACE;
            }
        }
        UI_DrawText(((u8)column * 25) + 0xEF, 0x73, 0, 3, g_UiFormatBuffer);
    }
}
