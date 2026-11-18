#include "area145_14.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F504C(u32 frame, u8 index) {
    s32 elapsed;
    u16 t;
    u32 off;
    u32 off4;
    u32 limit;
    s32 dx;
    s32 dy;
    s32 mx;
    s32 my;
    s32 x;
    s32 y;
    s32 base_x;
    u8* base;
    u8* step;

    off     = ((s32)D_80147A58[index].unk_6C >> 9) & 3;
    elapsed = (s32)frame;
    if (index != 1) {
        base = D_801F5D1C;
        off4 = off * 4;
    } else {
        off4 = off * 4;
        base = D_801F5D0C;
    }
    base_x = D_80147A58[index].pos.x.fixed;
    step   = base + off4;
    elapsed -= 10;
    t     = elapsed;
    limit = step[1];
    dx    = D_80181B00[step[0] * 2] << 16;
    mx    = elapsed;
    if (limit < t) {
        mx = limit;
    }
    x  = base_x + dx * (u16)mx;
    dy = D_80181B01[step[0] * 2] << 16;
    my = elapsed;
    if (limit < t) {
        my = limit;
    }
    y = D_80147A58[index].pos.y.fixed + dy * (u16)my;
    func_801F5190(base_x, D_80147A58[index].pos.y.fixed, x, y);
    if (t < step[1]) {
        return 1;
    }
    return step[2];
}
#else
INCLUDE_ASM(func_801F504C);
#endif
