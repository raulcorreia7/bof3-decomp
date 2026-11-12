#include "scena00_00.h"
#include "area/map.h"

static Scene00Tables D_801FC980_Tables = {
    {
        func_801F6E04, func_801F6E48, func_801F7264, func_801F72A0, func_801F7350, func_801F7350, func_801F73A8, func_801F7484, (Callback)func_801F74EC,
        func_801F7670, func_801F78CC, func_801F7A5C, func_801F7B0C, func_801F7B80, func_801F7C34, func_801F7CF0, func_801F7DC8, func_801F7EE0,
        func_801F8014, func_801F8140, func_801F82B4, func_801F878C, func_801F882C, func_801F8930, func_801F89F0, func_801F8AB8,
    },
    0x0C,
    (s8)0xC8,
    {0, 0},
    {-2, -1, -1, 1},
    {1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 1},
    {
        func_801F913C,
        (Callback)Scene_DispatchActor,
        (Callback)Scene_CheckStepTrigger,
        (Callback)func_801FC8F4,
    },
    0,
    {
        func_801F9178,
        func_801F92DC,
        func_801F9B98,
        func_801F9BD4,
        func_801F9BDC,
        func_801F9BE4,
        func_801F9FB8,
        func_801FA27C,
        func_801FA7D8,
        func_801FAF6C,
        func_801FB204,
        func_801FB620,
        func_801FB67C,
        func_801FB744,
        func_801FB924,
    },
    {0xFF, 0x00, 0x01, 0x00, 0xFF, 0x00, 0x01, 0x00, 0xFF, 0x00, 0x01, 0x00, 0xFF, 0x00, 0x01, 0x00},
    {0x0A, 0x32, 0x14, 0x32, 0x1E, 0x00, 0x00, 0x00},
    {
        {0x00, 0x00},
        {0x01, 0x00},
        {0x01, 0x02},
        {0x01, 0x01},
        {0x01, 0x04},
        {0x00, 0x00},
        {0x01, 0x03},
        {0x00, 0x00},
        {0x01, 0x06},
        {0x01, 0x07},
        {0x00, 0x00},
        {0x00, 0x00},
        {0x01, 0x05},
        {0x00, 0x00},
        {0x00, 0x00},
        {0x00, 0x00},
    },
};

MATCH void func_801F6DC0(void) {
    D_801FC980[g_Task->header.mode]();
}

MATCH void func_801F6E04(void) {
    SceneEffect* work;
    u32          value;
    u32          index;

    work  = SCN_EFFECT;
    index = work->channel_18;
    value = ((Actor*)D_80147A58)[index].range_54.word;

    work->step   = 1;
    work->unk_54 = value;
}

MATCH void func_801F6E48(void) {
    u8*          work;
    SceneEffect* work_cell;
    Actor*       adopted;
    u8*          prim;
    POLY_FT4*    poly;
    s32          origin[3];
    SVECTOR      projection;
    long         depth;
    long         flag;
    u16          x;
    u16          x2;
    u16          y;

    work      = (u8*)g_Task;
    prim      = g_GfxPrimCursor;
    work_cell = (SceneEffect*)work;
    adopted   = (Actor*)(D_80147A58 + work_cell->channel_18 * 0x98);

    work_cell->pos.x       = adopted->pos.x.fixed;
    work_cell->pos.y       = adopted->pos.y.fixed;
    work_cell->pos.z.fixed = adopted->pos.z.fixed;
    g_GfxPrimCursor        = prim + 8;
    TASK_SET(adopted);
    ((RECT*)prim)->x = 0;
    ((RECT*)prim)->y = 240;
    setWH(((RECT*)prim), 16, 16);
    SetTexWindow((DR_TWIN*)(prim + 8), (RECT*)prim);
    Area_AddCellPrim(SPAD_ROW->pos.x.fixed, SPAD_ROW->pos.y.fixed, 0x11, 0x0C);

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);

    func_801AC1DC(origin, work_cell->channel_1C);

    projection.vx = ((origin[0] + SPAD_ROW->pos.x.fixed) >> 9) - 0x4000;
    projection.vy = ((origin[1] + SPAD_ROW->pos.y.fixed) >> 9) - 0x4000;
    projection.vz = -(origin[2] + COORD_INT(SPAD_ROW->pos.z)) / 2;

    work_cell->projected = RotTransPers(&projection, (long*)&poly->x0, &depth, &flag);

    y        = poly->y0;
    x        = poly->x0;
    poly->y1 = 0;
    poly->y0 = 0;
    g_Task   = work;
    x2       = poly->x0;
    poly->x1 = x + 8;
    poly->x3 = x + 8;
    poly->x0 = x2 - 8;
    poly->x2 = x2 - 8;
    poly->y3 = y;
    poly->y2 = y;
    setClut(poly, 176, STAGE_PALETTE_Y + 3);
    poly->tpage = GetTPage(0, 0, 704, 256);

    setUV4(poly, 0, (g_FrameCount >> 2) & 0x15, 16, (g_FrameCount >> 2) & 0x15, 0, ((g_FrameCount >> 2) & 0x15) + poly->y2, 16, ((g_FrameCount >> 2) & 0x15) + poly->y2);

    setRGB0(poly, 128, 128, 128);

    SetShadeTex(poly, 1);

    Area_AddCellPrim(SPAD_ROW->pos.x.fixed, SPAD_ROW->pos.y.fixed, 0x11, sizeof(POLY_FT4));

    prim             = g_GfxPrimCursor;
    g_GfxPrimCursor  = prim + 8;
    ((RECT*)prim)->x = 0;
    ((RECT*)prim)->y = 0;
    setWH(((RECT*)prim), 256, 256);
    SetTexWindow((DR_TWIN*)(prim + 8), (RECT*)prim);

    Area_AddCellPrim(SPAD_ROW->pos.x.fixed, SPAD_ROW->pos.y.fixed, 0x11, 0x0C);
}

MATCH void func_801F70F0(void) {
    SceneEffect* work;

    work = SCN_EFFECT;
    D_801FC988[work->step]();
}

MATCH void func_801F7134(s32 chapter_id) {
    SPRT* prim;
    s32   tpage;

    tpage = getTPage(1, 2, 832, 256);
    GFX_SET_DRAW_MODE(tpage);
    GFX_AddPrim(g_Task->draw_layer, sizeof(DR_MODE));

    prim = (SPRT*)g_GfxPrimCursor;
    SetSprt(prim);
    setXY0(prim, 32, 32);
    setUV0(prim, 0, 32);
    setWH(prim, 256, 1768);
    prim->clut = 0x7A80;
    setRGB0(prim, g_Task->tint.bytes.unk_5D, g_Task->tint.bytes.unk_5E, g_Task->tint.bytes.unk_5F);
    SetShadeTex(prim, 0);
    SetSemiTrans(prim, chapter_id & BYTE_MASK);
    GFX_AddPrim(g_Task->draw_layer, sizeof(SPRT));
}

MATCH void func_801F7264(void) {
    u8* first;
    u8* second;
    u8* third;

    first       = (u8*)g_Task;
    first[0x5F] = 0;
    first[0x5E] = 0;
    first[0x5D] = 0;

    second    = (u8*)g_Task;
    second[9] = 0xF0;

    third    = (u8*)g_Task;
    third[1] = 1;
}

MATCH void func_801F72A0(void) {
    SceneEffect* work;

    func_801F7134(1);

    g_Task->tint.bytes.unk_5D += 2;
    g_Task->tint.bytes.unk_5E += 2;
    g_Task->tint.bytes.unk_5F += 2;

    work = SCN_EFFECT;
    if (work->color_r == 0x80) {
        g_ScriptVarsReq.byte = 0x14;
        work->step           = 2;
        g_Task->timer        = 255;
    }
}

MATCH void func_801F7350(void) {
    u8* work;
    u8  timer;

    func_801F7134(1);

    work  = (u8*)g_Task;
    timer = work[9];
    if (timer == 0) {
        work[1]++;
        work = (u8*)g_Task;
    }
    work[9] = timer ? timer - 1 : 0xFF;
}

MATCH void func_801F73A8(void) {
    SceneEffect* work;

    func_801F7134(1);

    work = SCN_EFFECT;
    work->color_r -= 2;
    work = SCN_EFFECT;
    work->color_g -= 2;
    work = SCN_EFFECT;
    work->color_b -= 2;

    work = SCN_EFFECT;
    if (work->color_r == 0) {
        work->counter_09 = 0;
        Actor_Clear();
    }
}

MATCH void func_801F7440(void) {
    SceneEffect* work;

    work = SCN_EFFECT;
    D_801FC99C[work->step]();
}

MATCH void func_801F7484(void) {
    s16 distance;

    SCN_EFFECT->pos.x              = TO_COORD(11);
    SCN_EFFECT->pos.y              = TO_COORD(15) + COORD_HALF;
    distance                       = Area_SampleHeight(SCN_EFFECT->pos.x, TO_COORD(15) + COORD_HALF);
    SCN_EFFECT->pos.z.part.integer = distance;
    SCN_EFFECT->ot_index           = 5;
    SCN_EFFECT->step               = 1;
}

/* Draws the forward scenario line from the active work point toward the row point in 0x8000 steps. */
MATCH void func_801F74EC(void) {
    SceneEffect*   work;
    Actor*         row;
    SceneLinePoint point;
    SceneLinePoint next;
    SceneLinePoint row_point;
    SceneLineColor color;
    s16            stop;

    work              = SCN_EFFECT;
    color             = D_801F6C04;
    row               = (Actor*)&g_Actors[work->channel_06];
    point.x           = work->pos.x;
    next.x            = point.x;
    point.y           = work->pos.y;
    next.y            = point.y;
    point.z           = work->pos.z;
    next.z            = point.z;
    row_point.x       = row->pos.x.fixed;
    row_point.y       = row->pos.y.fixed;
    row_point.z.fixed = row->pos.z.fixed;
    stop              = 1;
    do {
        next.x = point.x;
        next.y = point.y + 0x8000;
        if (row_point.y < next.y) {
            next.y = row_point.y;
            next.z = row_point.z;
            stop   = 0;
        } else {
            next.z.part.integer = Area_SampleHeight(point.x, next.y);
        }
        func_801F78EC(next, point, color);
        point = next;
    } while (stop);

    if (g_ScriptVars[2] == 0x32) {
        SCN_EFFECT->step = 2;
    }
}

