#include "magic226_03.h"
#include "sys/scene.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlots.h"

/* func_801EED18 */
MATCH void BMagic_MeteorStrikeInit(void) {
    u16* dst;
    u16* src;
    u32  slot;
    s32  i;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    Battle_ProjectRange();
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT) {
            SELF(PartyMember)->facing = g_BattleActiveActor->facing;
        } else {
            SELF(PartyMember)->facing = g_BattleActiveActor->facing ^ 2;
        }
    } else if (g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) {
        SELF(PartyMember)->facing = g_BattleActiveActor->facing;
    } else {
        SELF(PartyMember)->facing = g_BattleActiveActor->facing ^ 2;
    }
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0x10;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_METEOR_STRIKE) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    SELF(PartyMember)->param.unk_0B += 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    i   = 0;
    dst = g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    src = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors;
    for (; i < 16; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_AreaPaletteCopy->rows[AREA_PALETTE_BMAGIC_ROW].colors[0]   = g_AreaPaletteArena->rows[AREA_PALETTE_BMAGIC_ROW].colors[0];
    g_GfxPalettePending                                          = 1;
}

#include "overlays/bmagic/shared/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EF004 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EF048 */
MATCH void BMagic_MeteorStrikeUpdate(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(g_BMagicMeteorStrikeSteps, SELF(PartyMember)->header.step);
    if ((SELF(PartyMember)->header.flags & BMAGIC_EFFECT_IN_USE) != 0 && SELF(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        Area_AddGridActor();
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
/* func_801EF10C */
MATCH void BMagic_MeteorStrikeStart(void) {
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->facing      = g_BattleEffectBattler->facing;
    SELF(PartyMember)->unk_0C      = 0x20000;
    SELF(PartyMember)->unk_10      = 0;
    SELF(PartyMember)->unk_14      = TO_COORD(2304);
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed += SELF(PartyMember)->unk_10;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_0C      = -0x1000;
    SELF(PartyMember)->unk_10      = 0;
    SELF(PartyMember)->unk_20      = 0x300000;
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->unk_25       = 0x1D;
    SELF(PartyMember)->unk_26       = 0;
    SELF(PartyMember)->unk_27       = 0x1A;
    SELF(PartyMember)->unk_28       = 1;
    SELF(PartyMember)->scale.x      = 0x10000;
    SELF(PartyMember)->scale.y      = 0x10000;
    SELF(PartyMember)->unk_48       = 0;
    SELF(PartyMember)->unk_5D       = 0;
    SELF(PartyMember)->unk_5E       = 0;
    SELF(PartyMember)->unk_5F       = 0;
    SELF(PartyMember)->unk_5C       = 0;
    SELF(PartyMember)->unk_2A       = 0;
    SELF(PartyMember)->unk_29       = 4;
    SELF(PartyMember)->unk_2C.value = 0;
    SELF(PartyMember)->unk_2B       = 0;
    SELF(PartyMember)->unk_24       = 0;
    Script_Select(0);
    SELF(PartyMember)->unk_04       = 0;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 32;
    SELF(PartyMember)->timer        = 16;
    SELF(PartyMember)->header.step += 1;
}

/* func_801EF310 */
MATCH void BMagic_MeteorStrikeFall(void) {
    PartyMember* work;
    PartyMember* owner;
    PartyMember* battler;
    u8           count;
    u8           i;
    u32          index;
    u8           shade;
    u8           slot;

    work = SELF(PartyMember);
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    work->unk_14 -= work->unk_20;
    work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + work->unk_14;
    work->param.unk_0B += 6;
    if ((g_FrameCount & 3) == 0) {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            owner                                  = SELF(PartyMember);
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = BMAGIC_METEOR_STRIKE_SLOT_RING;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
            SELF(PartyMember)->unk_04 += 1;
        }
    }
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if ((count & BYTE_MASK) != 0) {
        return;
    }
    i = 0;
    do {
        slot = BMagic_AllocEffect();
        if (slot != GAME_NONE) {
            battler                                = g_BattleEffectBattler;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = BMAGIC_METEOR_STRIKE_SLOT_FRAGMENT;
            BMAGIC_EFFECT_SLOTS[slot].target.party = battler;
            index                                  = i;
            shade                                  = g_BMagicMeteorStrikeFragmentTints[index >> 3];
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = index & 7;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = (index >> 3) * 3 + 1;
            BMAGIC_EFFECT_SLOTS[slot].unk_5D       = shade;
            BMAGIC_EFFECT_SLOTS[slot].unk_0A       = D_801F0C5C[index >> 3];
            g_BattleEffectBattler->param.unk_0B += 1;
        }
        i++;
    } while (i < 0x20);
    g_AreaCameraAngle.vx += 0x14;
    SND_SEQueueSelection(0x101);
    SELF(PartyMember)->unk_09 = 8;
    SELF(PartyMember)->header.step += 1;
}

/* func_801EF540 */
MATCH void Effect_SwingCameraAngle(void) {
    BMAGIC_SWING_CAMERA(60);
}

#include "overlays/bmagic/shared/Effect_StartTint.h"

/* func_801EF698 */
MATCH void BMagic_MeteorStrikeEnd(void) {
    u8 timer_next;

    timer_next = SELF(PartyMember)->timer;
    if (timer_next != 0) {
        SELF(PartyMember)->timer = timer_next - 2;
    }
    SELF(PartyMember)->unk_5D -= 8;
    SELF(PartyMember)->unk_5E -= 8;
    SELF(PartyMember)->unk_5F -= 8;
    if ((s8)SELF(PartyMember)->unk_5D == -0x80) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActiveActorMatrix.h"

/* func_801EF814 */
#include "overlays/bmagic/shared/Effect_DrawShadedDisc.h"

#include "overlays/bmagic/shared/BMagic_DrawDarkRing.h"

/* func_801EFD84 */
MATCH void BMagic_MeteorStrikeSlotUpdate(void) {
    SYS_DISPATCH_TASK(g_BMagicMeteorStrikeSlotModes, 1, g_Self);
}

/* func_801EFDC8 */
MATCH void BMagic_MeteorStrikeFragmentUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicMeteorStrikeFragmentSteps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        BMagic_MeteorStrikeDrawFragment();
    }
}

/* Starts the meteor's arc: places it on a radius-24 ring at the ticker's angle, picks the rise speed and its fall
 * rate, then waits 32 frames. */
/* func_801EFE48 */
MATCH void BMagic_MeteorStrikeFragmentLaunch(void) {
    s16* angle_cell;
    s32  phase;

    if (--SELF(PartyMember)->unk_09 == 0) {
        angle_cell                     = &D_1F800004;
        phase                          = (SELF(PartyMember)->param.unk_0B - 2) & 0xF;
        *angle_cell                    = phase << 8;
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 8)) * 24;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * 24;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->unk_14      = g_BMagicMeteorStrikeFragmentRiseSpeeds[SELF(PartyMember)->param.unk_0B & 0x3];
        SELF(PartyMember)->unk_20      = -(SELF(PartyMember)->unk_14 / 16);
        SELF(PartyMember)->unk_5E      = 16;
        SELF(PartyMember)->unk_09      = 32;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Moves the effect in a circle of radius 2 around its origin by the angle byte 0x0B, arcs it in z with its
 * velocity, and relaunches the arc every 16 frames from the rise speed the ticker picks. */
/* func_801EFF88 */
MATCH void BMagic_MeteorStrikeFragmentRise(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell  = &D_1F800004;
    phase       = (SELF(PartyMember)->param.unk_0B - 2) & 0xF;
    /* kept: (s16) types the rsin angle; without it GCC loads the ticker into a0 and the body is 4 bytes short. */
    *angle_cell = phase << 8;
    SELF(PartyMember)->pos.x.fixed += rsin((s16)(phase << 8)) * 2;
    SELF(PartyMember)->pos.y.fixed += rcos(*angle_cell) * 2;
    SELF(PartyMember)->pos.z.fixed += SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        SELF(PartyMember)->unk_14 = g_BMagicMeteorStrikeFragmentRiseSpeeds[SELF(PartyMember)->param.unk_0B & 0x3];
        SELF(PartyMember)->unk_20 = -(SELF(PartyMember)->unk_14 / 8);
        SELF(PartyMember)->unk_09 = 16;
        SELF(PartyMember)->header.step += 1;
    }
}

