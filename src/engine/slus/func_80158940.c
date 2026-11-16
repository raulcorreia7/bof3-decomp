#include "engine/slus/slus.h"
#include "battle/records.h"

/* One word of a rectangle list: the header, whose third byte counts the words, or a rectangle
 * packed as x, y, width and height with a flag in bit 0. */
typedef union AreaRectWord {
    u32 rect;

    struct {
        u8 pad_00[2];
        u8 count;
        u8 pad_03;
    } header;
} AreaRectWord;

/* marks the layer and marker bytes of every entry whose rectangle
 * contains one of the three layer points or the base point.
 */
MATCH void func_80158940(void* obj) {
    AreaRectWord* cursor = obj;
    u8*           flag;
    u8*           marker;
    s32           count;
    s32           i;
    s32           j;
    u8            x;
    u8            y;
    u8            width;
    u8            height;
    s32           point_x;
    s32           point_y;

    if (g_AreaDrawMode == GFX_LAYER_BATTLE_SCENE) {
        return;
    }
    count = cursor->header.count - 1;
    cursor++;
    for (i = 0; i < count; i++) {
        j      = 0;
        flag   = &g_Game.members[0].unk_29;
        marker = &g_Game.members[0].status.unk_12C[0];
        x      = cursor->rect >> 24;
        y      = cursor->rect >> 16;
        width  = (cursor->rect >> 9) & 0x7F;
        height = (cursor->rect >> 2) & 0x7F;
        for (; j < 3; flag += sizeof(PartyMember), marker += sizeof(PartyMember), j++) {
            point_x = g_Game.members[j].pos.x.fixed + 0x8000;
            point_y = g_Game.members[j].pos.y.fixed + 0x8000;
            if ((point_x >> 16) >= x && (point_x >> 16) < width + x && (point_y >> 16) >= y && (point_y >> 16) < height + y) {
                if (cursor->rect & 1) {
                    *marker |= 1;
                    *flag = 4;
                } else {
                    *marker &= 0xFE;
                    *flag = g_AreaDrawMode;
                }
            }
        }
        point_x = g_Game.base_x.fixed + 0x8000;
        point_y = g_Game.base_y.fixed + 0x8000;
        if ((point_x >> 16) >= x && (point_x >> 16) < width + x && (point_y >> 16) >= y && (point_y >> 16) < height + y) {
            if (cursor->rect & 1) {
                g_Game.unk_3E7 |= 1;
            } else {
                g_Game.unk_3E7 &= 0xFE;
            }
        }
        cursor++;
    }
}
