#include "sce15ef0_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/scenario/shared/Scene_DispatchEntity.h"

MATCH void func_801D0C48(void) {
    SELF(Actor)->pos.x.fixed = TO_COORD(48) + COORD_HALF;
    SELF(Actor)->pos.y.fixed = TO_COORD(116);
    SELF(Actor)->pos.z.fixed = Area_HeightSample(SELF(Actor)->pos.x.fixed, TO_COORD(116)) << 16;
    setVector(SELF(Actor), 0x308000, 0x718000, 0xFEC00000);
    SELF(Actor)->screen_x         = 0;
    SELF(Actor)->tint.bytes.rgb.r = 0;
    SELF(Actor)->timer            = 8;
    SELF(Actor)->header.mode += 1;
}

MATCH void func_801D0CEC(void) {
    Actor* work = SELF(Actor);

    work->tint.bytes.rgb.r += 8;
    work->screen_x += 0x10;
    func_801D1C1C(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, SELF(Actor)->tint.bytes.rgb.r);
    GFX_DrawColorFan(&SELF(Actor)->pos.x.fixed, SELF(Actor)->screen_x, 2);

    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        SELF(Actor)->timer = 60;
        SELF(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 13));
    }
}

MATCH void func_801D0DB0(void) {
    func_801D1C1C(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, SELF(Actor)->tint.bytes.rgb.r);
    GFX_DrawColorFan(&SELF(Actor)->pos.x.fixed, SELF(Actor)->screen_x, 2);

    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        SELF(Actor)->tint.bytes.rgb.g = 0;
        SELF(Actor)->timer            = 4;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D0E5C(void) {
    SELF(Actor)->tint.bytes.rgb.g += 0x40;
    if ((s8)SELF(Actor)->tint.bytes.rgb.g != 0) {
        func_801D1220((u8)SELF(Actor)->tint.bytes.rgb.g);
    } else {
        func_801D1220(0xFF);
    }
    func_801D1C1C(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, SELF(Actor)->tint.bytes.rgb.r);
    GFX_DrawColorFan(&SELF(Actor)->pos.x.fixed, SELF(Actor)->screen_x, 2);
    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        SELF(Actor)->timer = 4;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D0F44(void) {
    SELF(Actor)->tint.bytes.rgb.g -= 0x40;
    func_801D1220(SELF(Actor)->tint.bytes.rgb.g);
    func_801D1C1C(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, SELF(Actor)->tint.bytes.rgb.r);
    GFX_DrawColorFan(&SELF(Actor)->pos.x.fixed, SELF(Actor)->screen_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        SELF(Actor)->timer = 60;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D101C(void) {
    func_801D1C1C(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, SELF(Actor)->tint.bytes.rgb.r);
    GFX_DrawColorFan(&SELF(Actor)->pos.x.fixed, SELF(Actor)->screen_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        SELF(Actor)->timer = 60;
        SELF(Actor)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 14));
    }
}

MATCH void func_801D10C4(void) {
    if ((s16)SELF(Actor)->screen_x > 0) {
        SELF(Actor)->screen_x -= 0x10;
    }
    if ((s8)SELF(Actor)->tint.bytes.rgb.r > 0) {
        SELF(Actor)->tint.bytes.rgb.r -= 8;
    }
    func_801D1C1C(&SELF(Actor)->pos.x.fixed, &SELF(Actor)->vx, SELF(Actor)->tint.bytes.rgb.r);
    GFX_DrawColorFan(&SELF(Actor)->pos.x.fixed, SELF(Actor)->screen_x, 2);
    func_801D1914(64);

    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        SELF(Actor)->timer    = 16;
        SELF(Actor)->screen_x = 0x40;
        SELF(Actor)->header.mode += 1;
    }
}

MATCH void func_801D11B4(void) {
    func_801D1914(SELF(Actor)->screen_x -= 4);

    if (TIMER_EXPIRED(SELF(Actor)->timer)) {
        Actor_Clear();
    }
}

MATCH void func_801D1220(s32 value) {
    s32      front[3];
    s32      back[3];
    POLY_F4* prim;
    POLY_F4* new_var;
    s32      tpage;
    u8       i;
    /* FAKE: retail reserves 8 more frame bytes than the cell position takes, between the point rows and the saved registers. */
    FAKE_STACK_PADS(u8, 8);

    front[0] = back[0] = TO_COORD(44) + COORD_HALF;
    front[1] = back[1] = TO_COORD(113) + COORD_HALF;
    front[2]           = 0;
    back[2]            = -TO_COORD(768);
    i                  = 0;
    do {
        tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        {
            Coord cell_x = {front[0]};
            Coord cell_y = {front[1]};

            Area_CellAddPrim(cell_x.fixed, cell_y.fixed, 0, 0xC);
        }
        i++;
        /* FAKE: the copy in its own block fixes the cursor pointer's allocation; retail keeps the load and the draw setup apart. */
        do {
            new_var = (POLY_F4*)g_GfxPrimCursor;
            prim    = new_var;
        } while (0);
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        Camera_ProjectPoint(front, (DVECTOR*)&prim->x0);
        Camera_ProjectPoint(back, (DVECTOR*)&prim->x1);
        front[0] += TO_COORD(1);
        back[0] += TO_COORD(1);
        Camera_ProjectPoint(front, (DVECTOR*)&prim->x2);
        Camera_ProjectPoint(back, (DVECTOR*)&prim->x3);
        setRGB0(prim, value, value, value);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F4));
    } while (i < 8);
}

