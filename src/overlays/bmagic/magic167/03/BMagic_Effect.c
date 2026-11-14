#include "magic167_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

/* Copies the selected battler's pose into the effect, spawns one battle effect
 * at that position and eight more in a four-column grid, and queues the
 * selection sound. */
MATCH void func_801EEC94(void) {
    PartyMember* battler;
    PartyMember* target;
    u32          first_slot;
    u8           i;
    u8           slot;

    battler              = g_BattleSelectedActor;
    g_Task->facing       = battler->facing;
    g_Task->pos.x        = battler->pos.x;
    g_Task->pos.y        = battler->pos.y;
    g_Task->pos.z        = battler->pos.z;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    first_slot                                   = Battle_AllocEffect(1, 0x47) & BYTE_MASK;
    g_BattleEffects[first_slot].target.party     = g_Task;
    g_BattleEffects[first_slot].header.mode      = 0;
    g_BattleEffects[first_slot].arg.unk_09       = 0;
    g_BattleEffects[first_slot].pos.x            = g_Task->pos.x;
    g_BattleEffects[first_slot].pos.y            = g_Task->pos.y;
    COORD_INT(g_BattleEffects[first_slot].pos.z) = COORD_INT(g_Task->pos.z);
    g_Task->param.unk_0B += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 0x47);
        target                             = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = (i & 0x3) * 8;
        g_BattleEffects[slot].arg.unk_09   = ((i >> 2) * 40) + 17;
        g_BattleEffects[slot].target.party = target;
        g_BattleEffects[slot].pos.x        = g_Task->pos.x;
        g_BattleEffects[slot].pos.y        = g_Task->pos.y;
        g_BattleEffects[slot].pos.z        = g_Task->pos.z;
        g_Task->param.unk_0B += 1;
        i++;
    } while (i < 8);
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
}

/* func_801EEE88 */
#include "overlays/bmagic/Effect_PreparePalette.h"

#include "overlays/bmagic/Effect_BrightenPalette.h"

#include "overlays/bmagic/Effect_Pause.h"

/* Darkens the palette fade row the effect timer indexes and, when its red reaches zero, releases the selected
 * battler's fades and advances the mode. */
