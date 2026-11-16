#include "magic226_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlots.h"

MATCH void func_801EED18(void) {
    u16* dst;
    u16* src;
    u32  slot;
    s32  i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    Battle_ProjectRange();
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT) {
            g_Task->facing = D_8014637C->facing;
        } else {
            g_Task->facing = D_8014637C->facing ^ 2;
        }
    } else if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        g_Task->facing = D_8014637C->facing;
    } else {
        g_Task->facing = D_8014637C->facing ^ 2;
    }
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x10;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 0x5F) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_Task->param.unk_0B += 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0));
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 256; i++) {
        *dst++ = *src++ | 0x8000;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    for (; i < 16; i++) {
        *dst++ = *src++ | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                      = 1;
}

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF004 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF048(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0C44, g_Task->header.step);
    if ((g_Task->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_8014D290();
        Effect_SetActiveActorMatrix();
        Effect_DrawShadedDisc();
        BMagic_DrawDarkRing();
        PopMatrix();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

/* Starts the meteor above the battler: copies its pose, rotates the unk_0C/unk_10 pair by the
 * facing and adds it to x and y, puts z at the battler's z plus 2304, then sets the drift, tint,
 * scale, timer and script. */
MATCH void func_801EF10C(void) {
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    g_Task->facing      = g_BattleEffectBattler->facing;
    g_Task->unk_0C      = 0x20000;
    g_Task->unk_10      = 0;
    g_Task->unk_14      = TO_COORD(2304);
    Effect_RotatePosition(g_Task);
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + g_Task->unk_14;
    g_Task->unk_0C      = -0x1000;
    g_Task->unk_10      = 0;
    g_Task->unk_20      = 0x300000;
    Effect_RotatePosition(g_Task);
    g_Task->unk_25      = 0x1D;
    g_Task->unk_26      = 0;
    g_Task->unk_27      = 0x1A;
    g_Task->unk_28      = 1;
    g_Task->scale.x     = 0x10000;
    g_Task->scale.y     = 0x10000;
    g_Task->unk_48      = 0;
    g_Task->unk_5D      = 0;
    g_Task->unk_5E      = 0;
    g_Task->unk_5F      = 0;
    g_Task->unk_5C      = 0;
    g_Task->unk_2A      = 0;
    g_Task->unk_29      = 4;
    g_Task->unk_2C.half = 0;
    g_Task->unk_2B      = 0;
    g_Task->unk_24      = 0;
    Actor_SelectScript(0);
    g_Task->unk_04       = 0;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 32;
    g_Task->timer        = 16;
    g_Task->header.step += 1;
}

MATCH void func_801EF310(void) {
    PartyMember* work;
    PartyMember* owner;
    PartyMember* battler;
    u8           count;
    u8           i;
    u32          index;
    u8           shade;
    u8           slot;

    work = g_Task;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    work->unk_14 -= work->unk_20;
    work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + work->unk_14;
    work->param.unk_0B += 6;
    if ((g_FrameCount & 3) == 0) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            owner                                  = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 1;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
            g_Task->unk_04 += 1;
        }
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) != 0) {
        return;
    }
    i = 0;
    do {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            battler                                = g_BattleEffectBattler;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
            index                                  = i;
            shade                                  = D_801F0C58[index >> 3];
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = index & 7;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (index >> 3) * 3 + 1;
            BMAGIC_EFFECT_SLOTS[slot].unk_5D       = shade;
            BMAGIC_EFFECT_SLOTS[slot].unk_0A       = D_801F0C5C[index >> 3];
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        i++;
    } while (i < 0x20);
    g_AreaCameraAngle.vx += 0x14;
    SND_QueueSelectionEffect(0x101);
    g_Task->unk_09 = 8;
    g_Task->header.step += 1;
}

/* func_801EF540 */
MATCH void Effect_SwingCameraAngle(void) {
    BMAGIC_SWING_CAMERA(60);
}

#include "overlays/bmagic/Effect_StartTint.h"

