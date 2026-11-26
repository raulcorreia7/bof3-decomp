#include "magic150_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC20.h"

MATCH void func_801EECA4(void) {
    setVector(&D_801EFA9C.origin, D_801EC2E0->target.party->pos.x.fixed + 0x14000, D_801EC2E0->target.party->pos.y.fixed, D_801EC2E0->target.party->pos.z.fixed + (0x2C0 << 16));
    D_801EFA9C.radius = 0;
    D_801EFA9C.offset = 0;
    D_801EFA9C.angle  = 0;
    func_801EF6B0();
    SELF(PartyMember)->unk_09 = 0x3C;
    SELF(PartyMember)->header.mode += 1;
    SND_SEPlay(0x100);
}

MATCH void func_801EED60(void) {
    u8 timer;

    func_801EF6F8();
    func_801EF8EC();
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}

MATCH void func_801EEDCC(void) {
    if (func_801EF8EC() == 0) {
        SELF(PartyMember)->unk_09      = 4;
        SELF(PartyMember)->header.mode = SELF(PartyMember)->header.mode + 1;
    }
}

MATCH void func_801EEE24(void) {
    s16* radius;
    u8   timer;

    radius = &D_801EFA9C.radius;
    *radius += 0x40;
    D_801EFA9C.offset += 96;
    func_801EF254();
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->unk_09 = 120;
        SELF(PartyMember)->header.mode += 1;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}

MATCH void func_801EEEC4(void) {
    u8 count;

    D_801EFA9C.radius = ((g_FrameCount & 0x1) * 16) + 256;
    D_801EFA9C.angle -= ANGLE_45;
    func_801EF254();
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        SELF(PartyMember)->unk_09 = 4;
        SELF(PartyMember)->header.mode += 1;
        Battle_MarkDamaged(g_Battle.target_selector);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x02));
    }
}

MATCH void func_801EEF80(void) {
    s16* radius;
    u8   timer;

    radius = &D_801EFA9C.radius;
    *radius -= 0x40;
    D_801EFA9C.offset -= 96;
    func_801EF254();
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "shared/Effect_StartPlaying.h"

MATCH void func_801EF040(void) {
    POLY_F4* prim;
    DVECTOR  screen;
    s32      pos[3];
    u16      angle;
    u8       i;

    angle = 0;
    for (i = 0; i < 16; i++) {
        prim = (POLY_F4*)g_GfxPrimCursor;
        SetPolyF4(prim);
        SetSemiTrans(prim, 1);
        pos[0] = D_801EFA9C.origin.vx;
        pos[1] = D_801EFA9C.origin.vy + ((D_801EFA9C.radius * rcos(angle)) >> 4);
        pos[2] = D_801EFA9C.origin.vz + ((D_801EFA9C.radius * rsin(angle)) << 4);
        Camera_ProjectPoint(pos, &screen);
        setXY0(prim, screen.vx, screen.vy);
        pos[0] = D_801EFA9C.origin.vx + TO_COORD(16);
        Camera_ProjectPoint(pos, &screen);
        prim->x1 = screen.vx;
        prim->y1 = screen.vy;
        angle += 0x100;
        pos[0] = D_801EFA9C.origin.vx;
        pos[1] = D_801EFA9C.origin.vy + ((D_801EFA9C.radius * rcos(angle)) >> 4);
        pos[2] = D_801EFA9C.origin.vz + ((D_801EFA9C.radius * rsin(angle)) << 4);
        Camera_ProjectPoint(pos, &screen);
        prim->x2 = screen.vx;
        prim->y2 = screen.vy;
        pos[0]   = D_801EFA9C.origin.vx + TO_COORD(16);
        Camera_ProjectPoint(pos, &screen);
        prim->x3 = screen.vx;
        prim->y3 = screen.vy;
        setRGB0(prim, 128, 0, 0);
        /* FAKE: retail tests the whole return register, as for a call with no prototype; the shared s16 prototype adds a sign extension. */
        if (((s32 (*)(Pos2*, Pos2*, Pos2*))MATH_TriangleWinding)((Pos2*)&prim->x0, (Pos2*)&prim->x1, (Pos2*)&prim->x2) < 0) {
            GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_F4));
        }
    }
}

MATCH void func_801EF254(void) {
    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100) & HALF_MASK);
    func_801AFE18();
    func_801EF040();
    func_801EF4E0();
}

/* Projects the point and the points half a unit to its left and right to the screen. */
/* func_801EF2C0 */
MATCH void BMagic_ProjectSpan(ProjectedSpan* span) {
    Camera_ProjectPoint(&span->pos.vx, &span->screen[1]);
    span->pos.vx -= COORD_HALF;
    Camera_ProjectPoint(&span->pos.vx, &span->screen[0]);
    span->pos.vx += TO_COORD(1);
    Camera_ProjectPoint(&span->pos.vx, &span->screen[2]);
}

/* Draws the beam segment between two projected spans: two gouraud quads join
 * their left and right cells and a flat line joins their centres. */
