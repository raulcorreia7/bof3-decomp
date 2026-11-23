#include "area145_14.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F504C(u32 frame, u8 index) {
    Area145Step* step;
    Area145Step* table;
    s32          elapsed;
    u16          t;
    u32          direction;
    u32          step_offset;
    u32          limit;
    s32          dx;
    s32          dy;
    s32          mx;
    s32          my;
    s32          x;
    s32          y;

    elapsed   = (s32)frame;
    direction = ((s32)g_PartyActors[index].unk_6C >> 9) & 3;
    if (index != 1) {
        table       = D_801F5D1C;
        step_offset = direction * 4;
    } else {
        step_offset = direction * 4;
        table       = D_801F5D0C;
    }
    step = (Area145Step*)((u8*)table + step_offset);
    elapsed -= 10;
    t     = elapsed;
    limit = step->duration;
    dx    = D_80181B00[step->heading * 2] << 16;
    mx    = elapsed;
    if (limit < t) {
        mx = limit;
    }
    x  = g_PartyActors[index].pos.x.fixed + dx * (u16)mx;
    dy = D_80181B01[step->heading * 2] << 16;
    my = elapsed;
    if (limit < t) {
        my = limit;
    }
    y = g_PartyActors[index].pos.y.fixed + dy * (u16)my;
    func_801F5190(g_PartyActors[index].pos.x.fixed, g_PartyActors[index].pos.y.fixed, x, y);
    if (t < step->duration) {
        return 1;
    }
    return step->unk_2;
}
#else
INCLUDE_ASM(func_801F504C);
#endif
