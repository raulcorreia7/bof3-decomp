#include "area191_13.h"
#include "menu/save_data.h"

MATCH u16 func_801F37AC(u8 character_id) {
    u8  area;
    u8  slot;
    u8  fatigue;
    u8  row;
    s32 base;

    /* kept: row is the found slot, then its table base, then the index; a local of its own for the slot changes the bytes. */
    for (row = 0; row < CAMP_MESSAGE_CHARACTER_COUNT; row++) {
        if (D_801F4248[row] == character_id) {
            break;
        }
    }
    area = g_SaveData.desert.days;
    base = row * CAMP_MESSAGE_ROW_SIZE;
    row  = base;
    if (area >= CAMP_MESSAGE_ROW_SIZE) {
        area = CAMP_MESSAGE_AREA_LAST;
    }
    slot    = g_CharSlot[character_id];
    fatigue = g_Characters[slot].fatigue;
    if (SYS_TestFlag(&g_SaveData.scene_flag_words[14 * 8], 0xA) != 0) {
        return func_801F3924(row, character_id, area, fatigue);
    }
    if (fatigue < 8) {
        if (fatigue >= 5 && area < 7) {
            row = base + 7;
        } else {
            row = row + D_801F4250[area];
        }
    } else {
        row = base + CAMP_MESSAGE_AREA_LAST;
    }
    if (SYS_TestFlag(g_SceneFlags, 2) != 0) {
        return D_801F4218[row];
    }
    return D_801F41E8[row];
}
