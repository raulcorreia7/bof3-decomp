#include "area030_04.h"

/* Draws the accessory panel for one actor row. */
/* nonmatching unmeasured: the retail frame is 0x48 and the candidate 0x40, so the eight unused frame bytes are
 * declared; candidate 60.27%. resume: a source shape that reproduces the retail's cell, row and enemy-row address
 * forms. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D88E0(s16 x, s16 y) {
    /* FAKE: unused frame, 8 bytes. */
    FAKE_STACK_PADS(u8, 8);
    s16  last_y;
    s16  panel_x;
    s16  panel_y;
    s16  x0;
    s16  y0;
    s32  last_x;
    s32  last_palette;
    s32  icon_y;
    s32* accessory;
    s32  icon_x;
    u16  record_word;
    u8*  slot_x;
    u8*  accessory_name;
    u8   accessory_flags;

    panel_x = x;
    panel_y = y;
    func_801D8D70((u16)panel_x, (u16)panel_y);
    UI_DrawText((s16)(panel_x + 51), (s16)(panel_y + 7), 0, 5U, (&D_801E21D4));
    x0              = panel_x;
    accessory_flags = g_Task->option_flags;
    y0              = panel_y;
    if (accessory_flags & 0x80) {
        icon_x = panel_x + 16;
        icon_x <<= 0x10;
        icon_x = icon_x >> 0x10;
        slot_x = &g_FishingRod;
        slot_x = &g_FishingRod;
        func_800F7094(icon_x, (s16)(panel_y + 28), g_FishingRod, 3, 0);
        icon_y = panel_x + 28;
        icon_y <<= 0x10;
        icon_y = icon_y >> 0x10;
        slot_x = g_Accessories->header.name;
        slot_x = g_Accessories->header.name;
        UI_DrawText((s16)icon_y, (s16)(panel_y + 26), 0, 0xCU, ((g_FishingRod * 0x14) + slot_x));
        func_800F7094(icon_x, (s16)(panel_y + 44), g_FishingLure, 3, 0);
        last_x       = icon_y;
        last_y       = panel_y + 42;
        last_palette = 0;
    } else {
        slot_x = panel_x + 16;
        if (!(accessory_flags & 1)) {
            slot_x         = (u8*)((s32)slot_x << 0x10);
            slot_x         = (u8*)((s32)slot_x >> 0x10);
            accessory_name = &g_FishingRod;
            accessory_name = &g_FishingRod;
            func_800F7094((s32)slot_x, (s16)(panel_y + 28), g_FishingRod, 3, 1);
            icon_x = panel_x + 28;
            icon_x <<= 0x10;
            icon_x = icon_x >> 0x10;
            icon_y = panel_y + 26;
            icon_y <<= 0x10;
            icon_y  = icon_y >> 0x10;
            panel_x = (s16)g_Accessories;
            panel_x = (s16)g_Accessories;
            UI_DrawText((s16)icon_x, (s16)icon_y, 7, 0xCU, (g_FishingRod * 0x14) + panel_x);
            func_800F7094((s32)slot_x, (s16)icon_y, g_FishingRod, 3, 0);
            UI_DrawText((s16)icon_x, (s16)(panel_y + 24), (s32)(g_Task->option_flags), 0xCU,
                        (g_FishingRod * 0x14) + panel_x);
            func_800F7094((s32)slot_x, (s16)(panel_y + 44), g_FishingLure, 3, 0);
            last_x       = icon_x;
            last_y       = panel_y + 42;
            last_palette = 0;
        } else {
            slot_x    = (u8*)((s32)slot_x << 0x10);
            slot_x    = (u8*)((s32)slot_x >> 0x10);
            icon_y    = (s32)(&g_FishingRod);
            accessory = &g_FishingRod;
            func_800F7094((s32)slot_x, (s16)(panel_y + 28), *accessory, 3, 0);
            icon_x = panel_x + 28;
            icon_x <<= 0x10;
            icon_x         = icon_x >> 0x10;
            accessory_name = g_Accessories->header.name;
            accessory_name = g_Accessories->header.name;
            UI_DrawText((s16)icon_x, (s16)(panel_y + 26), 0, 0xCU, ((*accessory * 0x14) + accessory_name));
            func_800F7094((s32)slot_x, (s16)(panel_y + 44), g_FishingLure, 3, 1);
            icon_y = panel_y + 42;
            icon_y <<= 0x10;
            icon_y = icon_y >> 0x10;
            UI_DrawText((s16)icon_x, (s16)icon_y, 7, 0xCU, ((g_FishingLure * 0x14) + accessory_name));
            func_800F7094((s32)slot_x, (s16)icon_y, g_FishingLure, 3, 0);
            last_x       = icon_x;
            last_y       = panel_y + 40;
            last_palette = g_Task->option_flags & ACTOR_OPT_KEEP_FACING;
        }
    }
    UI_DrawText((s16)last_x, last_y, last_palette, 0xCU, 0);
    UI_DrawText((s16)(x0 + 51), (s16)(y0 + 71), 0, 5U, (&D_801E21D9));
    record_word = g_Task->unk_2C;
    if (record_word != 0xFFFF) {
        UI_DrawText(25, 154, 0, 0xFFU, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, record_word * 2));
    }
}
#else
INCLUDE_ASM(func_801D88E0);
#endif