/* Draws the scenario line forward from the active point to the row point in 0x8000 steps, then back
 * from the far corner to the row point.
 */
MATCH void func_801F7670(void) {
    FAKE_STACK_PADS(u8, 8);
    SceneEffect*   work;
    Actor*         row;
    SceneLinePoint point;
    SceneLinePoint next;
    SceneLinePoint row_point;
    SceneLineColor color;
    s16            stop;

    work              = SCN_EFFECT;
    color             = D_801F6C04;
    row               = (Actor*)&g_Actors[work->channel_06];
    point.x           = work->pos.x;
    point.y           = work->pos.y;
    point.z           = work->pos.z;
    row_point.x       = row->pos.x.fixed;
    row_point.y       = row->pos.y.fixed;
    row_point.z.fixed = row->pos.z.fixed;
    stop              = 1;
    do {
        next.x = point.x;
        next.y = point.y + 0x8000;
        if (row_point.y < next.y) {
            next.y = row_point.y;
            next.z = row_point.z;
            stop   = 0;
        } else {
            next.z.part.integer = Area_SampleHeight(point.x, next.y);
        }
        func_801F78EC(next, point, color);
        point = next;
    } while (stop);

    point.x              = TO_COORD(11);
    point.y              = TO_COORD(19) + COORD_HALF;
    point.z.part.integer = Area_SampleHeight(TO_COORD(11), TO_COORD(19) + COORD_HALF);
    color.r              = 0x30;
    color.g              = 0x30;
    color.b              = 0x30;
    stop                 = 1;
    do {
        next.x = point.x;
        next.y = point.y - COORD_HALF;
        if (next.y < row_point.y) {
            next.y = row_point.y;
            next.z = row_point.z;
            stop   = 0;
        } else {
            next.z.part.integer = Area_SampleHeight(point.x, next.y);
        }
        func_801F78EC(point, next, color);
        point = next;
    } while (stop);

    if (g_ScriptVars[2] == 0x34) {
        SCN_EFFECT->step = 3;
    }
}

MATCH void func_801F78CC(void) {
    Actor_Clear();
}

/* Draws the scenario line between two transformed points with the given color and appends one
 * LINE_F2 primitive.
 */
MATCH void func_801F78EC(volatile SceneLinePoint to, volatile SceneLinePoint from, SceneLineColor color) {
    LINE_F2* prim;
    SVECTOR  vec;
    long     p;
    long     flag;
    Coord*   point_z;

    prim = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(prim);

    vec.vx  = ((from.x >> 9) - 0x4000);
    vec.vy  = ((from.y >> 9) - 0x4000);
    point_z = (Coord*)&from.z;
    vec.vz  = (-point_z->part.integer / 2);
    RotTransPers(&vec, (long*)&prim->x0, &p, &flag);

    vec.vx  = ((to.x >> 9) - 0x4000);
    vec.vy  = ((to.y >> 9) - 0x4000);
    point_z = (Coord*)&to.z;
    vec.vz  = (-point_z->part.integer / 2);
    RotTransPers(&vec, (long*)&prim->x1, &p, &flag);

    setRGB0(prim, color.r, color.g, color.b);

    GFX_AddPrim((u8)SCN_EFFECT->ot_index, sizeof(*prim));
}

MATCH void func_801F7A18(void) {
    SceneEffect* work;

    work = SCN_EFFECT;
    D_801FC9AC[work->step]();
}

MATCH void func_801F7A5C(void) {
    SceneEffect* work_pos;
    SceneEffect* work_tail;
    SceneEffect* work_state;

    work_pos                     = SCN_EFFECT;
    work_pos->pos.x              = TO_COORD(99) + COORD_HALF;
    work_pos->pos.y              = TO_COORD(13);
    work_pos->pos.z.part.integer = 0x300;
    work_pos->counter_09         = 0x78;
    work_tail                    = SCN_EFFECT;
    work_pos->angle.x            = 0;
    work_pos->angle.y            = 0;
    work_pos->angle.z            = 0;
    *(s8*)&work_tail->color_b    = -1;
    *(s8*)&work_tail->color_g    = -1;
    *(s8*)&work_tail->color_r    = -1;
    work_state                   = SCN_EFFECT;
    work_state->counter_0C       = 1;
    work_state->counter_10       = 0;
    work_state->channel_20       = 0;
    work_state->channel_1C       = 0;
    work_state->channel_18       = 0;
    work_state->channel_0A       = 0;
    work_state->channel_0B       = 0;
    work_state->channel_08       = 0;
    work_state->channel_07       = 0;
    work_state->channel_06       = 0;
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
    SCN_EFFECT->step = 1;
}

MATCH void func_801F7B0C(void) {
    s32          step;
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    work             = SCN_EFFECT;
    step             = work->channel_18 + 8;
    work->channel_18 = step;
    if (step == 96) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 2;
    }
}

MATCH void func_801F7B80(void) {
    s32          channel;
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    work             = SCN_EFFECT;
    channel          = work->channel_1C + 0x10;
    work->channel_1C = channel;
    if (channel == 0x20) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
    }
    if (SCN_EFFECT->channel_1C == 0xA0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 3;
    }
}

MATCH void func_801F7C34(void) {
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    Scene_DrawTriangle(SCN_EFFECT->channel_0B, 0x155, 0, 0x200);
    work             = SCN_EFFECT;
    work->channel_0B = (work->channel_0B + 0x10);
    if (SCN_EFFECT->channel_0B == 0x60) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 4;
    }
}

MATCH void func_801F7CF0(void) {
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    Scene_DrawTriangle(SCN_EFFECT->channel_0B, 0x155, 0, 0x200);
    Scene_DrawTriangle(SCN_EFFECT->channel_08, 0xE3, 0, 0xE38);
    work             = SCN_EFFECT;
    work->channel_08 = (work->channel_08 + 8);
    if (SCN_EFFECT->channel_08 == 0x60) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 5;
    }
}

MATCH void func_801F7DC8(void) {
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    Scene_DrawTriangle(SCN_EFFECT->channel_0B, 0x155, 0, 0x200);
    Scene_DrawTriangle(SCN_EFFECT->channel_08, 0xE3, 0, 0xE38);
    Scene_DrawTriangle(SCN_EFFECT->channel_0A, 0x31C, 0, 0x555);
    work             = SCN_EFFECT;
    work->channel_0A = (work->channel_0A + 8);
    if (SCN_EFFECT->channel_0A == 0x10) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
    }
    if (SCN_EFFECT->channel_0A == 0x60) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 6;
    }
}

MATCH void func_801F7EE0(void) {
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    Scene_DrawTriangle(SCN_EFFECT->channel_0B, 0x155, 0, 0x200);
    Scene_DrawTriangle(SCN_EFFECT->channel_08, 0xE3, 0, 0xE38);
    Scene_DrawTriangle(SCN_EFFECT->channel_0A, 0x31C, 0, 0x555);
    Scene_DrawTriangle(SCN_EFFECT->channel_06, 0x238, 0, 0xAAA);
    work             = SCN_EFFECT;
    work->channel_06 = (work->channel_06 + 8);
    if (SCN_EFFECT->channel_06 == 0x10) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
    }
    if (SCN_EFFECT->channel_06 == 0x60) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 7;
    }
}

MATCH void func_801F8014(void) {
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    Scene_DrawTriangle(SCN_EFFECT->channel_0B, 0x155, 0, 0x200);
    Scene_DrawTriangle(SCN_EFFECT->channel_08, 0xE3, 0, 0xE38);
    Scene_DrawTriangle(SCN_EFFECT->channel_0A, 0x31C, 0, 0x555);
    Scene_DrawTriangle(SCN_EFFECT->channel_06, 0x238, 0, 0xAAA);
    Scene_DrawTriangle(SCN_EFFECT->channel_07, 0, 0, 0x71C);
    work             = SCN_EFFECT;
    work->channel_07 = (work->channel_07 + 8);
    if (SCN_EFFECT->channel_07 == 0x60) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
        SCN_EFFECT->step = 8;
    }
}

MATCH void func_801F8140(void) {
    s32          channel;
    SceneEffect* work;

    Scene_DrawTriangle(SCN_EFFECT->channel_18, 0x200, 0, 0);
    Scene_DrawTriangle(SCN_EFFECT->channel_1C, 0x71, 0, 0x8E3);
    Scene_DrawTriangle(SCN_EFFECT->channel_0B, 0x155, 0, 0x200);
    Scene_DrawTriangle(SCN_EFFECT->channel_08, 0xE3, 0, 0xE38);
    Scene_DrawTriangle(SCN_EFFECT->channel_0A, 0x31C, 0, 0x555);
    Scene_DrawTriangle(SCN_EFFECT->channel_06, 0x238, 0, 0xAAA);
    Scene_DrawTriangle(SCN_EFFECT->channel_07, 0, 0, 0x71C);
    Scene_DrawTriangle(SCN_EFFECT->channel_20, 0, 0, 0xC00);
    work             = SCN_EFFECT;
    channel          = work->channel_20 + 8;
    work->channel_20 = channel;
    if (channel == 0x10) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 14));
    }
    if (SCN_EFFECT->channel_20 == 0x60) {
        u8* counter;

        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
        counter = &g_ScriptVarsReq.byte;
        (*counter) += 1;
        SCN_EFFECT->step = 9;
    }
}

MATCH void func_801F82B4(void) {
    if (g_Task->timer != 0) {
        func_801F8360();

        if (SCN_EFFECT->counter_0C < 0x80) {
            SCN_EFFECT->counter_0C += 4;
        }

        if (SCN_EFFECT->counter_10 < 0xB6) {
            SCN_EFFECT->counter_10 += 2;
        } else {
            SCN_EFFECT->counter_10 = 0xB6;
        }

        g_Task->timer--;
    } else {
        Actor_Clear();
    }
}