MATCH void func_801EF080(void) {
    /* FAKE: retail frame reserves 0x10 bytes no statement uses. */
    FAKE_STACK_PADS(u8, 0x10);

    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    g_PaletteFades[g_Task->timer].offset.blue -= 1;
    if (g_PaletteFades[g_Task->timer].offset.red == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF2D8 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF31C(void) {
    SYS_DISPATCH_BYTE(D_801F08B8, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        D_1F800004 = g_Task->unk_09 * 5;
        func_801EF4B0();
        func_801EF708();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EF4B0(void) {
    POLY_G3* poly;
    s32      tpage;
    s32      i;
    long     flag;
    long     depth;
    s32*     shade;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(5, tpage);
    D_1F800014[2].vx = (rsin(0) * 3U) >> 6;
    D_1F800014[2].vy = (rcos(0) * 3U) >> 6;
    for (i = 1; i < 17; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = (rsin(i << 8) * 3U) >> 6;
        D_1F800014[2].vy = (rcos(i << 8) * 3U) >> 6;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        poly             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(poly);
        SetSemiTrans(poly, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, &depth, &flag);
        shade    = &D_1F800004;
        poly->r0 = *shade;
        poly->g0 = *shade;
        poly->b0 = *shade;
        poly->r1 = *shade;
        poly->g1 = *shade / 2;
        poly->b1 = 1;
        poly->r2 = *shade;
        poly->g2 = *shade / 2;
        poly->b2 = 1;
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(5, tpage);
}

MATCH void func_801EF708(void) {
    POLY_G4* poly;
    s32      tpage;
    s32      i;
    long     depth;
    long     flag;
    s32*     shade;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    GFX_AddDitheredDrawMode(5, tpage);
    D_1F800014[1].vx = (rsin(0) * 3U) >> 6;
    D_1F800014[1].vy = (rcos(0) * 3U) >> 6;
    D_1F800014[3].vx = (u32)rsin(0) >> 4;
    D_1F800014[3].vy = (u32)rcos(0) >> 4;
    for (i = 1; i < 17; i++) {
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = (rsin(i << 8) * 3U) >> 6;
        D_1F800014[1].vy = (rcos(i << 8) * 3U) >> 6;
        D_1F800014[3].vx = (u32)rsin(i << 8) >> 4;
        D_1F800014[3].vy = (u32)rcos(i << 8) >> 4;
        D_1F800014[3].vz = 0;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        poly             = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(poly);
        SetSemiTrans(poly, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&poly->x0, (long*)&poly->x1, (long*)&poly->x2, (long*)&poly->x3, &depth, &flag);
        shade    = &D_1F800004;
        poly->r0 = *shade;
        poly->g0 = *shade / 2;
        poly->b0 = 1;
        poly->r1 = *shade;
        poly->g1 = *shade / 2;
        poly->b1 = 1;
        poly->r2 = 1;
        poly->g2 = 1;
        poly->b2 = 1;
        poly->r3 = 1;
        poly->g3 = 1;
        poly->b3 = 1;
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    GFX_AddDitheredDrawMode(5, tpage);
}

MATCH void func_801EF9B8(void) {
    SYS_DISPATCH_BYTE(D_801F08C4, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        if (g_Task->header.step < 3) {
            func_801EFC44();
        }
        func_801F05C8(2);
        func_801F05C8(3);
        PopMatrix();
    }
}

MATCH void func_801EFA70(void) {
    u8 timer;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->timer       = 1;
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EFACC(void) {
    u8 timer;

    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    timer = g_Task->timer;
    if (timer < 16U) {
        g_Task->timer = timer + 1;
    }
    if (g_Task->unk_09 == 0x18) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFB5C(void) {
    g_Task->param.unk_0B += 2;
    g_Task->unk_09 += 1;
    g_Task->timer -= 1;
    if (g_Task->unk_09 == 0x28) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFBE4(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x18) {
        g_BattleEffectBattler->param.unk_0B--;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EFC44);

MATCH void func_801F05C8(s32 step) {
    TILE_1*      primitive;
    PartyMember* work;
    s32*         angle;
    s32*         shade;
    s32          tpage;
    s32          i;
    s32          rise;
    s32          height;
    s32          turn;
    s32          jitter;
    s32          x;
    s32          y;
    long         p;
    long         flag;

    /* The angle word sits three scratch words after the radius word; the depth word lies between them. */
    i     = 1;
    angle = &D_1F80000C;
    for (; i < 24; i += step) {
        if (i >= g_Task->unk_09) {
            break;
        }
        if (g_Task->header.step == 3) {
            if (g_Task->timer + i >= 25) {
                break;
            }
            jitter     = rand();
            rise       = (g_Task->timer + i) * (step + 2);
            D_1F800004 = 0x80 - (g_Task->timer + i) * 5;
            height     = rise + (jitter & 3);
        } else {
            jitter     = rand();
            rise       = i * (step + 2);
            D_1F800004 = 0x80 - i * 5;
            height     = rise + (jitter & 3);
        }
        work             = g_Task;
        turn             = ((work->param.unk_0B - i) & 0x1F) << 7;
        angle[0]         = turn;
        angle[-3]        = 0xC0 - (work->unk_09 - i) * 2;
        angle[-1]        = -((work->unk_09 - i) * 12);
        D_1F800014[0].vx = FIXED_MUL(rsin(turn), angle[-3]);
        D_1F800014[0].vy = FIXED_MUL(rcos(angle[0]), angle[-3]);
        D_1F800014[0].vz = angle[-1] + height + 8;
        if (D_1F800014[0].vz > 0) {
            D_1F800014[0].vz = 0;
        }
        x     = (D_1F800014[0].vx << 9) + g_Task->pos.x.fixed;
        y     = (D_1F800014[0].vy << 9) + g_Task->pos.y.fixed;
        tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        primitive = (TILE_1*)g_GfxPrimCursor;
        SetTile1(primitive);
        SetSemiTrans(primitive, 1);
        RotTransPers(D_1F800014, (long*)&primitive->x0, &p, &flag);
        shade         = &D_1F800004;
        primitive->r0 = *shade;
        primitive->g0 = *shade;
        primitive->b0 = *shade;
        /* Retail advances the cell by 0x24 bytes here, more than the tile takes. */
        Area_AddCellPrim(x, y, 0, 0x24);
    }
}
