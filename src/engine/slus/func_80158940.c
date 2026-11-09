#include "engine/slus/slus.h"
#include "battle/records.h"

/* marks the layer and marker bytes of every entry whose rectangle contains one of the three layer points or the base point. */
/* nonmatching 90.85%: tried the first draft cleaned to compiling C; best score 90.85%. resume: a lever or header fix
 * that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_80158940(void* obj) {
    u32* cursor = (u32*)obj;
    s32* base;
    u8*  flag;
    u8*  marker;
    s32  entry_count;
    s32  entry_index;
    s32  layer;
    s32  layer_offset;
    s32  bias;
    u8   x;
    u8   y;
    u8   width;
    u8   height;
    s32  point_x;
    s32  point_y;
    u8   flag_value;

    if (g_AreaDrawMode == 4) {
        return;
    }
    entry_count = *((u8*)cursor + 2) - 1;
    cursor += 1;
    bias = 0x8000;
    if (entry_count <= 0) {
        return;
    }
    base = &D_801462A0;
    for (entry_index = 0; entry_index < entry_count; entry_index++) {
        layer        = 0;
        flag         = &g_Game.members[0].unk_29;
        marker       = flag + 0x103;
        x            = *cursor >> 24;
        y            = *cursor >> 16;
        width        = (*cursor >> 9) & 0x7F;
        height       = (*cursor >> 2) & 0x7F;
        layer_offset = 0;
        for (; layer < 3; layer++) {
            point_x = (FIELD(s32, &D_80145EC4, layer_offset) + bias) >> 16;
            point_y = (FIELD(s32, &D_80145EC8, layer_offset) + bias) >> 16;
            if ((point_x >= x) && (point_x < (x + width)) && (point_y >= y) && (point_y < (y + height))) {
                if ((*cursor & 1) != 0) {
                    *marker |= 1;
                    flag_value = 4;
                } else {
                    *marker &= 0xFE;
                    flag_value = g_AreaDrawMode;
                }
                *flag = flag_value;
            }
            flag += BATTLE_PARTY_STRIDE;
            marker += BATTLE_PARTY_STRIDE;
            layer_offset += BATTLE_PARTY_STRIDE;
        }

        point_x = (*base + bias) >> 16;
        point_y = (base[1] + bias) >> 16;
        if ((point_x >= x) && (point_x < (x + width)) && (point_y >= y) && (point_y < (y + height))) {
            if ((*cursor & 1) != 0) {
                *((u8*)base - 0x29) |= 1;
            } else {
                *((u8*)base - 0x29) &= 0xFE;
            }
        }

        cursor += 1;
    }
}
#else
/* First difference: the bias load is scheduled early. */
INCLUDE_ASM(func_80158940);
#endif
