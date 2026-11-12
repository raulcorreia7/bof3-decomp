#include "magic150_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC20.h"

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED60(void) {
    u8 timer;

    func_801EF6F8();
    func_801EF8EC();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEDCC(void) {
    if (func_801EF8EC() == 0) {
        g_Task->unk_09      = 4;
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEE24(void) {
    s16* radius;
    u8   timer;

    radius = &D_801EFA9C.radius;
    *radius += 0x40;
    D_801EFA9C.offset += 96;
    func_801EF254();
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = 120;
        g_Task->header.mode += 1;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}

MATCH void func_801EEEC4(void) {
    u8 count;

    D_801EFA9C.radius = ((g_FrameCount & 0x1) * 16) + 256;
    D_801EFA9C.angle -= ANGLE_45;
    func_801EF254();
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        g_Task->unk_09 = 4;
        g_Task->header.mode += 1;
        Battle_MarkDamaged(g_Battle.target_selector);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
    }
}

INCLUDE_ASM(func_801EEF80);

#include "shared/Effect_StartPlaying.h"

INCLUDE_ASM(func_801EF040);

MATCH void func_801EF254(void) {
    GFX_AddDrawMode(GetTPage(0, 1, 0x2C0, 0x100) & HALF_MASK);
    func_801AFE18();
    func_801EF040();
    func_801EF4E0();
}

/* Projects the point and the points half a unit to its left and right to the screen. */
/* func_801EF2C0 */
MATCH void BMagic_ProjectSpan(ProjectedSpan* span) {
    Area_ProjectPoint(span->pos, &span->screen[1]);
    span->pos[0] -= COORD_HALF;
    Area_ProjectPoint(span->pos, &span->screen[0]);
    span->pos[0] += TO_COORD(1);
    Area_ProjectPoint(span->pos, &span->screen[2]);
}

INCLUDE_ASM(func_801EF324);

INCLUDE_ASM(func_801EF4E0);

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

INCLUDE_ASM(func_801EF6F8);

/* Draws a semi-transparent ring of sixteen Gouraud triangles from (x, y), one per sixteenth of a turn: the first
 * vertex red, the other two shaded. */
MATCH void func_801EF790(s16 x, s16 y, s16 radius, u8 red, u8 shade) {
    POLY_G3* packet;
    u16      angle;
    u16      next;

    angle = 0;
    do {
        packet = GFX_BeginPolyG3(1);
        setXY2(packet, x, y, (s16)(x + FIXED_MUL(radius, rcos(angle))), (s16)(y + FIXED_MUL(radius, rsin(angle))));
        next       = angle + ONE / 16;
        packet->x2 = (s16)(x + FIXED_MUL(radius, rcos(next)));
        packet->y2 = (s16)(y + FIXED_MUL(radius, rsin(next)));
        angle      = next;
        setRGB0(packet, red, 0, 0);
        setRGB1(packet, shade, 0, 0);
        setRGB2(packet, shade, 0, 0);
        GFX_AddPrim(1u, sizeof(POLY_G3));
    } while (angle < ONE);
}

MATCH u8 func_801EF8EC(void) {
    s32     origin[3];
    DVECTOR screen;
    u8      i;
    u8      drawn;

    GFX_AddDrawMode(GetTPage(0, 1, 0x2C0, 0x100));
    func_801AFE18();
    drawn      = 0;
    D_801EFAF4 = D_801EFA9C.sparks;
    for (i = 0; i < 8; i++) {
        if (D_801EFAF4->active != 0) {
            origin[0] = D_801EFA9C.origin[0];
            origin[1] = D_801EFA9C.origin[1] + ((D_801EFAF4->offset * rcos(D_801EFAF4->angle)) >> 4);
            origin[2] = D_801EFA9C.origin[2] + ((D_801EFAF4->offset * rsin(D_801EFAF4->angle)) << 4);
            Area_ProjectPoint(origin, &screen);
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