/* Rocks the effect by the angle its ticker selects, drifts it along z by its velocity, and clears it when its
 * counter runs out. */
/* func_801F00B0 */
MATCH void BMagic_MeteorStrikeFragmentFall(void) {
    s16* angle_cell;
    s32  angle;
    s8   timer;

    angle_cell  = &D_1F800004;
    angle       = (SELF(PartyMember)->param.unk_0B - 2) & 0xF;
    *angle_cell = angle << 8;
    SELF(PartyMember)->pos.x.fixed += rsin((s16)(angle << 8));
    SELF(PartyMember)->pos.y.fixed += rcos(*angle_cell);
    SELF(PartyMember)->pos.z.fixed += SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    timer = SELF(PartyMember)->unk_5E;
    if (timer != 0) {
        SELF(PartyMember)->unk_5E = timer - 1;
    }
    if (--SELF(PartyMember)->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        Actor_Clear();
    }
}

/* func_801F01B8 */
MATCH void BMagic_MeteorStrikeDrawFragment(void) {
    POLY_FT4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[5] = (s8)SELF(PartyMember)->unk_5E * 6;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->timer;
    prim                         = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]),
           SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]),
           SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]),
           SELF(PartyMember)->screen_x.value + FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), SELF(PartyMember)->screen_y.value + FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, SELF(PartyMember)->unk_5D + g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[5]);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_FT4));
}