MATCH void func_801EF698(void) {
    u8 timer_next;

    timer_next = g_Task->timer;
    if (timer_next != 0) {
        g_Task->timer = timer_next - 2;
    }
    g_Task->unk_5D -= 8;
    g_Task->unk_5E -= 8;
    g_Task->unk_5F -= 8;
    if ((s8)g_Task->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

/* func_801EF814 */
#include "overlays/bmagic/Effect_DrawShadedDisc.h"

#include "overlays/bmagic/BMagic_DrawDarkRing.h"

MATCH void func_801EFD84(void) {
    SYS_DISPATCH_TASK(D_801F0C60, 1, g_Task);
}

MATCH void func_801EFDC8(void) {
    SYS_DISPATCH_BYTE(D_801F0C78, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801F01B8();
    }
}

/* Starts the meteor's arc: places it on a radius-24 ring at the ticker's angle, picks the rise speed and its fall
 * rate, then waits 32 frames. */
MATCH void func_801EFE48(void) {
    s16* angle_cell;
    s32  phase;

    if (--g_Task->unk_09 == 0) {
        angle_cell          = &D_1F800004;
        phase               = (g_Task->param.unk_0B - 2) & 0xF;
        *angle_cell         = phase << 8;
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 8)) * 24;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * 24;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->unk_14      = D_801F0C68[g_Task->param.unk_0B & 0x3];
        g_Task->unk_20      = -(g_Task->unk_14 / 16);
        g_Task->unk_5E      = 16;
        g_Task->unk_09      = 32;
        g_Task->header.step += 1;
    }
}

/* Moves the effect in a circle of radius 2 around its origin by the angle byte 0x0B, arcs it in z with its
 * velocity, and relaunches the arc every 16 frames from the rise speed the ticker picks. */
MATCH void func_801EFF88(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = (g_Task->param.unk_0B - 2) & 0xF;
    /* kept: (s16) types the rsin angle; without it GCC loads the ticker into a0 and the body is 4 bytes short. */
    *angle_cell = phase << 8;
    g_Task->pos.x.fixed += rsin((s16)(phase << 8)) * 2;
    g_Task->pos.y.fixed += rcos(*angle_cell) * 2;
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        g_Task->unk_14 = D_801F0C68[g_Task->param.unk_0B & 0x3];
        g_Task->unk_20 = -(g_Task->unk_14 / 8);
        g_Task->unk_09 = 16;
        g_Task->header.step += 1;
    }
}

/* Rocks the effect by the angle its ticker selects, drifts it along z by its velocity, and clears it when its
 * counter runs out. */
MATCH void func_801F00B0(void) {
    s16* angle_cell;
    s32  angle;
    s8   timer;

    angle_cell  = &D_1F800004;
    angle       = (g_Task->param.unk_0B - 2) & 0xF;
    *angle_cell = angle << 8;
    g_Task->pos.x.fixed += rsin((s16)(angle << 8));
    g_Task->pos.y.fixed += rcos(*angle_cell);
    g_Task->pos.z.fixed += g_Task->unk_14;
    g_Task->unk_14 += g_Task->unk_20;
    timer = g_Task->unk_5E;
    if (timer != 0) {
        g_Task->unk_5E = timer - 1;
    }
    if (--g_Task->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

MATCH void func_801F01B8(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 1, 320, 256), 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.cells.halves[5] = (s8)g_Task->unk_5E * 6;
    D_1F800000.cells.halves[0] = g_Task->timer;
    prim                       = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, g_Task->unk_2E.half + FIXED_MUL(rcos(512), D_1F800000.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(512), D_1F800000.cells.halves[0]),
           g_Task->unk_2E.half + FIXED_MUL(rcos(1536), D_1F800000.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(1536), D_1F800000.cells.halves[0]),
           g_Task->unk_2E.half + FIXED_MUL(rcos(3584), D_1F800000.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(3584), D_1F800000.cells.halves[0]),
           g_Task->unk_2E.half + FIXED_MUL(rcos(2560), D_1F800000.cells.halves[0]), g_Task->unk_30.half + FIXED_MUL(rsin(2560), D_1F800000.cells.halves[0]));
    prim->tpage = GetTPage(0, 1, 832, 256);
    prim->clut  = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, g_Task->unk_5D + D_1F800000.cells.halves[5], D_1F800000.cells.halves[5], D_1F800000.cells.halves[5]);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_FT4));
}