MATCH void func_801F8360(void) {
    MATRIX       matrix;
    SVECTOR      v0;
    SVECTOR      v1;
    SVECTOR      v2;
    SVECTOR      v3;
    SVECTOR      v4;
    SVECTOR      v5;
    long         depth;
    long         flag;
    s32          angle;
    s32          size;
    s32          v2x;
    s32          v2y;
    s16          i;
    s8           shade;
    SceneEffect* work;
    POLY_G3*     prim;

    work          = SCN_EFFECT;
    work->angle.z = (work->counter_09 << 12) / 360;
    angle         = work->counter_10;
    size          = work->counter_0C;

    v2x = (u32)(size * rcos(angle)) >> 8;
    v2y = (u32)(size * rsin(angle)) >> 8;

    v0.vx = 0;
    v0.vy = 0;
    v0.vz = 0;
    v1.vx = size << 4;
    v1.vy = 0;
    v1.vz = 0;
    v2.vx = v2x;
    v2.vy = v2y;
    v2.vz = 0;

    v2x = (u32)(size * rcos(172)) >> 8;
    v2y = (u32)(size * rsin(172)) >> 8;

    v3.vx = 0;
    v3.vy = 0;
    v3.vz = 0;
    v4.vx = size << 4;
    v4.vy = 0;
    v4.vz = 0;
    v5.vx = v2x;
    v5.vy = v2y;
    v5.vz = 0;

    i = 0;
    do {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        PushMatrix();
        func_8015B410(&matrix);
        func_8015B4B0(&matrix);
        if (i & 0x1) {
            RotTransPers3(&v0, &v1, &v2, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        } else {
            RotTransPers3(&v3, &v4, &v5, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        }
        shade = -(g_Task->timer << 1);
        setRGB0(prim, g_Task->tint.bytes.unk_5D, g_Task->tint.bytes.unk_5E, g_Task->tint.bytes.unk_5F);
        setRGB1(prim, shade, shade, shade);
        setRGB2(prim, shade, shade, shade);
        SetSemiTrans(prim, 1);
        GFX_AddPrim(g_Task->draw_layer, sizeof(POLY_G3));
        PopMatrix();
        i = i + 1;
        SCN_EFFECT->angle.z += 170;
    } while (i < 24);
}

/* The current scenario work object. The cell is a volatile pointer so every
 * read of it stays its own load, as in the shipped image. */

/* Scene_DrawTriangle saves the active effect's rotation across a triangle draw;
 * func_8015B410 passes the three angles to RotMatrix. */
typedef struct SceneRotation {
    Point3DL angle;
    s32      unk_0C; /* 0x0C */
} SceneRotation;

ASSERT_SIZE(SceneRotation, 0x10);
ASSERT_OFFSET(SceneRotation, angle, 0x00);

/* func_801F85A8 */
MATCH void Scene_DrawTriangle(s32 size, s32 angle_x, s32 angle_y, s32 angle_z) {
    MATRIX        matrix;
    SVECTOR       v0;
    SVECTOR       v1;
    SVECTOR       v2;
    SceneRotation saved;
    long          depth;
    long          flag;
    SceneEffect*  work;
    POLY_G3*      prim;
    s32           v2x;
    s32           v2y;

    saved         = *(SceneRotation*)&g_Task->unk_64;
    work          = SCN_EFFECT;
    work->angle.x = angle_x;
    work->angle.y = angle_y;
    work->angle.z = angle_z;

    v2x = (u32)(size * rcos(SCN_TRI_APEX_ANGLE)) >> 8;
    v2y = (u32)(size * rsin(SCN_TRI_APEX_ANGLE)) >> 8;

    prim = (POLY_G3*)g_GfxPrimCursor;

    v0.vx = 0;
    v0.vy = 0;
    v0.vz = 0;
    v1.vx = size << 4;
    v1.vy = 0;
    v1.vz = 0;
    v2.vx = v2x;
    v2.vy = v2y;
    v2.vz = 0;

    SetPolyG3(prim);
    PushMatrix();
    func_8015B410(&matrix);
    func_8015B4B0(&matrix);
    RotTransPers3(&v0, &v1, &v2, (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, SCN_TRI_SHADE_V0, SCN_TRI_SHADE_V0, SCN_TRI_SHADE_V0);
    setRGB1(prim, SCN_TRI_SHADE_V1, SCN_TRI_SHADE_V1, SCN_TRI_SHADE_V1);
    setRGB2(prim, SCN_TRI_SHADE_V2, SCN_TRI_SHADE_V2, SCN_TRI_SHADE_V2);
    SetSemiTrans(prim, 1);
    GFX_AddPrim(g_Task->draw_layer, sizeof(POLY_G3));
    PopMatrix();

    *(SceneRotation*)&g_Task->unk_64 = saved;
}

MATCH void func_801F8748(void) {
    D_801FC9D4[g_Task->header.mode]();
}

MATCH void func_801F878C(void) {
    SceneEffect* work;
    SceneEffect* tail;
    SceneEffect* late;

    work                    = SCN_EFFECT;
    FIELD(s16, work, 0x2Eu) = (D_80147A86 + D_801FC9E8);
    work->origin.y          = (D_80147A88 + D_801FC9E9);
    work->counter_09        = 0;
    SCN_EFFECT->channel_06  = 0x20;
    tail                    = SCN_EFFECT;
    *(s8*)&tail->color_b    = -0x80;
    *(s8*)&tail->color_g    = -0x80;
    *(s8*)&tail->color_r    = -0x80;
    func_801F8BCC();
    late       = SCN_EFFECT;
    late->step = late->channel_07;
}

MATCH void func_801F882C(void) {
    SceneEffect* work;
    SceneEffect* tail;
    s8           shade;

    work = SCN_EFFECT;
    work->origin.x -= 4;
    work->origin.y += D_801FC9EC[work->counter_09 >> 2];
    shade = *(s8*)&work->color_r;

    if (shade != 0) {
        work->color_r = shade - 2;
        tail          = SCN_EFFECT;
        tail->color_b -= 2;
        tail = SCN_EFFECT;
        tail->color_g -= 2;
        tail = SCN_EFFECT;
        tail->counter_09 += 1;
        tail = SCN_EFFECT;
        if ((tail->counter_09 & 0x3) == 0) {
            tail->channel_06 += 1;
        }
        func_801F8BCC();
    } else {
        Actor_Clear();
    }
}

MATCH void func_801F8930(void) {
    SceneEffect* work;
    SceneEffect* tail;
    s8           shade;

    work = SCN_EFFECT;
    work->origin.y -= 2;
    shade = *(s8*)&work->color_r;

    if (shade != 0) {
        work->color_r = shade - 4;
        tail          = SCN_EFFECT;
        tail->color_b -= 4;
        tail = SCN_EFFECT;
        tail->color_g -= 4;
        tail = SCN_EFFECT;
        if ((tail->counter_09 & 0x7) == 0) {
            tail->channel_06 += 1;
        }
        func_801F8BCC();
    } else {
        Actor_Clear();
    }
}

MATCH void func_801F89F0(void) {
    s32          deltas[3];
    SceneEffect* update_work;
    SceneEffect* setup_work;

    setup_work                    = SCN_EFFECT;
    VOL(s32, setup_work->pos.x)   = D_80147A8C;
    VOL(s32, setup_work->pos.y)   = g_AreaFocusY[0];
    FIELD(s32, setup_work, 0x3Cu) = D_80147A94;
    VOL(s32, setup_work->angle.x) = D_80147ABC;
    VOL(s32, setup_work->angle.y) = D_80147AC0;
    setup_work->angle.z           = D_80147AC4;
    func_801AC1DC(deltas, FIELD(u8, setup_work, 0x1Cu));
    update_work                     = SCN_EFFECT;
    update_work->pos.x              = (update_work->pos.x + deltas[0]);
    update_work->pos.y              = (update_work->pos.y + deltas[1]);
    update_work->pos.z.part.integer = (update_work->pos.z.part.integer + deltas[2]);
    update_work->step               = (update_work->step + 1);
}

MATCH void func_801F8AB8(void) {
    DVECTOR*     screen;
    SceneEffect* work;
    SceneEffect* tail;
    SceneEffect* current;
    s8           shade;
    s32          point[3];

    screen = (DVECTOR*)D_1F800034;
    work   = SCN_EFFECT;
    work->pos.z.part.integer += 0x20;
    point[0] = work->pos.x;
    point[1] = work->pos.y;
    point[2] = work->pos.z.fixed;
    Area_ProjectPoint(point, screen);

    current                     = SCN_EFFECT;
    VOL(u16, current->origin.x) = (u16)screen->vx;
    current->origin.y           = SP_REF(u16, 0x36u);
    shade                       = *(s8*)&current->color_r;

    if (shade != 0) {
        current->color_r = shade - 4;
        tail             = SCN_EFFECT;
        tail->color_b -= 4;
        tail = SCN_EFFECT;
        tail->color_g -= 4;
        tail = SCN_EFFECT;
        if ((tail->counter_09 & 0x7) == 0) {
            tail->channel_06 += 1;
        }
        func_801F8BCC();
    } else {
        Actor_Clear();
    }
}

MATCH void func_801F8BCC(void) {
    POLY_FT4* prim;
    u8        half;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    half = SCN_EFFECT->channel_06 >> 1;
    SetPolyFT4(prim);
    setXYWH(prim, SCN_EFFECT->origin.x - half, SCN_EFFECT->origin.y - half, SCN_EFFECT->channel_06, SCN_EFFECT->channel_06);
    setUVWH(prim, 0xE0, 0x30, 0x1F, 0x20);
    setRGB0(prim, SCN_EFFECT->color_r, SCN_EFFECT->color_g, SCN_EFFECT->color_b);
    setClut(prim, 160, STAGE_PALETTE_Y + 3);
    prim->tpage = GetTPage(0, 1, 704, 256);
    SetShadeTex(prim, 0);
    SetSemiTrans(prim, 1);
    if (g_AreaDrawFlags != 0) {
        GFX_AddPrim(3U, sizeof(POLY_FT4));
    }
}

MATCH void func_801F8D70(void) {
    func_801F8D90();
}

MATCH void func_801F8D90(void) {
    u8*          work;
    SceneEffect* work_cell;
    Actor*       first;
    Actor*       second;
    u8*          prim;
    POLY_FT4*    poly;
    s32          origin[3];
    SVECTOR      projection;
    long         depth;
    long         flag;

    work      = (u8*)g_Task;
    prim      = g_GfxPrimCursor;
    work_cell = (SceneEffect*)work;
    first     = (Actor*)(D_80147A58 + work_cell->counter_0C * 0x98);

    work_cell->pos.x       = first->pos.x.fixed;
    work_cell->pos.y       = first->pos.y.fixed;
    work_cell->pos.z.fixed = first->pos.z.fixed;
    g_GfxPrimCursor        = prim + 8;
    TASK_SET(first);
    ((RECT*)prim)->x = 0;
    ((RECT*)prim)->y = 240;
    setWH(((RECT*)prim), 16, 16);
    SetTexWindow((DR_TWIN*)(prim + 8), (RECT*)prim);
    Area_AddCellPrim(SPAD_ROW->pos.x.fixed, SPAD_ROW->pos.y.fixed, 0x11, 0x0C);

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);

    func_801AC1DC(origin, work[0x10]);

    projection.vx = ((origin[0] + SPAD_ROW->pos.x.fixed) >> 9) - 0x4000;
    projection.vy = ((origin[1] + SPAD_ROW->pos.y.fixed) >> 9) - 0x4000;
    projection.vz = -(origin[2] + COORD_INT(SPAD_ROW->pos.z)) / 2;

    work_cell->projected = RotTransPers(&projection, (long*)&poly->x0, &depth, &flag);

    poly->x1 = poly->x0 + 8;
    poly->x0 = poly->x0 - 8;
    poly->y1 = poly->y0;

    second = (Actor*)(D_80147A58 + work_cell->channel_18 * 0x98);
    TASK_SET(second);
    func_801AC1DC(origin, work[0x1C]);

    projection.vx = ((origin[0] + SPAD_ROW->pos.x.fixed) >> 9) - 0x4000;
    projection.vy = ((origin[1] + SPAD_ROW->pos.y.fixed) >> 9) - 0x4000;
    projection.vz = -(origin[2] + COORD_INT(SPAD_ROW->pos.z)) / 2;

    work_cell->projected = RotTransPers(&projection, (long*)&poly->x2, &depth, &flag);

    poly->x3 = poly->x2 + 8;
    poly->x2 = poly->x2 - 8;
    poly->y3 = poly->y2;
    g_Task   = work;

    setClut(poly, 176, STAGE_PALETTE_Y + 3);
    poly->tpage = GetTPage(0, 0, 704, 256);

    setUV4(poly, 0, (g_FrameCount >> 2) & 0x15, 16, (g_FrameCount >> 2) & 0x15, 0, ((g_FrameCount >> 2) & 0x15) + abs(poly->y2 - poly->y0), 16,
           ((g_FrameCount >> 2) & 0x15) + abs(poly->y2 - poly->y0));

    setRGB0(poly, 128, 128, 128);

    SetShadeTex(poly, 1);

    Area_AddCellPrim(SPAD_ROW->pos.x.fixed, SPAD_ROW->pos.y.fixed, 0x11, sizeof(POLY_FT4));

    prim             = g_GfxPrimCursor;
    g_GfxPrimCursor  = prim + 8;
    ((RECT*)prim)->x = 0;
    ((RECT*)prim)->y = 0;
    setWH(((RECT*)prim), 256, 256);
    SetTexWindow((DR_TWIN*)(prim + 8), (RECT*)prim);

    Area_AddCellPrim(SPAD_ROW->pos.x.fixed, SPAD_ROW->pos.y.fixed, 0x11, 0x0C);
}

MATCH void func_801F913C(void) {
    SYS_DISPATCH_BYTE(D_801FCA10, D_80146872);
}

MATCH void func_801F9178(void) {
    volatile u16* state;
    u8(*table)[4];
    u8 i;
    u8 j;

    func_801C1DF0(0);
    Game_RequestAreaChange(AREA_ID_DAUNA_MINE_WHELP, TO_COORD(99), TO_COORD(12), FACING_RIGHT);
    /* FAKE: place loop init early. */
    i                     = 0;
    state                 = &g_SaveAreaId;
    table                 = (u8(*)[4])((u8*)state + 0xC04);
    *state                = 0x18;
    g_SaveEntryX          = TO_COORD(99);
    g_SaveEntryY          = TO_COORD(12);
    g_SaveEntryFacing     = FACING_RIGHT;
    g_SceneState.state_04 = 5;
    g_SceneState.step_05  = 0;
    for (i = 0; i < 6; i++) {
        for (j = 0; j < 4; j++) {
            table[i][j] = 0xFF;
        }
    }
    for (i = 0; i < 12; i++) {
        for (j = 0; j < 4; j++) {
            D_80145518[i][j] = 0xFF;
        }
    }
    g_GameFlags |= GAME_FLAG_MENU_LOCK;
    while (EMI_IsReady() == 0) {
        CallbackWait(1U);
    }
    g_ScriptVarsReq.word = 0;
    D_80146872           = 1;
}

MATCH void func_801F92DC(void) {
    s32  actor_slot;
    s8   next_state;
    u16  selection;
    u16* state0;
    u16* state3;
    u8   slot;

    selection = g_GameAreaId;
    if (selection == 1) {
        func_801BE1B0(0U);
        if (g_ScriptVars[2] == 0) {
            slot        = Actor_FindFreeSlot();
            *D_1F800000 = slot;
            actor_slot  = slot & BYTE_MASK;
            if (actor_slot != GAME_NONE) {
                g_ActorSlots[actor_slot].header.flags = 1;
                g_ActorSlots[*D_1F800000].type        = 0x10;
                g_ActorSlots[*D_1F800000].counter_18  = 2;
                g_ActorSlots[*D_1F800000].counter_1C  = 2;
                g_ActorSlots[*D_1F800000].scene_step  = 3;
                g_ActorSlots[*D_1F800000].selection   = selection;
            }
            state0  = &g_AreaCameraAngle.vz;
            *state0 = *state0 - 0x155;
            goto block_7;
        }
        if (g_ScriptVars[2] == 3) {
            D_80147C38 = selection;
            D_80147C3C = 4;
            D_80147C21 = 7;
            state3     = &g_AreaCameraAngle.vz;
            *state3    = *state3 + 0x155;
        block_7:
            if (g_ScriptVars[2] != 3) {
                goto block_8;
            }
        } else {
        block_8:
            g_ScriptVars[2]      = 0;
            g_SceneState.step_05 = 0;
        }
        g_SceneState.state_04 = 0xA;
    }
    func_801F9644();
    if (g_GameAreaId == AREA_ID_DAUNA_MINE_INTRO) {
        if (SYS_TestFlag(g_SceneFlags, 0) == 0) {
            g_AreaDrawFlags = 0;
            SYS_SetFlag(g_SceneFlags, 0U);
            Game_SetScriptActive();
            g_SceneState.state_04 = 2;
        }
        if (D_80143F03 == 2) {
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Party_HideBattlers();
        }
    }
    func_801F9868();
    if (g_GameAreaId == AREA_ID_NO_TEXT_25) {
        D_801468A0 = 2;
        D_801468A4 = 2;
        D_80147BA0 = 1;
        D_80147BA4 = 3;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 0));
        g_SceneState.state_04 = 0xB;
        g_SceneState.timer_06 = 20;
        g_AreaDrawFlags       = 0;
    }
    if (g_GameAreaId == AREA_ID_TITLE_INTRO) {
        g_AreaCameraAngle.vx = 256;
        g_AreaCameraAngle.vz = 0;
        g_AreaCameraAngle.vy = 0;
        g_AreaCameraOffsetZ  = 0x100;
        if (SYS_TestFlag(g_SceneFlags, 1) == 0) {
            g_AreaDrawFlags = 0;
            SYS_SetFlag(g_SceneFlags, 1U);
            next_state = 3;
        } else {
            func_801BE1B0(0U);
            next_state = 9;
        }
        g_SceneState.state_04 = next_state;
    }
    D_80146872 = 2;
}