/* Draw a red line between two points with a fan at each end. */
MATCH void func_801D1370(s32* first, s32* second, s16 width) {
    LINE_F2* line;
    u16      size[2];
    u16      scale[2];
    MATRIX   camera;
    s32      angle;
    u16      angle1;
    u16      angle2;
    s16      radius1;
    s16      radius2;

    GFX_AddDitheredDrawMode(3, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, FONT_TPAGE_X, FONT_TPAGE_Y));
    Camera_SetMatrix(&camera);
    line = (LINE_F2*)g_GfxPrimCursor;
    SetLineF2(line);
    SetSemiTrans(line, 0);
    Camera_ProjectPoint(first, (DVECTOR*)&line->x0);
    Camera_ProjectPoint(second, (DVECTOR*)&line->x1);
    setRGB0(line, 64, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(LINE_F2));
    angle   = ratan2(line->y1 - line->y0, line->x1 - line->x0);
    size[0] = size[1] = width;
    Game_ProjectWorldPoint(first, size, scale);
    angle1  = angle + ANGLE_90;
    radius1 = scale[0] + (g_FrameCount & 1);
    func_801D1540(line->x0, line->y0, radius1, angle1);
    Game_ProjectWorldPoint(second, size, scale);
    angle2  = angle + ANGLE_270;
    radius2 = scale[0] + (g_FrameCount & 1);
    func_801D1540(line->x1, line->y1, radius2, angle2);
    func_801D1690(line->x0, line->y0, radius1, angle1, line->x1, line->y1, radius2, angle2);
}

MATCH void func_801D1540(s32 x, s32 y, s16 radius, u16 angle) {
    POLY_G3* prim;
    u8       i;

    i = 0;
    do {
        prim = GFX_BeginPolyG3(1);
        setXY2(prim, x, y, x + FIXED_MUL(radius, rcos(angle)), y + FIXED_MUL(radius, rsin(angle)));
        angle += 0x100;
        prim->x2 = x + FIXED_MUL(radius, rcos(angle));
        i += 1;
        prim->y2 = y + FIXED_MUL(radius, rsin(angle));
        setRGB0(prim, 64, 0, 0);
        setRGB1(prim, 0, 0, 0);
        setRGB2(prim, 0, 0, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G3));
    } while (i < 8);
}

