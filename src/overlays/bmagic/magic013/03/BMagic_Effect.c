#include "magic013_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic010Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, BMAGIC_WORK->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, func_801EFDB4);
}

MATCH void func_801EED28(void) {
    PartyMember* actor;
    PartyMember* task;
    u16*         dst;
    u16*         src;
    u32          slot;
    u8           i;

    BMAGIC_CLEAR_EFFECTS(i);
    actor               = g_BattleSelectedActor;
    BMAGIC_WORK->facing = actor->facing;
    task                = g_Task;
    WorldPos_Copy(&task->pos, &actor->pos);
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    do {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
        i++;
    } while (i < 16);
    g_GfxPalettePending                = 1;
    slot                               = Battle_AllocEffect(1, 41) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    BMAGIC_WORK->param.unk_0B          = 2;
    BMAGIC_WORK->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_Pause.h"

MATCH void func_801EEEA0(void) {
    u8*          selector;
    u32          slot;
    PartyMember* work;

    selector = (u8*)&g_Battle.target_selector;
    if (!(Battle_SlotIsBlocked(*selector) & BYTE_MASK) && (Battle_CanTarget(1, *selector) & BYTE_MASK)) {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].unk_04       = 4;
        g_BattleEffects[slot].arg.unk_09   = 0x18;
        g_BattleEffects[slot].unk_0A       = 4;
        g_BattleEffects[slot].target.party = work;
        BMAGIC_WORK->param.unk_0B += 1;
    }
    BMAGIC_WORK->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEFD0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(D_801F03C0, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0) {
        func_801EF4F0();
        func_801EF79C();
        PopMatrix();
        func_801EF648();
        func_801EFAA8();
        PopMatrix();
    }
}

