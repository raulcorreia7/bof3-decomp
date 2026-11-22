#include "area111_13.h"

/* Walks the lead party member toward the cell the focus actor faces, then starts
 * a 32-frame move along the step the cell's event record gives. */
MATCH void func_801F3D3C(void) {
    Coord target_x;
    Coord target_y;
    s32   dx;
    s32   dy;
    s16   dz;
    s32   frames;
    u8    facing;

    target_x.fixed = g_PartyActors[g_Task->unk_18].pos.x.fixed;
    target_y.fixed = g_PartyActors[g_Task->unk_18].pos.y.fixed;
    facing         = g_Task->direction & 7;
    /* The facing step bytes count half cells. */
    target_x.part.integer += D_80181B00[facing * 2] << 1;
    target_y.part.integer += D_80181B01[facing * 2] << 1;
    dx = target_x.fixed - g_Task->pos.x.fixed;
    dy = target_y.fixed - g_Task->pos.y.fixed;
    dz = Area_HeightSample(target_x.fixed, target_y.fixed) - LOHU(g_Task->pos.z.part.integer);
    if (g_ScriptState->move_mode != 0) {
        frames        = 32;
        g_Task->timer = 32;
        setVector(g_Task, dx / frames, dy / frames, dz / frames);
    }
}