MATCH void func_801F9644(void) {
    s16* timer;
    s32  slot;
    u8   id;

    if (g_GameAreaId == AREA_ID_DAUNA_MINE_WORKER) {
        if (SYS_TestFlag(g_SceneFlags, 2) == 0) {
            g_ScriptVarsReq.word = 0;
            Area_AdvanceScroll(768);
            func_801C601C(0);
            timer       = &g_AreaCameraAngle.vx;
            *timer      = (*timer + 0xAA);
            id          = Actor_FindFreeSlot();
            slot        = id & BYTE_MASK;
            *D_1F800000 = id;
            if (slot != GAME_NONE) {
                g_ActorSlots[slot].header.flags            = 1;
                g_ActorSlots[D_1F800000[0]].type           = 0x13;
                g_ActorSlots[D_1F800000[0]].camera_angle.x = *timer - 170;
                g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000[0]].layer          = 0x40;
            }
            Party_HideBattlers();
            g_Game.members[0].pos.x.fixed = TO_COORD(51);
            g_Game.members[0].pos.y.fixed = TO_COORD(64);
            SYS_SetFlag(g_SceneFlags, 2U);
            return;
        }
        if (SYS_TestFlag(g_SceneFlags, 10) == 0) {
            SYS_SetFlag(g_SceneFlags, 10U);
            func_801BE1B0(0U);
            g_AreaScrollTargetX    = TO_COORD(38);
            g_AreaScrollTargetY[0] = TO_COORD(27) + COORD_HALF;
        }
    }
}

