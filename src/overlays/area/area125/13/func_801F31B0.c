#include "area125_13.h"

MATCH void func_801F31B0(s32 arg0) {
    AreaSprite* sprite;
    u8          index;
    s32         x;
    s32         y;
    s32         z;
    s32         w;

    index  = arg0;
    sprite = (AreaSprite*)Area_FindFreeWorkRow();
    if (sprite != NULL) {
        sprite->unk_00[0]  = 1;
        sprite->flags_03   = 0x20;
        sprite->unk_00[1]  = 0;
        sprite->unk_00[2]  = 0;
        sprite->half_size  = 0x80;
        x                  = FIELD(s16, D_801F364C, index * 4) << 8;
        sprite->origin_x   = x;
        y                  = FIELD(s16, D_801F364E, index * 4) << 8;
        sprite->unk_10     = 0;
        sprite->origin_y   = y;
        z                  = FIELD(s16, D_801F368C, index * 4) << 5;
        sprite->unk_18     = z;
        w                  = FIELD(s16, D_801F368E, index * 4) << 5;
        sprite->unk_20     = 0;
        sprite->unk_1C     = w;
    }
}
