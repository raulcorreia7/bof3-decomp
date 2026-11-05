#include "area030_04.h"

/* Draws the accessory panel for one actor row: the accessory icons, their names and the slot markers
 * around the actor's icon. */
/* nonmatching unmeasured: the retail frame is 0x48 and the candidate 0x40, so the eight unused frame bytes are
 * declared; candidate 60.27%. resume: a source shape that reproduces the retail's cell, row and enemy-row address
 * forms. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D88E0(s16 arg0, s16 arg1) {
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);
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

    panel_x = arg0;
    panel_y = arg1;
    func_801D8D70((u16)panel_x, (u16)panel_y);
    UI_DrawText((s16)(panel_x + 0x33), (s16)(panel_y + 7), 0, 5U, (&D_801E21D4));
    x0              = panel_x;
    accessory_flags = g_Task->unk_07;
    y0              = panel_y;
    if (accessory_flags & 0x80) {
        icon_x = panel_x + 0x10;
        icon_x <<= 0x10;
        icon_x = icon_x >> 0x10;
        slot_x = &D_80145028;
        slot_x = &D_80145028;
        func_800F7094(icon_x, (s16)(panel_y + 0x1C), D_80145028, 3, 0);
        icon_y = panel_x + 0x1C;
        icon_y <<= 0x10;
        icon_y = icon_y >> 0x10;
        slot_x = g_Accessories->name;
        slot_x = g_Accessories->name;
        UI_DrawText((s16)icon_y, (s16)(panel_y + 0x1A), 0, 0xCU, ((D_80145028 * 0x14) + slot_x));
        func_800F7094(icon_x, (s16)(panel_y + 0x2C), D_80145026, 3, 0);
        last_x       = icon_y;
        last_y       = panel_y + 0x2A;
        last_palette = 0;
    } else {
        slot_x = panel_x + 0x10;
        if (!(accessory_flags & 1)) {
            slot_x         = (u8*)((s32)slot_x << 0x10);
            slot_x         = (u8*)((s32)slot_x >> 0x10);
            accessory_name = &D_80145028;
            accessory_name = &D_80145028;
            func_800F7094((s32)slot_x, (s16)(panel_y + 0x1C), D_80145028, 3, 1);
            icon_x = panel_x + 0x1C;
            icon_x <<= 0x10;
            icon_x = icon_x >> 0x10;
            icon_y = panel_y + 0x1A;
            icon_y <<= 0x10;
            icon_y  = icon_y >> 0x10;
            panel_x = (s16)g_Accessories;
            panel_x = (s16)g_Accessories;
            UI_DrawText((s16)icon_x, (s16)icon_y, 7, 0xCU, (D_80145028 * 0x14) + panel_x);
            func_800F7094((s32)slot_x, (s16)icon_y, D_80145028, 3, 0);
            UI_DrawText((s16)icon_x, (s16)(panel_y + 0x18), (s32)(g_Task->unk_07), 0xCU, (D_80145028 * 0x14) + panel_x);
            func_800F7094((s32)slot_x, (s16)(panel_y + 0x2C), D_80145026, 3, 0);
            last_x       = icon_x;
            last_y       = panel_y + 0x2A;
            last_palette = 0;
        } else {
            slot_x    = (u8*)((s32)slot_x << 0x10);
            slot_x    = (u8*)((s32)slot_x >> 0x10);
            icon_y    = (s32)(&D_80145028);
            accessory = &D_80145028;
            func_800F7094((s32)slot_x, (s16)(panel_y + 0x1C), *accessory, 3, 0);
            icon_x = panel_x + 0x1C;
            icon_x <<= 0x10;
            icon_x         = icon_x >> 0x10;
            accessory_name = g_Accessories->name;
            accessory_name = g_Accessories->name;
            UI_DrawText((s16)icon_x, (s16)(panel_y + 0x1A), 0, 0xCU, ((*accessory * 0x14) + accessory_name));
            func_800F7094((s32)slot_x, (s16)(panel_y + 0x2C), D_80145026, 3, 1);
            icon_y = panel_y + 0x2A;
            icon_y <<= 0x10;
            icon_y = icon_y >> 0x10;
            UI_DrawText((s16)icon_x, (s16)icon_y, 7, 0xCU, ((D_80145026 * 0x14) + accessory_name));
            func_800F7094((s32)slot_x, (s16)icon_y, D_80145026, 3, 0);
            last_x       = icon_x;
            last_y       = panel_y + 0x28;
            last_palette = g_Task->unk_07 & ACTOR_OPT_KEEP_FACING;
        }
    }
    UI_DrawText((s16)last_x, last_y, last_palette, 0xCU, 0);
    UI_DrawText((s16)(x0 + 0x33), (s16)(y0 + 0x47), 0, 5U, (&D_801E21D9));
    record_word = g_Task->unk_2C;
    if (record_word != 0xFFFF) {
        UI_DrawText(0x19, 0x9A, 0, 0xFFU, D_80010000[record_word * 2] + FISHING_TEXT_BANK);
    }
}
#else
INCLUDE_ASM(func_801D88E0);
#endif