MATCH void func_801F9868(void) {
    s32 slot;
    u8  i;
    u8  free_slot;

    if (g_GameAreaId == AREA_ID_DAUNA_MINE_WHELP) {
        switch (D_80143F03) {
            case 1:
                if (SYS_TestFlag(g_SceneFlags, 3) == 0) {
                    SND_RequestBGM(3);
                loop_10:
                    if (EMI_IsReady() == 0) {
                        CallbackWait(1U);
                        goto loop_10;
                    }
                    g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                    g_ScriptVarsReq.word = 0;
                    SYS_SetFlag(g_SceneFlags, 3U);
                    Area_AdvanceScroll(1152);
                    g_AreaCameraOffsetZ  = 0x480;
                    g_AreaCameraAngle.vz = 848;
                    func_801BE1B0(0U);
                    func_801C601C(0);
                    free_slot   = Actor_FindFreeSlot();
                    slot        = free_slot & BYTE_MASK;
                    *D_1F800000 = free_slot;
                    if (slot != GAME_NONE) {
                        g_ActorSlots[slot].header.flags            = 1;
                        g_ActorSlots[D_1F800000[0]].type           = 0x13;
                        g_ActorSlots[D_1F800000[0]].camera_angle.x = g_AreaCameraAngle.vx;
                        g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                        g_ActorSlots[D_1F800000[0]].camera_angle.z = 512;
                        g_ActorSlots[D_1F800000[0]].layer          = 0x90;
                        return;
                    }
                } else {
                    u8* pal1;
                    u8* pal2;

                    i    = 0;
                    pal1 = MEM_PTR(u8, AREA_PALETTE_ARENA_33E00);
                    pal2 = MEM_PTR(u8, AREA_PALETTE_WORK + 0x600u);
                    for (; i < 16; i++) {
                        *((u16*)pal1 + i + 0x40) = *((u16*)pal1 + i + 0x50);
                        *((u16*)pal2 + i + 0x40) = *((u16*)pal2 + i + 0x50);
                    }
                    g_GfxPalettePending = 1;
                    if (SYS_TestFlag(g_SceneFlags, 5) == 0) {
                        g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                        g_ScriptVarsReq.word = 0;
                        func_801BE1B0(1U);
                        return;
                    }
                    Game_ClearScriptActive();
                    return;
                }
                break;
            case 0:
                g_ScriptVarsReq.word = 0;
                if (SYS_TestFlag(g_SceneFlags, 6) == 0) {
                    g_SceneState.state_04 = 8;
                    g_SceneState.step_05  = 0;
                }
                break;
            case 2:
                if (SYS_TestFlag(g_SceneFlags, 8) == 0) {
                    g_ScriptVarsReq.word  = 0;
                    g_SceneState.state_04 = 6;
                    g_SceneState.step_05  = 0;
                }
                break;
            case 4:
                if (SYS_TestFlag(g_SceneFlags, 9) == 0) {
                    g_ScriptVarsReq.word  = 0;
                    g_SceneState.state_04 = 6;
                    g_SceneState.step_05  = 0;
                }
                break;
        }
    }
}

MATCH void func_801F9B98(void) {
    SYS_DISPATCH_BYTE(D_801FCA1C, g_SceneState.state_04);
}

MATCH void func_801F9BD4(void) {
}

MATCH void func_801F9BDC(void) {
}

/* PsyQ master volume: the left and right channel levels (SPU_VOL_MAIN_L/R). */

MATCH void func_801F9BE4(void) {
    u16* counter;

    switch (g_SceneState.step_05) {
        case 0:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            SsSetMVol(0, 0);
            Message_StartAreaMessage(16);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            SND_PlayBGM(6, 0x5A, 8);
            g_SceneState.timer_06 = 0;
            g_SceneState.step_05  = 1;
            g_GameFlags |= 0x80;
            break;

        case 1:
            counter = &g_SceneState.timer_06;
            SsSetMVol(*counter, *counter);
            if (*counter < 124) {
                *counter = *counter + 1;
            }
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            SsSetMVol(0x7F, 0x7F);
            g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
            Game_SetScriptActive();
            Party_HideBattlers();
            UI_SetMode(UI_MODE_FADE_IN);
            g_ScriptVars[3]      = 1;
            *counter             = 0;
            g_SceneState.step_05 = 2;
            break;

        case 2:
            if (g_ScriptVars[3] != 0x54) {
                break;
            }
            UI_SetMode(UI_MODE_FADE_OUT);
            g_SceneState.step_05 = 3;
            break;

        case 3:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(17);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 4;
            break;

        case 4:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_INTRO, TO_COORD(68), TO_COORD(8), FACING_DOWN);
            g_SceneState.step_05 = 5;
            break;

        case 5:
            if (D_80143F03 != 2) {
                break;
            }
            g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
            g_SceneState.step_05 = 6;
            break;

        case 6:
            if (g_ScriptVars[2] != 0x23) {
                break;
            }
            D_1F800000[0] = Actor_FindFreeSlot();
            if ((D_1F800000[0] & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[D_1F800000[0]].header.flags   = 1;
                g_ActorSlots[D_1F800000[0]].type           = 0x13;
                g_ActorSlots[D_1F800000[0]].camera_angle.x = g_AreaCameraAngle.vx + 384;
                g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000[0]].layer          = 0x60;
            }
            g_SceneState.step_05 = 7;
            break;

        case 7:
            if (g_ScriptVars[3] != 0x60) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_TITLE_INTRO, TO_COORD(7), TO_COORD(20), FACING_UP_LEFT);
            g_GameRequestKind = 0xFF;
            SND_FadeOutBGM(6, 0x5A, 0x40);
            g_SceneState.state_04 = 3;
            g_SceneState.step_05  = 0;
            break;
    }
}

MATCH void func_801F9FB8(void) {
    u8* state;
    u8  id;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (g_ScriptVars[2] == 0x30) {
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                UI_SetMode(UI_MODE_FADE_IN);
                id            = Actor_FindFreeSlot();
                D_1F800000[0] = id;
                if ((id & BYTE_MASK) != GAME_NONE) {
                    g_ActorSlots[id].header.flags              = 1;
                    g_ActorSlots[D_1F800000[0]].type           = 0x13;
                    g_ActorSlots[D_1F800000[0]].camera_angle.x = g_AreaCameraAngle.vx + 448;
                    g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                    g_ActorSlots[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                    g_ActorSlots[D_1F800000[0]].layer          = 0xFF;
                }
                *state = 1;
            }
            break;

        case 1:
            if (g_ScriptVars[2] == 0x35) {
                *state = 2;
            } else if (g_AreaCameraY == 0x4400) {
                g_AreaCameraY = 0x6200;
                g_AreaTileOriginY -= 0x1E;
                g_AreaScrollTargetY[0] += TO_COORD(-30);
                g_AreaFocusY[0] += TO_COORD(-30);
                g_PartyY[0] += TO_COORD(-30);
                Area_RefreshCellGrid();
            }
            break;

        case 2:
            g_ScriptVars[2] = 0x37;
            *state          = 3;
            break;

        case 3:
            if (g_ScriptVars[2] == 0x38) {
                SND_PlayBGM(2, 0x64, 0x20);
                Game_RequestAreaChange(AREA_ID_DAUNA_MINE_WORKER, TO_COORD(52), TO_COORD(67), FACING_RIGHT);
                g_SceneState.state_04 = 4;
                *state                = 0;
            }
            break;
    }
}

MATCH void func_801FA27C(void) {
    u8 id;

    switch (g_SceneState.step_05) {
        case 0:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            Message_StartAreaMessage(1);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 1;
            break;

        case 1:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            g_SceneState.step_05 = 2;
            break;

        case 2:
            if (g_ScriptVarsReq.byte != 3) {
                break;
            }
            Message_StartAreaMessage(2);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 3;
            break;

        case 3:
            if (g_ScriptVarsReq.byte != 4) {
                break;
            }
            Message_StartAreaMessage(3);
            g_GameStateIndex      = GAME_REQUEST_MESSAGE;
            g_SceneState.timer_06 = 304;
            g_SceneState.step_05  = 4;
            break;
        case 4: {
            u16* counter;
            u16  count;

            counter = &g_SceneState.timer_06;
            count   = *counter;
            if (count != 0) {
                count--;
                *counter            = count;
                g_AreaCameraOffsetZ = (((304 - count) * 0x57943u) >> 16);
                break;
            }
            g_SceneState.step_05 = 5;
            break;
        }

        case 5:
            if (g_ScriptVarsReq.byte != 5) {
                break;
            }
            id            = Actor_FindFreeSlot();
            D_1F800000[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags              = 1;
                g_ActorSlots[D_1F800000[0]].type           = 0x13;
                g_ActorSlots[D_1F800000[0]].camera_angle.x = -842;
                g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000[0]].layer          = 0x60;
            }
            g_SceneState.step_05 = 6;
            break;

        case 6:
            if (g_ScriptVarsReq.byte != 8) {
                break;
            }
            id            = Actor_FindFreeSlot();
            D_1F800000[0] = id;
            if ((id & BYTE_MASK) != GAME_NONE) {
                g_ActorSlots[id].header.flags              = 1;
                g_ActorSlots[D_1F800000[0]].type           = 0x13;
                g_ActorSlots[D_1F800000[0]].camera_angle.x = -684;
                g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                g_ActorSlots[D_1F800000[0]].camera_angle.z = g_AreaCameraAngle.vz;
                g_ActorSlots[D_1F800000[0]].layer          = 0x20;
            }
            g_SceneState.timer_06 = 512;
            g_SceneState.step_05  = 7;
            break;

        case 7: {
            u16* counter;

            counter = &g_SceneState.timer_06;
            if (*counter != 0) {
                g_AreaCameraOffsetZ = ((*counter * 0xDu) >> 2);
                (*counter)--;
                break;
            }
            g_SceneState.step_05 = 8;
            break;
        }

        case 8:
            if (g_ScriptVarsReq.byte != 0xB) {
                break;
            }
            UI_SetMode(UI_MODE_FADE_OUT);
            g_SceneState.step_05 = 9;
            break;

        case 9:
            if (WINDOW_EFFECT_BUSY()) {
                break;
            }
            g_AreaDrawFlags = 0;
            Message_StartAreaMessage(4);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            SND_FadeOutBGM(2, 0x64, 0x20);
            g_SceneState.step_05 = 0xA;
            break;

        case 10:
            if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
                break;
            }
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_WHELP, TO_COORD(99), TO_COORD(12), FACING_RIGHT);
            g_SceneState.state_04 = 5;
            g_SceneState.step_05  = 0;
            break;
    }
}

