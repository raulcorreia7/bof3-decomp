#include "area030_04.h"

/* The accessory slot list sits this far past the panel style byte. */
#define FISHING_ACCESSORY_SLOT_OFFSET 0x87A
/* The accessory slot list: one byte per slot, naming the accessory type. */
#define FISHING_ACCESSORY_SLOT_COUNT  128
/* Each accessory row is one icon cell tall. */
#define FISHING_ACCESSORY_ROW_HEIGHT  0xD

/* Draws the accessory slot list: two icon rows per accessory with
 * its quantity, then the footer and the selection cursor clamp. */
/* nonmatching unmeasured: the x/y parameters are 32-bit (the retail prologue copies $a0 and $a1 whole into $s0 and $v1
 * and never re-sign-extends them, and it masks the y argument with 0xFFFF after adding 1); area030_04.h and this
 * definition now declare them s32, and the callers narrow their argument to 16 bits themselves. resume: a source shape
 * that reproduces the retail's argument narrowing and its 0x58 frame. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D7EB0(s32 x, s32 y) {
    FishingState* work;
    u8*           buffer;
    u8*           slot_list;
    s32           icon_y;
    s32           row;
    s32           slot;
    u8            id;
    u8            qty;

    row       = 0;
    /* the accessory rows step down from the panel's first icon row */
    icon_y    = y + 0x19;
    buffer    = g_UiFormatBuffer;
    slot_list = (u8*)MEM_PTR(u8, (u8*)&D_80144952 + FISHING_ACCESSORY_SLOT_OFFSET);
    UI_DrawWindow(x, (y + 1) & 0xFFFF, 0x8B, 0x9E, 0xF0, D_80144952);
    for (slot = 0; slot < FISHING_ACCESSORY_SLOT_COUNT; slot++) {
        id = *slot_list;
        if (g_Accessories[id].header.flags != 0xB) {
            slot_list++;
            continue;
        }
        work = (FishingState*)(void*)g_Task;
        if (work->pos_x_0C == row) {
            FIELD(s16, work, 0x36u) = slot;
        }
        if (D_80145E94[0] == 2 && !(work->counter_07 & 1) && work->pos_x_0C == row) {
            UI_DrawText(x + 5, (s16)icon_y, 7, 0xC, (u8*)&g_Accessories[id]);
            UI_DrawText(x + 5, y + 0x17 + icon_y - (y + 0x19), 0, 0xC, (u8*)&g_Accessories[id]);
            qty = g_InventoryCounts[3][slot];
            if (qty >= 2) {
                sprintf((char*)buffer, D_801D0C14, qty);
                UI_DrawGlyphString(x + 0x68, y + 0x1D + icon_y - (y + 0x19), 7, buffer);
                UI_DrawGlyphString(x + 0x68, y + 0x1B + icon_y - (y + 0x19), 0, buffer);
            }
        } else {
            UI_DrawText(x + 5, (s16)icon_y, 0, 0xC, (u8*)&g_Accessories[id]);
            qty = g_InventoryCounts[3][slot];
            if (qty >= 2) {
                sprintf((char*)buffer, D_801D0C14, qty);
                UI_DrawGlyphString(x + 0x68, y + 0x1D + icon_y - (y + 0x19), 0, buffer);
            }
        }
        icon_y += FISHING_ACCESSORY_ROW_HEIGHT;
        row += 1;
        slot_list++;
    }
    work                = (FishingState*)(void*)g_Task;
    work->step_delta_18 = row;
    if (work->pos_x_0C >= row) {
        work->pos_x_0C = row == 0 ? 0 : row - 1;
    }
    func_801D90FC(x, y);
    func_801D8248(x + 0x80, y + 0x1C, 0x72);
    UI_DrawText(x + 0x3A, y + 7, 0, 3, D_801E21CC);
}
#else
INCLUDE_ASM(func_801D7EB0);
#endif