MATCH void func_801F04D4(void) {
    SYS_DISPATCH_BYTE(D_801F0C84, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F07D4();
        PopMatrix();
    }
}

MATCH void func_801F055C(void) {
    PartyMember* src;
    PartyMember* dst;
    s32          z;

    if (--g_Task->unk_09 == 0) {
        g_Task->facing   = BATTLE_ACTIVE_WORK->facing;
        src              = BATTLE_ACTIVE_WORK;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        z                = src->pos.z.fixed;
        dst->unk_14      = 0x60000;
        dst->unk_09      = 8;
        dst->pos.z.fixed = z - (3 << 24);
        g_Task->timer    = 16;
        g_Task->header.step++;
    }
}

MATCH void func_801F061C(void) {
    PartyMember* src;
    PartyMember* work;
    u8           count;

    src               = g_BattleEffectBattler;
    work              = g_Task;
    work->pos.x.fixed = src->pos.x.fixed;
    work->pos.y.fixed = src->pos.y.fixed;
    work->pos.z.fixed -= work->unk_14;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    if (count == 24) {
        g_Task->header.step++;
    }
}

MATCH void func_801F068C(void) {
    PartyMember* battler;
    PartyMember* task;

    g_Task->unk_09 += 1;
    g_Task->timer -= 2;
    battler           = g_BattleEffectBattler;
    task              = g_Task;
    task->pos.x.fixed = battler->pos.x.fixed;
    task->pos.y.fixed = battler->pos.y.fixed;
    task->pos.z.fixed -= task->unk_14;
    if (task->timer == 0) {
        battler->unk_04 -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801F07D4(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;

    D_1F800000.cells.halves[0] = g_Task->unk_09 * 24;
    D_1F800000.cells.halves[1] = g_Task->unk_09 << 5;
    D_1F800000.cells.halves[5] = g_Task->timer * 12;
    D_1F800000.cells.halves[6] = g_Task->timer * 6;
    D_1F800000.cells.halves[7] = g_Task->timer * 6;
    D_1F800014[0].vx           = FIXED_MUL(rsin(0), D_1F800000.cells.halves[1]);
    D_1F800014[0].vy           = FIXED_MUL(rcos(0), D_1F800000.cells.halves[1]);
    D_1F800014[1].vz           = -64;
    D_1F800014[0].vz           = -64;
    D_1F800014[2].vx           = FIXED_MUL(rsin(0), D_1F800000.cells.halves[0]);
    D_1F800014[2].vy           = FIXED_MUL(rcos(0), D_1F800000.cells.halves[0]);
    D_1F800014[3].vz           = 0;
    D_1F800014[2].vz           = 0;
    for (i = 1; i <= 32; i++) {
        D_1F800014[1].vx = D_1F800014[0].vx;
        D_1F800014[1].vy = D_1F800014[0].vy;
        D_1F800014[0].vx = FIXED_MUL(rsin(i << 7), D_1F800000.cells.halves[1]);
        D_1F800014[0].vy = FIXED_MUL(rcos(i << 7), D_1F800000.cells.halves[1]);
        D_1F800014[3].vx = D_1F800014[2].vx;
        D_1F800014[3].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 7), D_1F800000.cells.halves[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 7), D_1F800000.cells.halves[0]);
        x                = (D_1F800014[2].vx << 9) + g_Task->pos.x.fixed;
        y                = (D_1F800014[2].vy << 9) + g_Task->pos.y.fixed;
        tpage            = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, D_1F800000.cells.halves[5], D_1F800000.cells.halves[6], D_1F800000.cells.halves[7]);
        setRGB3(prim, D_1F800000.cells.halves[5], D_1F800000.cells.halves[6], D_1F800000.cells.halves[7]);
        /* Retail advances the cursor 40 bytes, a POLY_FT4, past this 36-byte POLY_G4. */
        Area_AddCellPrim(x, y, 0, sizeof(POLY_FT4));
    }
}

/* func_801F0B8C */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F0BF0 */
#include "overlays/bmagic/Actor_Clear.h"