MATCH void func_801FA7D8(void) {
    u32  bit;
    u8   id;
    u8   value;
    u16* accum;
    s32  distance;
    s32  delta;

    if (((g_SceneState.step_05 - 4) < 3U) && ((g_FrameCount & 0xFu) == 0u)) {
        bit             = (1 << (RANDOM_MOD(3)));
        g_ScriptVars[3] = bit;
        if ((bit & BYTE_MASK) >= 2u) {
            D_80146866 += 0x10;
        }
    }

    switch (g_SceneState.step_05) {
        case 0:
            g_GameFlags |= 0x80u;
            SYS_SetFlag(g_SceneFlags, 0u);
            SYS_SetFlag(g_SceneFlags, 1u);
            SYS_SetFlag(g_SceneFlags, 2u);
            SYS_SetFlag(g_SceneFlags, 3u);
            g_SceneState.timer_06 = 0x90u;
            g_SceneState.step_05  = 1u;
            return;

        case 1:
        case 2: {
            u16* counter;

            counter = &g_SceneState.timer_06;
            if (*counter != 0u) {
                g_AreaCameraOffsetZ = ((u32)*counter << 0x13 >> 0x10);
                (*counter)--;
                return;
            }
            g_AreaCameraRefreshCount = 2u;
            g_AreaCameraOffsetZ      = 0u;
            g_SceneState.step_05     = 3u;
            return;
        }

        case 3:
            if (g_ScriptVarsReq.byte == 0xCu) {
                g_SceneState.timer_06 = 0x3Cu;
                g_SceneState.step_05  = 4u;
                D_80146866            = 0u;
            }
            break;

        case 4: {
            u16* counter;
            u8*  fade;

            counter = &g_SceneState.timer_06;
            if (*counter != 0u) {
                (*counter)--;
            } else {
                u8* scene;

                g_SceneState.step_05 = 5u;
                scene                = &g_ScriptVarsReq.byte;
                (*scene)++;
            }
            fade = &D_80146866;
            if (*fade == 0u) {
                break;
            }
            /* FAKE: table load after the fade decrement. */
            FAKE_ORDER_LOCK(value = D_801FCA4C[g_FrameCount & 0xFu]);
            (*fade)--;
            accum = &D_80147A96;
            goto accumulate;
        }

        case 5: {
            /* FAKE: index copy stays in v0 across the schedule wall. */
            FAKE_REG(s32, index_raw, "v0");

            if (g_ScriptVarsReq.byte == 0x11u) {
                g_SceneState.timer_06 = 0x3Cu;
                g_SceneState.step_05  = 6u;
            }
            if (D_80146866 == 0u) {
                break;
            }
            /* FAKE: the index read gets its own statement and is locked, so the scheduler cannot hoist the accum
               address above it. */
            /* FAKE: the lock holds the retail load order around the index read. */
            FAKE_ORDER_LOCK(index_raw = g_FrameCount);
            accum      = &D_80147A96;
            D_80146866 = (D_80146866 - 1u);
            /* FAKE: the barrier is the schedule wall after the fade store. */
            FAKE_BARRIER();
            value = D_801FCA4C[index_raw & 0xFu];
        }
        accumulate:
            {
                u16 acc;

                /* FAKE: accumulate load before the shift. */
                FAKE_ORDER_LOCK(acc = *accum);
                delta  = (value << 0x18);
                *accum = (acc + (delta >> 0x16));
                return;
            }

        case 6: {
            u16* counter;
            u8*  scene;

            counter = &g_SceneState.timer_06;
            if (*counter != 0u) {
                (*counter)--;
                return;
            }
            id            = Actor_FindFreeSlot();
            D_1F800000[0] = id;
            if (id != 0xFFu) {
                g_ActorSlots[D_1F800000[0]].header.flags = 1;
                g_ActorSlots[D_1F800000[0]].type         = 0x1Eu;
                g_ActorSlots[D_1F800000[0]].pos.x.fixed  = g_Game.members[0].pos.x.fixed;
                g_ActorSlots[D_1F800000[0]].pos.y.fixed  = g_Game.members[0].pos.y.fixed;
                distance                                 = Area_SampleHeight(g_ActorSlots[D_1F800000[0]].pos.x.fixed, g_ActorSlots[D_1F800000[0]].pos.y.fixed) << 16;
                g_ActorSlots[D_1F800000[0]].pos.z.fixed  = distance;
                g_ActorSlots[D_1F800000[0]].unk_29       = 0;
            }
            *counter             = 0x84u;
            g_SceneState.step_05 = 7u;
            scene                = &g_ScriptVarsReq.byte;
            (*scene)++;
            return;
        }

        case 7: {
            u16* counter;

            counter = &g_SceneState.timer_06;
            (*counter)--;
            if (*counter == 32u) {
                UI_SetMode(8u);
                g_SceneState.step_05 = 8u;
                return;
            }
            break;
        }

        case 8: {
            u16* counter;

            counter = &g_SceneState.timer_06;
            if (*counter != 0u) {
                (*counter)--;
                if (WINDOW_EFFECT_IDLE()) {
                    g_AreaDrawFlags = 0u;
                    return;
                }
            } else {
                g_ScriptVarsReq.byte = 0x14u;
                *counter             = 0x40u;
                g_SceneState.step_05 = 0xAu;
                return;
            }
            break;
        }

        case 9:
            if (g_ScriptVarsReq.byte == 0x14u) {
                func_80164020(0u, 1u);
                g_SceneState.timer_06 = 0x25Cu;
                g_SceneState.step_05  = 0xAu;
                return;
            }
            break;

        case 10: {
            u16* counter;

            counter = &g_SceneState.timer_06;
            if (*counter != 0u) {
                (*counter)--;
                return;
            }
            SYS_SetFlag(g_SceneFlags, 4u);
            Game_RequestAreaChange(AREA_ID_DAUNA_MINE_WHELP, TO_COORD(99), TO_COORD(17), FACING_RIGHT);
            g_GameRequestKind    = 9u;
            g_GameEntryMode      = 0xFFu;
            g_SceneState.step_05 = 0xBu;
            return;
        }

        case 11:
            if (WINDOW_EFFECT_IDLE()) {
                g_ScriptVarsReq.byte = 1u;
                g_SceneState.step_05 = 0xCu;
                return;
            }
            break;

        case 12:
            if ((g_ScriptVarsReq.byte == 4u) && (EMI_IsReady() != 0)) {
                SND_PlayBGM(3u, 0x69, 8);
                g_SceneState.step_05 = 0xDu;
                return;
            }
            break;

        case 13:
            if (g_ScriptVarsReq.byte == 5u) {
                g_SceneState.timer_06 = 0x20u;
                g_SceneState.step_05  = 0xEu;
                return;
            }
            break;

        case 14: {
            u16* counter;
            u16  count;
            s32* pos;

            counter = &g_SceneState.timer_06;
            count   = *counter;
            if (count != 0u) {
                pos = &D_801469EC;
                *pos += (s8)D_801FCA4C[count & 0xFu] << 11;
                delta    = (((s8)D_801FCA4C[count & 0xFu])) << 11;
                *counter = (count - 1u);
                D_801469F0 -= delta;
                return;
            }
            g_SceneState.step_05 = 0xFu;
            return;
        }

        case 15:
            if (g_ScriptVarsReq.byte == 7u) {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 1u);
                Battle_StartScripted(1u);
                SYS_SetFlag(g_SceneFlags, 5u);
                g_SceneState.step_05 = 0x10u;
                return;
            }
            break;

        case 17: {
            u8* scene;

            scene = &g_ScriptVarsReq.byte;
            (*scene)++;
            Game_ClearScriptActive();
            func_801BE1B0(6u);
            g_SceneState.state_04 = 0u;
            g_SceneState.step_05  = 0u;
            break;
        }

        default:
            break;
    }
}

MATCH void func_801FAF6C(void) {
    switch (g_SceneState.step_05) {
        case 0:
            g_SceneState.step_05 = D_801FCA5C[D_80143F03];
            break;

        case 10:
            Game_SetScriptActive();
            func_801BE1B0(3);
            SYS_SetFlag(g_SceneFlags, 7);
            g_SceneState.step_05 = 0xB;
            break;

        case 11:
            if (g_ScriptVarsReq.byte == 0xB) {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 4);
                Battle_StartScripted(4);
                g_SceneState.step_05 = 0xC;
            }
            break;

        case 13:
            g_ScriptVarsReq.byte++;
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            break;

        case 20:
            if (D_80145E91[0] != 2) {
                Game_SetScriptActive();
                func_801BE1B0(4);
                SYS_SetFlag(g_SceneFlags, 8);
                g_SceneState.step_05 = 0x15;
            }
            break;

        case 21:
            if (g_ScriptVarsReq.byte == 5) {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 5);
                Battle_StartScripted(5);
                g_SceneState.step_05 = 0x16;
            }
            break;

        case 30:
            if (D_80145E91[0] != 2) {
                Game_SetScriptActive();
                func_801BE1B0(5);
                SYS_SetFlag(g_SceneFlags, 9);
                g_SceneState.step_05 = 0x1F;
            }
            break;

        case 31:
            if (g_ScriptVarsReq.byte == 4) {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 6);
                Battle_StartScripted(6);
                g_SceneState.step_05 = 0x20;
            }
            break;

        case 23:
        case 33:
            Game_ClearScriptActive();
            g_SceneState.step_05  = 0;
            g_SceneState.state_04 = 0;
            g_ScriptVarsReq.byte++;
            break;

        case 50:
            Game_RequestAreaChange(AREA_ID_TITLE_INTRO, TO_COORD(4), TO_COORD(36), FACING_UP);
            g_GamePrevSelection   = 4;
            g_SceneState.state_04 = 0;
            g_SceneState.step_05  = 0;
            break;
    }
}

