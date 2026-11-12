#include "magic126_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved;
    PartyMember* swap;
    s32          count;

    BMagic_DispatchTaskPair(func_801EECE4, Effect_PlayOnZeroTick);
    count = 0;
    do {
        if (D_801F12BC[(u8)count << 5] & 0x1) {
            saved                 = g_BattleEffectBattler;
            swap                  = FIELD(PartyMember*, D_801F12D8, (u8)count << 5);
            D_801F22BC            = D_801F12BC + ((u8)count << 5);
            g_BattleEffectBattler = swap;
            func_801F091C();
            g_BattleEffectBattler = saved;
        }
        count += 1;
    } while ((u8)count < 128);
}

INCLUDE_ASM(func_801EECE4);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEED0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF14(void) {
    SYS_DISPATCH_BYTE(D_801F1268, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        BMagic_DrawGlowRingOuter();
        BMagic_DrawGlowRingInner();
        func_801EF1C8();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CopyBattlerCoords.h"

MATCH void func_801EF00C(void) {
    g_Task->unk_09 += 2;
    g_Task->timer += 24;
    if (g_Task->unk_09 == 0x10) {
        BMagic_NextStep();
    }
}

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

INCLUDE_ASM(func_801EF1C8);

/* The glow ring scratch: the inner and outer radius and the inner-edge colour, then the quad corners (D_1F800014). */
#define GLOW_RING_INNER D_1F800000.view.effect.params[0]
#define GLOW_RING_OUTER D_1F800000.view.effect.params[1]
#define GLOW_RING_RED   D_1F800000.view.effect.params[3]
#define GLOW_RING_GREEN D_1F800000.view.effect.params[4]
#define GLOW_RING_BLUE  D_1F800000.view.effect.params[5]

/* The outer half of the glow ring: 16 additive quads from twice the effect timer (byte 0x0A) out to three
 * times it, plus a random 0 to 3 for flicker, fading out at the outer edge. */
MATCH void BMagic_DrawGlowRingOuter(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(5, getTPage(0, 1, 320, 256));
    GLOW_RING_INNER  = g_Task->timer * 2;
    GLOW_RING_OUTER  = g_Task->timer * 3 + (RANDOM_MASK(3));
    GLOW_RING_RED    = g_Task->unk_09 * 15;
    GLOW_RING_GREEN  = g_Task->unk_09 * 4;
    GLOW_RING_BLUE   = g_Task->unk_09 * 15;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_OUTER);
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB3(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
}

/* The inner half: from the timer out to twice it, coloured at the outer edge where the outer half starts. */
MATCH void BMagic_DrawGlowRingInner(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;

    GFX_AddDitheredDrawMode(5, getTPage(0, 1, 320, 256));
    GLOW_RING_INNER  = g_Task->timer;
    GLOW_RING_OUTER  = g_Task->timer * 2;
    GLOW_RING_RED    = g_Task->unk_09 * 15;
    GLOW_RING_GREEN  = g_Task->unk_09 * 4;
    GLOW_RING_BLUE   = g_Task->unk_09 * 15;
    D_1F800014[1].vx = FIXED_MUL(rsin(0), GLOW_RING_OUTER);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), GLOW_RING_OUTER);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), GLOW_RING_INNER);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), GLOW_RING_INNER);
    D_1F800014[3].vz = 0;
    D_1F800014[2].vz = 0;
    D_1F800014[1].vz = 0;
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_OUTER);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_OUTER);
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), GLOW_RING_INNER);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), GLOW_RING_INNER);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB1(prim, GLOW_RING_RED, GLOW_RING_GREEN, GLOW_RING_BLUE);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
}

MATCH void func_801EFAF4(void) {
    SYS_DISPATCH_BYTE(D_801F1278, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801EFD5C();
    }
}

MATCH void func_801EFB74(void) {
    u8           timer = g_Task->unk_09 - 1;
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    g_Task->unk_09 = timer;
    if (timer == 0) {
        SND_QueueSelectionFx(0x100);
        work               = g_Task;
        actor              = g_BattleEffectBattler;
        work->pos.x.fixed  = actor->pos.x.fixed;
        work->pos.y.fixed  = actor->pos.y.fixed;
        z                  = actor->pos.z.fixed;
        work->param.unk_0B = 0;
        work->pos.z.fixed  = z;
        g_Task->unk_09     = 0x14;
        g_Task->timer      = 0;
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_CountUpTimersAndStep.h"

MATCH void func_801EFC94(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 2;
    g_Task->unk_09 = timer;
    if (timer == 150) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

/* func_801EFCE4 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(1);
}

INCLUDE_ASM(func_801EFD5C);

MATCH void func_801F01C0(void) {
    SYS_DISPATCH_BYTE(D_801F1288, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801F06AC();
    }
}

INCLUDE_ASM(func_801F0240);

MATCH void func_801F037C(void) {
    s32 diff;
    u8  count;
    u8  scratch[16]; /* FAKE: unreferenced local pads the frame to 0x28. */

    count = g_Task->unk_09;
    if (count < 16) {
        g_Task->unk_09 = count + 4;
    }

    func_800AF2B4((BattleRange*)g_BattleEffectBattler, 0x60);
    g_Task->unk_10 = g_Task->unk_0C;
    g_Task->unk_0C = ratan2(g_BattleEffectBattler->pos.x.fixed - g_Task->pos.x.fixed, g_BattleEffectBattler->pos.y.fixed - g_Task->pos.y.fixed);

    if (func_800AF66C((BattleRange*)g_BattleEffectBattler, 0xC000) != 0) {
        g_Task->header.step += 1;
        return;
    }

    diff           = (g_Task->unk_10 & 0xFFF) - (g_Task->unk_0C & 0xFFF);
    g_Task->unk_10 = diff;
    if (diff < 0) {
        g_Task->unk_10 = ~diff + 1;
    }
    if ((u32)(g_Task->unk_10 - 0x601) < 0x3FF) {
        g_Task->header.step += 1;
    }
}

INCLUDE_ASM(func_801F0494);

#include "overlays/bmagic/Effect_TickOnTimerNegative.h"

INCLUDE_ASM(func_801F06AC);

MATCH void func_801F091C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 19), 1, D_801F22BC);
}

