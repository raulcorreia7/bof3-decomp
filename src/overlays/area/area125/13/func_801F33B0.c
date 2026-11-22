#include "area125_13.h"

MATCH s32 func_801F33B0(void) {
    u8              scratch[0x30];
    AreaQuadSprite* sprite;
    u8              handled;
    u8              count;
    u8              i;
    s32             y;

    Camera_SetMatrix(scratch);
    handled = 0;
    sprite  = MEM_PTR(AreaQuadSprite, AREA_WORK);
    i       = 0;
    do {
        if (sprite->unk_00[0] != 0) {
            handled = 1;
            switch (sprite->unk_00[1]) {
                case 0:
                    sprite->shade += 4;
                    count = sprite->unk_00[2] += 1;
                    if (count == 0x10) {
                        sprite->unk_00[1] += 1;
                    }
                    break;
                case 1:
                    sprite->shade -= 4;
                    count = sprite->unk_00[2] += 1;
                    if (count == 0x20) {
                        sprite->unk_00[0] = 0;
                    }
                    break;
            }
            sprite->origin.x += sprite->unk_18;
            sprite->half_size += 8;
            y                = sprite->origin.y + sprite->unk_1C;
            sprite->origin.y = y;
            sprite->unk_10   = Area_HeightSample(sprite->origin.x, y) << 16;
            func_801F2FC4(sprite);
        }
        sprite++;
        i++;
    } while (i < 0x10);
    return handled;
}
