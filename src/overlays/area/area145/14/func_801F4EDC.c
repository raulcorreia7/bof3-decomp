#include "area145_14.h"

MATCH u8 func_801F4EDC(s32 t, u32 stage) {
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

    direction = (g_PartyActors[(u8)stage].angle_z >> 9) & 3;
    if ((u8)stage != 1) {
        step = &D_801F5CFC[direction];
    } else {
        step = &D_801F5CEC[direction];
    }
    t -= 5;
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
    if (step->unk_2 == 0) {
        return 1;
    }
    if (elapsed == step->duration) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 6));
    }
    return func_801F504C(elapsed, step->unk_2);
}
