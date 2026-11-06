#include "game_00.h"

MATCH void func_801AC1DC(s32* out, u8 selector) {
    SVECTOR rot;
    VECTOR  trans;
    MATRIX  matrix;
    long    flags;
    u16     world;

    PushMatrix();
    rot.vx = g_Task->unk_64;
    rot.vy = g_Task->unk_68;
    rot.vz = g_Task->unk_6C;
    RotMatrix(&rot, &matrix);
    trans.vz = 0;
    trans.vy = 0;
    trans.vx = 0;
    TransMatrix(&matrix, &trans);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
    world  = g_GameAreaId;
    rot.vx = *(u16*)(((AreaLoad*)g_AreaLoads[world])->unk_0C + (selector & 0xFF) * 6);
    rot.vy = *(u16*)(((AreaLoad*)g_AreaLoads[world])->unk_0C + (selector & 0xFF) * 6 + 2);
    rot.vz = *(u16*)(((AreaLoad*)g_AreaLoads[world])->unk_0C + (selector & 0xFF) * 6 + 4);
    RotTrans(&rot, &trans, &flags);
    out[0] = trans.vx << 9;
    out[1] = trans.vy << 9;
    out[2] = -(trans.vz << 1);
    PopMatrix();
}
