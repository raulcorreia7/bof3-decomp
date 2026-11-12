#include "area135_14.h"

MATCH void func_801F3308(s32 x, s32 y, s32 z, s32 semitrans) {
    LINE_F2* p;
    s32      pos[3];

    p = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(p);
    pos[0] = x + 0x4000;
    pos[1] = y;
    pos[2] = z;
    Area_ProjectPoint(pos, (DVECTOR*)&p->x0);
    pos[0] = x - 0x4000;
    pos[1] = y;
    pos[2] = z;
    Area_ProjectPoint(pos, (DVECTOR*)&p->x1);
    p->r0 = g_Task->tint.bytes.unk_5D;
    p->g0 = 0;
    p->b0 = 0;
    SetSemiTrans(p, semitrans & BYTE_MASK);
    GFX_AddPrim(3, 0x10);

    p = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(p);
    pos[0] = x;
    pos[1] = y + 0x4000;
    pos[2] = z;
    Area_ProjectPoint(pos, (DVECTOR*)&p->x0);
    pos[0] = x;
    pos[1] = y - 0x4000;
    pos[2] = z;
    Area_ProjectPoint(pos, (DVECTOR*)&p->x1);
    p->r0 = g_Task->tint.bytes.unk_5D;
    p->g0 = 0;
    p->b0 = 0;
    GFX_AddPrim(3, 0x10);
    SetSemiTrans(p, semitrans & BYTE_MASK);
}