MATCH void func_801FB204(void) {
    u8 slot;

    switch (g_SceneState.step_05) {
        case 0:
            g_ScriptVarsReq.byte = 0xA;
            func_801BE1B0(1);
            func_801C601C(1);
            g_SceneState.step_05 = 1;
            break;

        case 1:
            if (g_ScriptVarsReq.byte == 0xD) {
                func_801BFE34(g_Game.members[0].pos.x.fixed, g_Game.members[0].pos.y.fixed, 7);
                Battle_StartScripted(7);
                g_SceneState.step_05 = 2;
            }
            break;

        case 2:
            break;

        case 3:
            g_GameFlags |= 0x180;
            Message_StartAreaMessage(14);
            g_GameStateIndex     = GAME_REQUEST_MESSAGE;
            g_SceneState.step_05 = 4;
            break;

        case 4:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                g_ScriptVarsReq.byte = 0x1E;
                g_AreaDrawFlags      = AREA_DRAW_ALL_FLAGS;
                UI_SetMode(UI_MODE_FAST_FADE_IN);
                g_PartyX               = TO_COORD(47);
                g_AreaScrollTargetX    = TO_COORD(47);
                g_PartyY[0]            = TO_COORD(29);
                g_AreaScrollTargetY[0] = TO_COORD(29);
                func_80153DE8();
                D_80143F84.raw = TO_COORD(1408);
                Area_AdvanceScroll(1408);
                g_AreaCameraAngle.vx  = -778;
                g_AreaCameraAngle.vz  = 384;
                g_AreaCameraOffsetZ   = 0x480;
                g_SceneState.timer_06 = 30;
                g_SceneState.step_05  = 5;
            }
            break;

        case 5: {
            u16* countdown;

            if (WINDOW_EFFECT_IDLE()) {
                countdown = &g_SceneState.timer_06;
                if (TIMER_EXPIRED(*countdown)) {
                    func_801C601C(2);
                    D_80143F84.raw = TO_COORD(1408);
                    Area_AdvanceScroll(D_80143F84.half[1]);
                    slot          = Actor_FindFreeSlot();
                    D_1F800000[0] = slot;
                    if ((slot & BYTE_MASK) != GAME_NONE) {
                        g_ActorSlots[slot].header.flags            = 1;
                        g_ActorSlots[D_1F800000[0]].type           = 0x13;
                        g_ActorSlots[D_1F800000[0]].camera_angle.x = -682;
                        g_ActorSlots[D_1F800000[0]].camera_angle.y = g_AreaCameraAngle.vy;
                        g_ActorSlots[D_1F800000[0]].camera_angle.z = 512;
                        g_ActorSlots[D_1F800000[0]].layer          = 0x20;
                    }
                    *countdown           = 0x20;
                    g_SceneState.step_05 = 6;
                }
            }
            break;
        }

        case 6: {
            u16* countdown;

            countdown = &g_SceneState.timer_06;
            if (*countdown != 0) {
                (*countdown)--;
                g_AreaCameraOffsetZ -= 0x24;
            } else {
                g_SceneState.step_05 = 7;
                g_ScriptVarsReq.byte++;
            }
            break;
        }

        case 7:
            if (g_ScriptVarsReq.byte == 0x24) {
                SND_PlayBGM(4, 0x69, 8);
                g_SceneState.step_05 = 8;
            }
            break;

        case 8:
            if (g_ScriptVarsReq.byte == 0x25) {
                Game_RequestAreaChange(AREA_ID_TITLE_INTRO, TO_COORD(4), TO_COORD(36), FACING_UP);
                g_SceneState.state_04 = 0;
                g_SceneState.step_05  = 0;
            }
            break;
    }
}

MATCH void func_801FB620(void) {
    volatile u8* state;

    state = &g_SceneState.step_05;
    if (*state == 0) {
        SYS_SetFlag(g_SceneFlags, 6);
        func_801BE1B0(2);
        g_SceneState.state_04 = 0;
        *state                = 0;
    }
}

MATCH void func_801FB67C(void) {
    u8* state;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (g_ScriptVars[2] == 0x71) {
                g_SceneState.timer_06 = 60;
                *state                = 2;
            }
            break;
        case 2:
            if (g_SceneState.timer_06 != 0) {
                g_SceneState.timer_06--;
            } else {
                Game_RequestAreaChange(AREA_ID_DAUNA_MINE_ADULT, TO_COORD(15), TO_COORD(33), FACING_UP);
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 6));
                g_ScriptVarsReq.word  = 0;
                *state                = 0;
                g_SceneState.state_04 = 0xA;
            }
            break;
    }
}

/* Scene angle interpolation: turns the scene angle g_AreaCameraAngle.vz to `degrees`,
 * spreading the turn over `duration` times the route's base frame count;
 * returns nonzero until it completes. */

MATCH void func_801FB744(void) {
    u8* state;

    state = &g_SceneState.step_05;
    switch (*state) {
        case 0:
            if (Area_StepCameraAngle(0x2D, 0xA) == 0) {
                g_SceneState.timer_06 = 50;
                *state                = 1;
            }
            break;

        case 1: {
            u8* request;

            request = &g_ScriptVars[2];
            if (*request & 0x1) {
                D_80147C54 = ((RANDOM_MASK(7) - 3) << 0xA) + (TO_COORD(26) + COORD_HALF);
                D_80147C58 = ((RANDOM_MASK(7) - 3) << 0xA) + (TO_COORD(21) + COORD_HALF);
            }
            if (*request == 3) {
                if (g_SceneState.timer_06 != 0) {
                    g_SceneState.timer_06--;
                } else {
                    Game_RequestAreaChange(AREA_ID_DAUNA_MINE_ADULT, TO_COORD(26), TO_COORD(22), FACING_UP);
                    *state = 2;
                }
            }
            break;
        }

        case 2:
            if (Area_StepCameraAngle(0xF, 0xA) == 0) {
                *state          = 3;
                g_ScriptVars[2] = 4;
            }
            break;

        case 3:
            if (g_ScriptVars[2] == 9) {
                g_GameFlags &= 0xFF7F;
                Game_RequestAreaChange(AREA_ID_NO_TEXT_25, TO_COORD(11) + COORD_HALF, TO_COORD(90), FACING_UP);
                g_SceneState.state_04 = 0xB;
                g_SceneState.timer_06 = 600;
                *state                = 0;
            }
            break;
    }
}

/* Advances the scena00 transition sequence, handling input, camera state and audio cues. */
MATCH void func_801FB924(void) {
    u16* counter;
    /* FAKE: keep the g_Game.members[0].unk_24 address for its masked load/store. */
    u8*  flags;
    /* FAKE: hold the g_PartyY base before g_AreaFocusY. */
    u32* base;

    if ((g_FrameCount & 0x1F) == 0) {
        g_ScriptVars[3] = RANDOM_MASK(0x7);
    }

    if (g_ScriptVars[2] < 0x14 && g_AreaCameraY == 0x5000) {
        g_AreaCameraY = 0x3000;
        g_AreaTileOriginY += 0x20;
        g_AreaScrollTargetY[0] += TO_COORD(32);
        base = g_PartyY;
        g_AreaFocusY[0] += TO_COORD(32);
        /* FAKE: barrier keeps the D_80147B28 load after the g_AreaFocusY store. */
        FAKE_BARRIER();
        D_80147B28 += TO_COORD(32);
        base[0] += TO_COORD(32);
        Area_RefreshCellGrid();
    }

    switch (g_SceneState.step_05) {
        case 0:
            counter = &g_SceneState.timer_06;
            if (TIMER_EXPIRED(*counter)) {
                g_ScriptVars[2] = 0x10;
                g_AreaDrawFlags = AREA_DRAW_ALL_FLAGS;
                UI_SetMode(UI_MODE_FADE_IN);
                SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
                *counter             = 60;
                g_SceneState.step_05 = 3;
            }
            break;

        case 1:
        case 2:
            break;

        case 3: {
            u16* counter;

            counter = &g_SceneState.timer_06;
            if (*counter != 0) {
                (*counter)--;
            } else {
                g_ScriptVars[2]      = 0x11;
                g_SceneState.step_05 = 4;
                *counter             = 900;
            }
            break;
        }

        case 4: {
            u16 buttons;

            counter = &g_SceneState.timer_06;
            buttons = g_InputPressed;
            (*counter)--;
            if ((buttons & INPUT_DIRECTIONAL) != 0 || *counter == 0) {
                g_ScriptVars[1]      = 0;
                g_ScriptVarsReq.byte = 0;
                g_ScriptVars[2]      = 0x12;
                func_801FBE88();
                *counter             = 900;
                g_SceneState.step_05 = 5;
            }
            break;
        }

        case 5: {
            u32  index;
            /* FAKE: keep the countdown address live only across its decrement/store. */
            u16* timer;

            if (D_80147BEC[0] != 0 || D_80147BF0[0] != 0) {
                D_80147BEC[0] = 0;
                D_80147BF0[0] = 0;
            }
            counter = &g_InputPressed;
            if ((*counter & INPUT_DIRECTIONAL) != 0) {
                g_ScriptVarsReq.byte = 0;
                g_ScriptVars[1]++;
                func_801FBE88();
                index = *counter >> 12;
                if (D_801FCA64[index * 2] != 0) {
                    TASK_SET((u8*)g_Actors);
                    D_80146890 = D_801FCA65[index * 2];
                    Actor_RequestScript(D_80146890);
                }
            } else {
                g_ScriptVarsReq.byte++;
                if (g_ScriptVarsReq.byte >= 21) {
                    g_ScriptVars[1]      = 0;
                    g_ScriptVarsReq.byte = 0;
                }
            }
            if (g_ScriptVars[1] >= 31) {
                g_ScriptVars[2]       = 0x13;
                g_SceneState.step_05  = 6;
                g_SceneState.timer_06 = 0;
            }
            timer = &g_SceneState.timer_06;
            if (TIMER_EXPIRED(*timer)) {
                g_ScriptVars[2]      = 0x13;
                g_SceneState.step_05 = 6;
            }
            break;
        }

        case 6: {
            s16* camera;
            /* FAKE: keep magnitude for the index and signed step. */
            s16  magnitude;
            s32* counter;

            D_1F800010                = (s16*)(((AreaLoad*)g_AreaLoads[g_GameAreaId])->unk_0C + 0x12);
            D_1F800010[0]             = RANDOM_MASK(0x7) - 3;
            D_1F800010[magnitude = 1] = RANDOM_MASK(0x7) - 3;
            camera                    = D_1F800010;
            magnitude                 = 0x40;
            counter                   = D_80147BEC;
            counter[0]                = (camera[0] >= 0) ? 0x40 : -magnitude;
            counter[1]                = (camera[1] >= 0) ? 0x40 : -magnitude;
            if ((g_FrameCount & 0x3) == 0) {
                TASK_SET((u8*)g_Actors);
                D_80146890 = (D_80146890 + 1) & 0x3;
                Actor_RequestScript(D_80146890);
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
            if (g_ScriptVars[2] == 0x15) {
                counter[0]           = 0;
                counter[1]           = 0;
                g_SceneState.step_05 = 7;
            }
            break;
        }

        case 7:
            if (g_ScriptVars[2] == 0x17) {
                g_SceneState.step_05 = 8;
            }
            break;

        case 8:
            UI_SetMode(UI_MODE_FADE_OUT);
            g_SceneState.step_05 = 9;
            break;

        case 9:
            if (WINDOW_EFFECT_IDLE()) {
                g_AreaDrawFlags = 0;
                flags           = &g_Game.members[0].unk_24;
                g_Game.flags &= ~(GAME_FLAG_SCROLL_LOCK | GAME_FLAG_MENU_LOCK);
                *flags &= 0xDF;
                Game_RequestAreaChange(AREA_ID_CEDAR_WOODS_BEFORE_NUE, TO_COORD(87), TO_COORD(4), FACING_LEFT);
                Scene_RequestChapterAdvance();
            }
            break;
    }
}

/* Current selection id: the index into the world-entry pointer table
 * g_AreaLoads. */

/* Scratchpad camera pointer cell, re-read on every use. */

MATCH void func_801FBE88(void) {
    u16* pad;

    pad           = &g_InputPressed;
    D_1F800010    = (s16*)(((AreaLoad*)g_AreaLoads[g_GameAreaId])->unk_0C + 0x12);
    D_1F800010[0] = 0;
    if ((*pad & PADLright) != 0u) {
        D_1F800010[0] += 2;
        D_80147BEC[0] += 0x40;
    }
    if ((*pad & PADLleft) != 0u) {
        D_1F800010[0] -= 2;
        D_80147BEC[0] -= 0x40;
    }
    D_1F800010[1] = 0;
    if ((*pad & PADLdown) != 0u) {
        D_1F800010[1] += 2;
        D_80147BF0[0] += 0x40;
    }
    if ((*pad & PADLup) != 0u) {
        D_1F800010[1] -= 2;
        D_80147BF0[0] -= 0x40;
    }
    SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 4));
}