MATCH void func_801EF0A4(void) {
    BMAGIC_WORK->facing = g_BattleEffectBattler->facing;
    BMAGIC_WORK->unk_0C = 0x20000;
    BMAGIC_WORK->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    BMAGIC_WORK->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + BMAGIC_WORK->unk_10;
    BMAGIC_WORK->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(256);
    BMAGIC_WORK->unk_0C      = -0x6000;
    BMAGIC_WORK->unk_10      = 0;
    Effect_RotatePosition(g_Task);
    BMAGIC_WORK->unk_04       = 0;
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->unk_09       = 16;
    BMAGIC_WORK->timer        = 4;
    BMAGIC_WORK->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF1F0(void) {
    s32 i;
    u8  slot;
    u8  timer;

    BMAGIC_WORK->pos.x.fixed += BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->pos.y.fixed += BMAGIC_WORK->unk_10;
    timer               = BMAGIC_WORK->unk_09 - 4;
    BMAGIC_WORK->unk_09 = timer;
    if (timer == 0) {
        for (i = 0; i < 32; i++) {
            slot = BMagic_AllocEffect();
            if (slot != 0xFF) {
                BMAGIC_EFFECT_SLOTS[slot].target.party = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.flags |= 0x41;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B     = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09 = (rand() & 7) + 1;
                BMAGIC_WORK->param.unk_0B += 1;
            }
        }
        if (BMAGIC_WORK->timer == 4) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
        BMAGIC_WORK->unk_0C = 0x3000;
        BMAGIC_WORK->unk_10 = 0;
        Effect_RotatePosition(g_Task);
        SND_SEQueueSelection(0x100);
        BMAGIC_WORK->header.step += 1;
    }
}

MATCH void func_801EF36C(void) {
    s32 limit;
    u8  count;

    BMAGIC_WORK->pos.x.fixed += BMAGIC_WORK->unk_0C;
    BMAGIC_WORK->pos.y.fixed += BMAGIC_WORK->unk_10;
    limit               = BMAGIC_WORK->timer == 1 ? 12 : 16;
    count               = BMAGIC_WORK->unk_09 + 2;
    BMAGIC_WORK->unk_09 = count;
    if (count == limit) {
        if (--BMAGIC_WORK->timer == 0) {
            Battle_MarkDamaged(g_Battle.target_selector);
            SND_SEQueueSelection(0x201);
            g_BattleEffectBattler->param.unk_0B -= 1;
            BMAGIC_WORK->header.step += 1;
        } else {
            BMAGIC_WORK->unk_0C = -0x6000;
            BMAGIC_WORK->unk_10 = 0;
            Effect_RotatePosition(g_Task);
            BMAGIC_WORK->header.step -= 1;
        }
    }
}

MATCH void func_801EF484(void) {
    PartyMember* work;
    PartyMember* active;

    work = g_Task;
    if (work->param.unk_0B == 0) {
        work->unk_04 = work->unk_04 - 1;
        if (work->unk_04 == 0) {
            active               = BATTLE_ACTIVE_WORK;
            active->param.unk_0B = active->param.unk_0B - 1;
            Effect_Reset();
        }
    }
}

MATCH void func_801EF4F0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    switch (BMAGIC_WORK->facing) {
        case 0:
            rot.vx = 0;
            rot.vy = ONE - BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            break;
        case 1:
            rot.vx = BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            rot.vy = 0;
            break;
        case 2:
            rot.vx = 0;
            rot.vy = BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            break;
        case 3:
            rot.vx = ONE - BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            rot.vy = 0;
            break;
    }
    rot.vz = 0;
    setVector(&pos, (BMAGIC_WORK->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (BMAGIC_WORK->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -(COORD_INT(BMAGIC_WORK->pos.z) + 0x20) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EF648(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    switch (BMAGIC_WORK->facing) {
        case 0:
            rot.vx = 0;
            rot.vy = BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            break;
        case 1:
            rot.vx = ONE - BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            rot.vy = 0;
            break;
        case 2:
            rot.vx = 0;
            rot.vy = ONE - BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            break;
        case 3:
            rot.vx = BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09);
            rot.vy = 0;
            break;
    }
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(BMAGIC_WORK);
}

MATCH void func_801EF79C(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    MAGIC013_DRAW_WAVE_BAND(-80);
}

MATCH void func_801EFAA8(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    MAGIC013_DRAW_WAVE_BAND(80);
}

MATCH void func_801EFDB4(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 1, g_Task);
}

MATCH void func_801EFDF8(void) {
    SYS_DISPATCH_BYTE(D_801F03DC, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->unk_09 != 0) {
        func_801F00A8();
        func_801F0164();
        PopMatrix();
    }
}

MATCH void func_801EFE80(void) {
    PartyMember* actor;
    s32*         angle_cell;
    u8           count;
    u8           phase;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (count == 0) {
        phase                    = BMAGIC_WORK->param.unk_0B;
        angle_cell               = &D_1F800004;
        *angle_cell              = phase << 7;
        actor                    = g_Battle.selected_actor;
        BMAGIC_WORK->pos.x.fixed = actor->pos.x.fixed + ((rsin(*angle_cell) * 0x100) >> 9);
        BMAGIC_WORK->pos.y.fixed = actor->pos.y.fixed + ((rcos(*angle_cell) * 0x100) >> 9);
        BMAGIC_WORK->pos.z.fixed = actor->pos.z.fixed;
        BMAGIC_WORK->unk_14      = RANDOM_MASK(7) + 0x80;
        BMAGIC_WORK->unk_20      = -0xC;
        BMAGIC_WORK->unk_09      = 16;
        BMAGIC_WORK->header.step++;
    }
}

MATCH void func_801EFF88(void) {
    s32* angle_cell;

    angle_cell  = &D_1F800004;
    *angle_cell = BMAGIC_WORK->param.unk_0B << 7;
    BMAGIC_WORK->pos.x.fixed += (rsin(*angle_cell) * 0x400) >> 9;
    BMAGIC_WORK->pos.y.fixed += (rcos(*angle_cell) * 0x400) >> 9;
    BMAGIC_WORK->unk_14 += BMAGIC_WORK->unk_20;
    COORD_INT(BMAGIC_WORK->pos.z) += BMAGIC_WORK->unk_14;
    if (--BMAGIC_WORK->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        BMAGIC_WORK->header.flags = 0;
        BMAGIC_WORK->header.mode  = 0;
        BMAGIC_WORK->header.step  = 0;
        BMAGIC_WORK->unk_03       = 0;
        BMAGIC_WORK->unk_04       = 0;
    }
}

MATCH void func_801F00A8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, BMAGIC_PHASE_ANGLE(BMAGIC_WORK->unk_09));
    BMAGIC_PROJECT_ACTOR_MATRIX(BMAGIC_WORK);
}

MATCH void func_801F0164(void) {
    POLY_F3* prim;
    long     depth;
    long     flag;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), NULL);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    setVector(&g_ScratchPadVectors[0], (u32)rsin(0) >> 8, (u32)rcos(0) >> 8, 0);
    setVector(&g_ScratchPadVectors[1], (u32)rsin(DEG(120)) >> 8, (u32)rcos(DEG(120)) >> 8, 0);
    setVector(&g_ScratchPadVectors[2], (u32)rsin(DEG(240)) >> 8, (u32)rcos(DEG(240)) >> 8, 0);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, (rand() & 0xF) * BMAGIC_WORK->unk_09, (rand() & 0xF) * BMAGIC_WORK->unk_09, (rand() & 0xF) * BMAGIC_WORK->unk_09);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(POLY_F3));
}

/* func_801F0358 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
