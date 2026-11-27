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

    target_x.fixed = g_PartyActors[SELF(Actor)->unk_18].pos.x.fixed;
    target_y.fixed = g_PartyActors[SELF(Actor)->unk_18].pos.y.fixed;
    facing         = SELF(Actor)->direction & 7;
    /* The facing step bytes count half cells. */
    target_x.part.integer += D_80181B00[facing][0] << 1;
    target_y.part.integer += D_80181B00[facing][1] << 1;
    dx = target_x.fixed - SELF(Actor)->pos.x.fixed;
    dy = target_y.fixed - SELF(Actor)->pos.y.fixed;
    dz = Area_HeightSample(target_x.fixed, target_y.fixed) - LOHU(SELF(Actor)->pos.z.part.integer);
    if (g_ScriptState->move_mode != 0) {
        frames             = 32;
        SELF(Actor)->timer = 32;
        setVector(SELF(Actor), dx / frames, dy / frames, dz / frames);
    }
}