/* func_801F04D4 */
MATCH void BMagic_MeteorStrikeRingUpdate(void) {
    BMAGIC_DISPATCH_AND_DRAW(g_BMagicMeteorStrikeRingSteps, BMagic_MeteorStrikeDrawRing);
}

/* func_801F055C */
MATCH void BMagic_MeteorStrikeRingPlace(void) {
    PartyMember* src;
    PartyMember* dst;
    s32          z;

    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->facing = BATTLE_ACTIVE_WORK->facing;
        src                       = BATTLE_ACTIVE_WORK;
        dst                       = SELF(PartyMember);
        dst->pos.x.fixed          = src->pos.x.fixed;
        dst->pos.y.fixed          = src->pos.y.fixed;
        z                         = src->pos.z.fixed;
        dst->unk_14               = 0x60000;
        dst->unk_09               = 8;
        dst->pos.z.fixed          = z - (3 << 24);
        SELF(PartyMember)->timer  = 16;
        SELF(PartyMember)->header.step++;
    }
}

/* func_801F061C */
MATCH void BMagic_MeteorStrikeRingRise(void) {
    PartyMember* src;
    PartyMember* work;
    u8           count;

    src               = g_BattleEffectBattler;
    work              = SELF(PartyMember);
    work->pos.x.fixed = src->pos.x.fixed;
    work->pos.y.fixed = src->pos.y.fixed;
    work->pos.z.fixed -= work->unk_14;
    count        = work->unk_09 + 1;
    work->unk_09 = count;
    if (count == 24) {
        SELF(PartyMember)->header.step++;
    }
}

/* func_801F068C */
MATCH void BMagic_MeteorStrikeRingFade(void) {
    PartyMember* battler;
    PartyMember* task;

    SELF(PartyMember)->unk_09 += 1;
    SELF(PartyMember)->timer -= 2;
    battler           = g_BattleEffectBattler;
    task              = SELF(PartyMember);
    task->pos.x.fixed = battler->pos.x.fixed;
    task->pos.y.fixed = battler->pos.y.fixed;
    task->pos.z.fixed -= task->unk_14;
    if (task->timer == 0) {
        battler->unk_04 -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

/* func_801F07D4 */
MATCH void BMagic_MeteorStrikeDrawRing(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_09 * 24;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_09 << 5;
    g_ScratchPad.cells.halves[5] = SELF(PartyMember)->timer * 12;
    g_ScratchPad.cells.halves[6] = SELF(PartyMember)->timer * 6;
    g_ScratchPad.cells.halves[7] = SELF(PartyMember)->timer * 6;
    g_ScratchPadVectors[0].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[0].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[1].vz    = -64;
    g_ScratchPadVectors[0].vz    = -64;
    g_ScratchPadVectors[2].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[2].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vz    = 0;
    g_ScratchPadVectors[2].vz    = 0;
    for (i = 1; i <= 32; i++) {
        g_ScratchPadVectors[1].vx = g_ScratchPadVectors[0].vx;
        g_ScratchPadVectors[1].vy = g_ScratchPadVectors[0].vy;
        g_ScratchPadVectors[0].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[1]);
        g_ScratchPadVectors[3].vx = g_ScratchPadVectors[2].vx;
        g_ScratchPadVectors[3].vy = g_ScratchPadVectors[2].vy;
        g_ScratchPadVectors[2].vx = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.halves[0]);
        g_ScratchPadVectors[2].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.halves[0]);
        x                         = (g_ScratchPadVectors[2].vx << 9) + SELF(PartyMember)->pos.x.fixed;
        y                         = (g_ScratchPadVectors[2].vy << 9) + SELF(PartyMember)->pos.y.fixed;
        tpage                     = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(x, y, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        setRGB0(prim, 1, 1, 1);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        setRGB3(prim, g_ScratchPad.cells.halves[5], g_ScratchPad.cells.halves[6], g_ScratchPad.cells.halves[7]);
        /* Retail advances the cursor 40 bytes, a POLY_FT4, past this 36-byte POLY_G4. */
        Area_CellAddPrim(x, y, 0, sizeof(POLY_FT4));
    }
}

/* func_801F0B8C */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F0BF0 */
#include "overlays/bmagic/shared/Actor_Clear.h"
