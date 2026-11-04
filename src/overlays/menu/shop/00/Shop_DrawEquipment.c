#include "shop_00.h"

MATCH void Shop_DrawEquipment(s16 x, s16 y, u8 record_index) {
    const volatile void* objects[6];
    Character*           record;
    u16                  row_y;
    u8                   row;

    Menu_DrawFilledPanel(x, y, 9, 0xA);
    record = &g_Characters[record_index];
    UI_DrawText((s16)(x + 46), (s16)(y + 7), 0, 0xFF, (u8*)&D_801E583C);
    func_801644D8(0, (s32)(u16)(x + 7), (s32)(u16)(y + 5), 0x10, 0x10, 0x80);

    objects[0] = &g_Weapons[record->weapon];
    objects[1] = &g_Armors[record->shield];
    objects[2] = &g_Armors[record->helmet];
    objects[3] = &g_Armors[record->armor];
    objects[4] = &g_Accessories[record->accessories[0]];
    objects[5] = &g_Accessories[record->accessories[1]];

    for (row = 0; row < 6; row++) {
        row_y = (u16)(y + (row * 0xD + 0x1A));
        func_801AEA80((s32)(u16)(x + 5), (s32)(u16)(row_y + 2), D_801E5834[row], 0);
        UI_DrawText((s16)(x + 17), (s16)row_y, 0, func_801AF20C((u8*)objects[row]) & BYTE_MASK, (u8*)objects[row]);
    }
}
