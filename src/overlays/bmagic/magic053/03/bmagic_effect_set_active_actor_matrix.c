#include "magic053_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EF0A8(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0554, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags & 0x1) {
        if (SELF(PartyMember)->header.step != 0) {
            if (SELF(PartyMember)->header.step < 4) {
                Battle_ProjectRange();
                Area_AddGridActor();
                Effect_SetActiveActorMatrix();
                Effect_DrawShadedDisc();
                BMagic_DrawDarkRing();
                PopMatrix();
            }
        }
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF174(void) {
    PartyMember* work;
    PartyMember* sprite;
    s16*         angle;
    u8           count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        angle                          = &g_ScratchPad.cells.halves[2];
        *angle                         = SELF(PartyMember)->param.unk_0B << 9;
        g_ScratchPad.cells.halves[0]   = (rand() & 0x10) + 0x18;
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(*angle) * g_ScratchPad.cells.halves[0];
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle) * g_ScratchPad.cells.halves[0];
        SELF(PartyMember)->facing      = g_BattleEffectBattler->facing;
        SELF(PartyMember)->unk_0C      = 0x20000;
        SELF(PartyMember)->unk_10      = 0;
        SELF(PartyMember)->unk_14      = TO_COORD(1536);
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed += SELF(PartyMember)->unk_10;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + SELF(PartyMember)->unk_14;
        SELF(PartyMember)->unk_0C      = -0x2000;
        SELF(PartyMember)->unk_10      = 0;
        SELF(PartyMember)->unk_20      = 0x600000;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->unk_25 = 0x1D;
        SELF(PartyMember)->unk_26 = 0;
        SELF(PartyMember)->unk_27 = 0x1A;
        SELF(PartyMember)->unk_28 = 1;
        work                      = SELF(PartyMember);
        work->unk_48              = 2;
        work->scale.x             = 0x10000;
        work->scale.y             = 0x10000;
        SELF(PartyMember)->unk_5D = 0;
        SELF(PartyMember)->unk_5E = 0;
        SELF(PartyMember)->unk_5F = 0;
        SELF(PartyMember)->unk_5C = 0;
        SELF(PartyMember)->unk_2A = 0;
        SELF(PartyMember)->unk_29 = 4;
        sprite                    = SELF(PartyMember);
        sprite->unk_2B            = 1;
        sprite->unk_2C.value      = 0;
        SELF(PartyMember)->unk_24 = 0;
        Script_Select(0);
        SELF(PartyMember)->param.unk_0B = 0;
        SELF(PartyMember)->unk_09       = 16;
        SELF(PartyMember)->timer        = 16;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF420(void) {
    PartyMember* work;
    PartyMember* owner;
    u8           count;
    u8           i;
    u8           slot;

    work = SELF(PartyMember);
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    work->unk_14 -= work->unk_20;
    work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + work->unk_14;
    work->param.unk_0B += 8;
    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (SELF(PartyMember)->unk_04 & 1) {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x01));
        } else {
            SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
        }
        SELF(PartyMember)->unk_04 = 0;
        for (i = 0; i < 8; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                owner                                  = SELF(PartyMember);
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
                SELF(PartyMember)->unk_04++;
            }
        }
        Script_Select(1);
        g_AreaCameraAngle.vx += 0x14;
        SELF(PartyMember)->unk_09 = 4;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF5C0(void) {
    s16* state;
    u16  angle;
    u8   timer;

    Script_AnimStepOnce();
    if (SELF(PartyMember)->unk_09 & 0x1) {
        state = &g_AreaCameraAngle.vx;
        angle = *state + 0x14;
    } else {
        state = &g_AreaCameraAngle.vx;
        angle = *state - 0x14;
    }
    *state                    = angle;
    timer                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_AreaCameraAngle.vx = -0x2AAU;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF674(void) {
    u8 timer;

    timer = SELF(PartyMember)->timer;
    if (timer != 0) {
        SELF(PartyMember)->timer = timer - 2;
    }
    if (Script_AnimStepOnce() & BYTE_MASK) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF6D8(void) {
    PartyMember* work;

    if (SELF(PartyMember)->unk_04 == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Effect_Reset();
    }
}

#include "overlays/bmagic/shared/Effect_SetActiveActorMatrix.h"

/* func_801EF7E0 */
#include "overlays/bmagic/shared/Effect_DrawShadedDisc.h"

#include "overlays/bmagic/shared/BMagic_DrawDarkRing.h"

MATCH void func_801EFD50(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Self);
}

MATCH void func_801EFD94(void) {
    BMAGIC_DISPATCH_AND_DRAW(D_801F056C, func_801F01C0);
}

/* func_801EFE1C */
MATCH void BMagic_CombustionSparkPlace(void) {
    s32  r;
    s32  direction;
    s16* angle = &D_1F800004;

    r                              = rand();
    direction                      = SELF(PartyMember)->param.unk_0B;
    SELF(PartyMember)->unk_0C      = (r & 0x7) + 8;
    *angle                         = direction << 9;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * SELF(PartyMember)->unk_0C);
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * SELF(PartyMember)->unk_0C);
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    SELF(PartyMember)->unk_09      = 8;
    SELF(PartyMember)->timer       = 16;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EFF24(void) {
    PartyMember* task;
    s16*         angle_cell;
    s32          direction;
    s32          velocity;

    task       = SELF(PartyMember);
    angle_cell = &D_1F800004;
    direction  = task->param.unk_0B;
    task->unk_0C += 2;
    *angle_cell                    = direction << 9;
    velocity                       = rsin((s16)(direction << 9)) * SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + velocity;
    velocity                       = rcos(*angle_cell) * SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + velocity;
    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801F0018(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = SELF(PartyMember)->param.unk_0B;
    SELF(PartyMember)->unk_0C += 1;
    *angle_cell                    = phase << 9;
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 9)) * SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * SELF(PartyMember)->unk_0C;
    count                          = SELF(PartyMember)->timer - 1;
    SELF(PartyMember)->timer       = count;
    if (count == 0) {
        g_BattleEffectBattler->unk_04 -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801F01C0(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    g_ScratchPad.cells.halves[0] = 0x100;
    D_1F80000A                   = SELF(PartyMember)->timer * 6;
    setVector(&g_ScratchPadVectors[0], FIXED_MUL(rcos(ANGLE_45), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(ANGLE_45), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[1], FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[2], FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]), 0);
    setVector(&g_ScratchPadVectors[3], FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]), 0);
    setTPage(prim, TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    /* FAKE: a volatile store keeps the clut write ahead of the texture-point stores; the best pure-C body is 0x2C8 against retail's 0x2D4. */
    FAKE_VOLATILE(u16, prim->clut) = GetClut(0, 482);
    setUVWH(prim, 0, 128, 32, 32);
    setRGB0(prim, D_1F80000A, D_1F80000A, D_1F80000A);
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_FT4));
}

/* func_801F0494 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801F04F8 */
#include "overlays/bmagic/shared/Actor_Clear.h"
