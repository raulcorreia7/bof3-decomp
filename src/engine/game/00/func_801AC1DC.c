#include "game_00.h"

MATCH void func_801AC1DC(s32* out, u8 selector) {
    SVECTOR rot;
    VECTOR  trans;
    MATRIX  matrix;
    long    flags;
    u16     world;

    PushMatrix();
    setVector(&rot, TASK(Actor)->angle_x, TASK(Actor)->angle_y, TASK(Actor)->angle_z);
    RotMatrix(&rot, &matrix);
    trans.vz = 0;
    trans.vy = 0;
    trans.vx = 0;
    TransMatrix(&matrix, &trans);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    world = g_GameAreaId;
    setVector(&rot, *(u16*)(((AreaLoad*)g_AreaLoads[world])->unk_0C + (selector & BYTE_MASK) * 6), *(u16*)(((AreaLoad*)g_AreaLoads[world])->unk_0C + (selector & BYTE_MASK) * 6 + 2),
              *(u16*)(((AreaLoad*)g_AreaLoads[world])->unk_0C + (selector & BYTE_MASK) * 6 + 4));
    RotTrans(&rot, &trans, &flags);
    out[0] = trans.vx << 9;
    out[1] = trans.vy << 9;
    out[2] = -(trans.vz << 1);
    PopMatrix();
}