MATCH void func_801F0960(void) {
    SYS_DISPATCH_BYTE(D_801F12AC, D_801F22BC->header.step);
    if (D_801F22BC->header.flags != 0 && D_801F22BC->header.step != 0) {
        func_801F11AC();
        func_801F0ED0();
    }
}

INCLUDE_ASM(func_801F09E0);

MATCH void func_801F0B34(void) {
    s16* angle_cell;
    s32  angle;
    u8   count;

    if (g_FrameCount & 1) {
        D_801F22BC->slot += 1;
        D_801F22BC->unk_07 += 1;
    }
    angle              = D_801F22BC->unk_04 & 0xF;
    angle_cell         = &D_1F800004;
    *angle_cell        = angle << 8;
    D_801F22BC->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(angle << 8)) * D_801F22BC->unk_07;
    D_801F22BC->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * D_801F22BC->unk_07;
    D_801F22BC->unk_18 += PARTY_MEMBER_WORD_08(D_801F22BC);
    count              = D_801F22BC->pad_06 + 1;
    D_801F22BC->pad_06 = count;
    if (count == 16) {
        D_801F22BC->header.step += 1;
    }
}

MATCH void func_801F0C7C(void) {
    s16* angle_cell;
    s32  angle;

    if (g_FrameCount & 0x1) {
        D_801F22BC->unk_07 += 1;
    }
    PARTY_MEMBER_WORD_08(D_801F22BC) += 0x80000;
    angle              = D_801F22BC->unk_04 & 0xF;
    angle_cell         = &D_1F800004;
    *angle_cell        = angle << 8;
    D_801F22BC->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(angle << 8)) * D_801F22BC->unk_07;
    D_801F22BC->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * D_801F22BC->unk_07;
    D_801F22BC->unk_18 += PARTY_MEMBER_WORD_08(D_801F22BC);
    if ((s32)PARTY_MEMBER_WORD_08(D_801F22BC) > 0x7FFFFF) {
        D_801F22BC->header.step += 1;
    }
}

MATCH void func_801F0DA4(void) {
    s16* angle_cell;
    s32  angle;
    u8   count;

    if (g_FrameCount & 0x1) {
        D_801F22BC->unk_07 += 1;
    }
    angle              = D_801F22BC->unk_04 & 0xF;
    angle_cell         = &D_1F800004;
    *angle_cell        = angle << 8;
    D_801F22BC->unk_10 = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(angle << 8)) * D_801F22BC->unk_07;
    D_801F22BC->unk_14 = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * D_801F22BC->unk_07;
    D_801F22BC->unk_18 += PARTY_MEMBER_WORD_08(D_801F22BC);
    count              = D_801F22BC->pad_06 - 1;
    D_801F22BC->pad_06 = count;
    if (count == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801F116C();
    }
}

INCLUDE_ASM(func_801F0ED0);

MATCH u32 func_801F1110(void) {
    u8 index;

    for (index = 0u; index < 128; index++) {
        if ((D_801F12BC[index << 5] & 0x1) == 0) {
            D_801F12BC[index << 5] |= 1;
            return index;
        }
    }
    return 0xFFu;
}

MATCH void func_801F116C(void) {
    D_801F22BC->header.flags = 0;
    D_801F22BC->header.mode  = 0;
    D_801F22BC->header.step  = 0;
    D_801F22BC->unk_03       = 0;
}

MATCH void func_801F11AC(void) {
    PartyMember* work;
    s16          vec[3];
    TILE_1*      primitive;

    work      = D_801F22BC;
    vec[0]    = (work->unk_10 >> 9) - 0x4000;
    primitive = (TILE_1*)g_GfxPrimCursor;
    vec[1]    = (work->unk_14 >> 9) - 0x4000;
    vec[2]    = -((s16)(*(u16*)((u8*)work + 0x1A)) / 2);
    SetTile1(primitive);
    RotTransPers((SVECTOR*)vec, (long*)&primitive->x0, (long*)vec, (long*)&vec[2]);
    ((s16*)&D_801F22BC->unk_0C)[0] = primitive->x0;
    ((s16*)&D_801F22BC->unk_0C)[1] = primitive->y0;
}