MATCH void func_801FC01C(void) {
    SceneSampleRecord* rec;
    u8*                base;
    s8                 i;
    s32                shift;
    s32                lifetime;
    s32                slot;

    base = D_80147BD8;
    i    = 0;
    if (*D_80147BDC > 0) {
        do {
            shift                                    = 0xB - RANDOM_MASK(3);
            slot                                     = i * sizeof(SceneFxSlot);
            rec                                      = (SceneSampleRecord*)(i * sizeof(SceneSampleRecord) + (s32)base);
            SCENE_FX_CELL(g_SceneFx.accum, slot, 0)  = rec->sample[0] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 0)  = rec->weight[0] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 1)  = rec->sample[1] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 1)  = rec->weight[1] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 2)  = rec->sample[2] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 2)  = rec->weight[2] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 3)  = rec->sample[3] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 3)  = rec->weight[0] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 4)  = rec->sample[4] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 4)  = rec->weight[1] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 5)  = rec->sample[5] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 5)  = rec->weight[2] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 6)  = rec->sample[6] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 6)  = rec->weight[0] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 7)  = rec->sample[7] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 7)  = rec->weight[1] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 8)  = rec->sample[8] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 8)  = rec->weight[2] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 9)  = rec->sample[9] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 9)  = rec->weight[0] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 10) = rec->sample[10] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 10) = rec->weight[1] << shift;
            SCENE_FX_CELL(g_SceneFx.accum, slot, 11) = rec->sample[11] << 16;
            SCENE_FX_CELL(g_SceneFx.delta, slot, 11) = rec->weight[2] << shift;

            lifetime                                     = RANDOM_MASK(7) + 1;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 0)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 1)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 2)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 3)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 4)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 5)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 6)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 7)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 8)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 9)  = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 10) = lifetime;
            SCENE_FX_CELL(g_SceneFx.life_step, slot, 11) = lifetime;
            i++;
        } while (i < *D_80147BDC);
    }
}

typedef struct SceneLifeRecord {
    u8  unk_00[2];
    u16 lifetime[SCENE_FX_CELL_COUNT];
    u8  unk_1A[0x0E];
} SceneLifeRecord;

MATCH void func_801FC3A0(void) {
    SceneSampleRecord* rec;
    SceneLifeRecord*   dst;
    u8*                src_base;
    u8*                dst_base;
    s8                 i;

    src_base = D_80147BD8;
    dst_base = D_80147AA8;
    i        = 0;
    if ((*D_80147BDC) > 0) {
        do {
            rec = (SceneSampleRecord*)(i * sizeof(SceneSampleRecord) + ((s32)src_base));
            dst = (SceneLifeRecord*)(i * sizeof(SceneLifeRecord) + ((s32)dst_base));

            g_SceneFx.accum[i].cell[0] += g_SceneFx.delta[i].cell[0];
            rec->sample[0] = g_SceneFx.accum[i].cell[0] >> 16;
            g_SceneFx.accum[i].cell[1] += g_SceneFx.delta[i].cell[1];
            rec->sample[1] = g_SceneFx.accum[i].cell[1] >> 16;
            g_SceneFx.accum[i].cell[2] += g_SceneFx.delta[i].cell[2];
            rec->sample[2] = g_SceneFx.accum[i].cell[2] >> 16;
            g_SceneFx.accum[i].cell[3] += g_SceneFx.delta[i].cell[3];
            rec->sample[3] = g_SceneFx.accum[i].cell[3] >> 16;
            g_SceneFx.accum[i].cell[4] += g_SceneFx.delta[i].cell[4];
            rec->sample[4] = g_SceneFx.accum[i].cell[4] >> 16;
            g_SceneFx.accum[i].cell[5] += g_SceneFx.delta[i].cell[5];
            rec->sample[5] = g_SceneFx.accum[i].cell[5] >> 16;
            g_SceneFx.accum[i].cell[6] += g_SceneFx.delta[i].cell[6];
            rec->sample[6] = g_SceneFx.accum[i].cell[6] >> 16;
            g_SceneFx.accum[i].cell[7] += g_SceneFx.delta[i].cell[7];
            rec->sample[7] = g_SceneFx.accum[i].cell[7] >> 16;
            g_SceneFx.accum[i].cell[8] += g_SceneFx.delta[i].cell[8];
            rec->sample[8] = g_SceneFx.accum[i].cell[8] >> 16;
            g_SceneFx.accum[i].cell[9] += g_SceneFx.delta[i].cell[9];
            rec->sample[9] = g_SceneFx.accum[i].cell[9] >> 16;
            g_SceneFx.accum[i].cell[10] += g_SceneFx.delta[i].cell[10];
            rec->sample[10] = g_SceneFx.accum[i].cell[10] >> 16;
            g_SceneFx.accum[i].cell[11] += g_SceneFx.delta[i].cell[11];
            rec->sample[11] = g_SceneFx.accum[i].cell[11] >> 16;

            dst->lifetime[0] -= g_SceneFx.life_step[i].cell[0];
            dst->lifetime[1] -= g_SceneFx.life_step[i].cell[1];
            dst->lifetime[2] -= g_SceneFx.life_step[i].cell[2];
            dst->lifetime[3] -= g_SceneFx.life_step[i].cell[3];
            dst->lifetime[4] -= g_SceneFx.life_step[i].cell[4];
            dst->lifetime[5] -= g_SceneFx.life_step[i].cell[5];
            dst->lifetime[6] -= g_SceneFx.life_step[i].cell[6];
            dst->lifetime[7] -= g_SceneFx.life_step[i].cell[7];
            dst->lifetime[8] -= g_SceneFx.life_step[i].cell[8];
            dst->lifetime[9] -= g_SceneFx.life_step[i].cell[9];
            dst->lifetime[10] -= g_SceneFx.life_step[i].cell[10];
            dst->lifetime[11] -= g_SceneFx.life_step[i].cell[11];
            i++;
        } while (i < (*D_80147BDC));
    }
}

/* The scenario entity-handler table, indexed by byte 0x7A of the entity record. */
static SceneFunc s_SceneActorDispatch[] = {(SceneFunc)func_801FC810, (SceneFunc)Scene_ClearParty};

/* func_801FC7D0. Not Scene_DispatchActor.h: that body reads the global g_SceneActorDispatch, and this table is file-local. */
MATCH void Scene_DispatchActor(void* entity) {
    SceneFunc handler;
    u8        index;

    index   = ((Actor*)entity)->callback_index;
    handler = s_SceneActorDispatch[index];
    handler(entity, g_SceneFlags);
}

MATCH void func_801FC810(void) {
}

/* Step trigger: entry_08 of the scenario, called by Area_IsStepBlocked with its handler_x (x >> 16 is compared with the
 * column). A hit starts a scripted scene and returns 1; a nonzero result blocks the step. */
MATCH s32 Scene_CheckStepTrigger(s32 x) { /* func_801FC818 */
    if ((g_GameAreaId == AREA_ID_DAUNA_MINE_WORKER) && ((x >> 16) == 43) && (SYS_TestFlag(g_SceneFlags, 6) != 0)) {
        g_SceneState.state_04 = 7;
        g_SceneState.step_05  = 0;
    }
    if (g_GameAreaId == AREA_ID_DAUNA_MINE_WHELP) {
        if (D_80143F03 == 0) {
            if ((x >> 16) == 20) {
                if (SYS_TestFlag(g_SceneFlags, 7) != 0) {
                    return 0;
                }
                Game_SetScriptActive();
                g_SceneState.state_04 = 6;
                g_SceneState.step_05  = 0;
                return 1;
            }
        }
    }
    return 0;
}

MATCH s32 func_801FC8F4(void) {
    return 0;
}

#include "overlays/scenario/Scene_ClearParty.h"