MATCH void func_801EF324(Magic150SpanPair* pair) {
    POLY_G4* quad;
    LINE_F2* line;

    quad = GFX_BeginPolyG4(1);
    setXY4(quad, pair->previous.screen[1].vx, pair->previous.screen[1].vy, pair->previous.screen[0].vx, pair->previous.screen[0].vy, pair->current.screen[1].vx, pair->current.screen[1].vy,
           pair->current.screen[0].vx, pair->current.screen[0].vy);
    setRGB0(quad, 64, 64, 0);
    setRGB1(quad, 0, 0, 0);
    setRGB2(quad, 64, 64, 0);
    setRGB3(quad, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));

    quad     = GFX_CURSOR(POLY_G4);
    *quad    = quad[-1];
    quad->x1 = pair->previous.screen[2].vx;
    quad->y1 = pair->previous.screen[2].vy;
    quad->x3 = pair->current.screen[2].vx;
    quad->y3 = pair->current.screen[2].vy;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));

    line = GFX_CURSOR(LINE_F2);
    SetLineF2(line);
    SetSemiTrans(line, 1);
    setXY2(line, pair->previous.screen[1].vx, pair->previous.screen[1].vy, pair->current.screen[1].vx, pair->current.screen[1].vy);
    setRGB0(line, 32, 32, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(LINE_F2));
}

/* Draws the beam along its path: 128 segments, each 1/32 turn further round the path
 * angle and a jittered step further along x. */
MATCH void func_801EF4E0(void) {
    s32 x;
    s32 step;
    u16 angle;
    u16 i;

    func_801AFE18();
    angle = D_801EFA9C.angle;
    x     = D_801EFA9C.origin.vx;
    setVector(&D_801EFAF8.current.pos, x, D_801EFA9C.origin.vy + ((D_801EFA9C.offset * rcos(angle)) >> 4), D_801EFA9C.origin.vz + ((D_801EFA9C.offset * rsin(angle)) << 4));
    BMagic_ProjectSpan(&D_801EFAF8.current);
    step = 0x1000;
    i    = 0;
    do {
        D_801EFAF8.previous = D_801EFAF8.current;
        angle += 0x80;
        x += step;
        setVector(&D_801EFAF8.current.pos, x + (rand() & 0xFFF) * 16 - 0x8000, D_801EFA9C.origin.vy + ((D_801EFA9C.offset * rcos(angle)) >> 4),
                  D_801EFA9C.origin.vz + ((D_801EFA9C.offset * rsin(angle)) << 4));
        step += 0x40;
        i++;
        BMagic_ProjectSpan(&D_801EFAF8.current);
        func_801EF324(&D_801EFAF8);
    } while (i < 0x80);
}

MATCH void func_801EF6B0(void) {
    u8 i;

    D_801EFAF4 = D_801EFA9C.sparks;
    i          = 0;
    do {
        i++;
        D_801EFAF4->active = 0;
        D_801EFAF4 += 1;
    } while (i < 8);
}

MATCH void func_801EF6F8(void) {
    u8 i;
    D_801EFAF4 = D_801EFA9C.sparks;
    i          = 0;
    do {
        if (D_801EFAF4->active == 0) {
            D_801EFAF4->active = 1;
            D_801EFAF4->offset = 0x300;
            D_801EFAF4->angle  = (rand() & BYTE_MASK) << 4;
            D_801EFAF4->life   = 8;
            break;
        }
        D_801EFAF4 += 1;
        i++;
    } while (i < 8);
}

MATCH void func_801EF790(s32 x, s32 y, s16 radius, u8 colour, u8 alpha) {
    POLY_G3* prim;
    u16      angle;
    u16      next;

    for (angle = 0; angle < ONE; angle += 0x100) {
        prim = GFX_BeginPolyG3(1);
        setXY2(prim, x, y, x + FIXED_MUL(radius, rcos(angle)), y + FIXED_MUL(radius, rsin(angle)));
        next     = angle + 0x100;
        prim->x2 = x + FIXED_MUL(radius, rcos(next));
        prim->y2 = y + FIXED_MUL(radius, rsin(next));
        setRGB0(prim, colour, 0, 0);
        setRGB1(prim, alpha, 0, 0);
        setRGB2(prim, alpha, 0, 0);
        GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G3));
    }
}

MATCH u8 func_801EF8EC(void) {
    s32     origin[3];
    DVECTOR screen;
    u8      i;
    u8      drawn;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x2C0, 0x100));
    func_801AFE18();
    drawn      = 0;
    D_801EFAF4 = D_801EFA9C.sparks;
    for (i = 0; i < 8; i++) {
        if (D_801EFAF4->active != 0) {
            origin[0] = D_801EFA9C.origin.vx;
            origin[1] = D_801EFA9C.origin.vy + ((D_801EFAF4->offset * rcos(D_801EFAF4->angle)) >> 4);
            origin[2] = D_801EFA9C.origin.vz + ((D_801EFAF4->offset * rsin(D_801EFAF4->angle)) << 4);
            Camera_ProjectPoint(origin, &screen);
            func_801EF790(screen.vx, screen.vy, D_801EFAF4->life, GFX_COLOR_NEUTRAL, 0);
            drawn              = 1;
            D_801EFAF4->angle  = D_801EFAF4->angle + 128;
            D_801EFAF4->offset = D_801EFAF4->offset - 96;
            D_801EFAF4->life   = D_801EFAF4->life - 1;
            if (D_801EFAF4->offset == 0) {
                D_801EFAF4->active = 0;
            }
        }
        D_801EFAF4 += 1;
    }
    return drawn;
}