MATCH void func_801D1690(s16 x1, s16 y1, s16 radius1, u16 angle1, s16 x2, s16 y2, s16 radius2, u16 angle2) {
    POLY_G4* poly;
    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 1);
    setXY4(poly, x1, y1, x2, y2, x1 + FIXED_MUL(radius1, rcos(angle1)), y1 + FIXED_MUL(radius1, rsin(angle1)), x2 + FIXED_MUL(radius2, rcos(angle2 + ANGLE_180)),
           y2 + FIXED_MUL(radius2, rsin(angle2 + ANGLE_180)));
    setRGB0(poly, 64, 0, 0);
    setRGB1(poly, 64, 0, 0);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G4));

    poly++;
    memcpy(poly, poly - 1, sizeof(POLY_G4));
    poly->x2 = x1 + FIXED_MUL(radius1, rcos(angle1 + ANGLE_180));
    poly->y2 = y1 + FIXED_MUL(radius1, rsin(angle1 + ANGLE_180));
    poly->x3 = x2 + FIXED_MUL(radius2, rcos(angle2));
    poly->y3 = y2 + FIXED_MUL(radius2, rsin(angle2));
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_G4));
}

MATCH void func_801D1914(s16 amount) {
    VECTOR start;
    VECTOR end;

    setVector(&start, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, TO_COORD(-768));
    setVector(&end, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, TO_COORD(-512));
    func_801D1370(&start, &end, amount);

    setVector(&start, TO_COORD(48), TO_COORD(113) + COORD_HALF, TO_COORD(-384));
    func_801D1370(&start, &end, amount);

    setVector(&end, TO_COORD(48), TO_COORD(113) + COORD_HALF, TO_COORD(-256));
    func_801D1370(&start, &end, amount);

    setVector(&start, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, TO_COORD(-128));
    func_801D1370(&start, &end, amount);

    setVector(&end, TO_COORD(48) + COORD_HALF, TO_COORD(113) + COORD_HALF, 0);
    func_801D1370(&start, &end, amount);
}

/* func_801D1A20 */
#include "shared/GFX_DrawColorFan.h"

/* Two tinted slivers between the work position and its target, then eight
 * stepped segments along the span. */
MATCH void func_801D1C1C(s32* from, s32* to, u8 level) {
    POLY_G4* prim;
    TILE_1*  segment;
    Pos3     current;
    Pos3     step;
    DVECTOR  projected;
    s32      phase;
    u8       i;
    u16      tpage;

    tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 704, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, tpage);

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(from, &projected);
    setXY2(prim, projected.vx + 1, projected.vy + 2, projected.vx, projected.vy);
    Camera_ProjectPoint(to, &projected);
    prim->x2 = projected.vx - 1;
    prim->y2 = projected.vy - 2;
    prim->x3 = projected.vx;
    prim->y3 = projected.vy;
    setRGB0(prim, 0, 0, 0);
    setRGB1(prim, level, level, 0);
    setRGB2(prim, 0, 0, 0);
    setRGB3(prim, level, level, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    Camera_ProjectPoint(from, &projected);
    setXY2(prim, projected.vx, projected.vy, projected.vx + 1, projected.vy + 2);
    Camera_ProjectPoint(to, &projected);
    prim->x2 = projected.vx;
    prim->y2 = projected.vy;
    prim->x3 = projected.vx - 1;
    prim->y3 = projected.vy - 2;
    setRGB0(prim, 0, level, 0);
    setRGB1(prim, 0, 0, 0);
    setRGB2(prim, 0, level, 0);
    setRGB3(prim, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));

    step.x    = (to[0] - from[0]) >> 6;
    step.y    = (to[1] - from[1]) >> 6;
    step.z    = (to[2] - from[2]) >> 6;
    phase     = g_FrameCount & 7;
    current.x = from[0] + step.x * phase;
    current.y = from[1] + step.y * phase;
    current.z = from[2] + step.z * phase;
    for (i = 0; i < 8; i++) {
        if (current.y < to[1]) {
            break;
        }
        Camera_ProjectPoint(&current.x, &projected);
        segment = (TILE_1*)g_GfxPrimCursor;
        SetTile1(segment);
        SetSemiTrans(segment, 1);
        setXY0(segment, projected.vx, projected.vy - 1);
        setRGB0(segment, 0, level, 0);
        GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE_1));
        current.x += step.x * 8;
        current.y += step.y * 8;
        current.z += step.z * 8;
    }
}
