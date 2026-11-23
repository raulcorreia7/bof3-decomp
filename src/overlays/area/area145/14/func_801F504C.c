#include "area145_14.h"

/* The second leg of func_801F4EDC's walk: moves the party actor along its step from frame 10 and returns 1
 * while the step runs, then the step's next stage. */
MATCH u8 func_801F504C(s32 t, u32 stage) {
    Area145Step* step;
    Actor*       actor;
    u16          elapsed;
    u32          duration;
    u32          direction;
    s32          dx;
    s32          dy;
    s32          moved_x;
    s32          moved_y;
    s32          x;
    s32          y;

    direction = (g_PartyActors[(u8)stage].unk_6C >> 9) & 3;
    if ((u8)stage != 1) {
        step = &D_801F5D1C[direction];
    } else {
        step = &D_801F5D0C[direction];
    }
    t -= 10;
    moved_x  = t;
    actor    = &g_PartyActors[(u8)stage]; /* Unused: retail forms the actor index here. */
    elapsed  = t;
    duration = step->duration;
    dx       = D_80181B00[step->heading * 2] << 16;
    if (duration < elapsed) {
        moved_x = duration;
    }
    x       = g_PartyActors[(u8)stage].pos.x.fixed + dx * (u16)moved_x;
    dy      = D_80181B01[step->heading * 2] << 16;
    moved_y = t;
    if (duration < elapsed) {
        moved_y = duration;
    }
    y = g_PartyActors[(u8)stage].pos.y.fixed + dy * (u16)moved_y;
    func_801F5190(g_PartyActors[(u8)stage].pos.x.fixed, g_PartyActors[(u8)stage].pos.y.fixed, x, y);
    if (elapsed < step->duration) {
        return 1;
    }
    return step->unk_2;
}
