#include "magic013_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC14(void) {
    Magic010Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);

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
    actor                     = g_BattleSelectedActor;
    SELF(PartyMember)->facing = actor->facing;
    task                      = SELF(PartyMember);
    WorldPos_Copy(&task->pos, &actor->pos);
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    do {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
        i++;
    } while (i < 16);
    g_GfxPalettePending                = 1;
    slot                               = Battle_AllocEffect(1, 41) & BYTE_MASK;
    g_BattleEffects[slot].target.party = SELF(PartyMember);
    SELF(PartyMember)->param.unk_0B    = 2;
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_Pause.h"

MATCH void func_801EEEA0(void) {
    u8*          selector;
    u32          slot;
    PartyMember* work;

    selector = (u8*)&g_Battle.target_selector;
    if (!(Battle_SlotIsBlocked(*selector) & BYTE_MASK) && (Battle_CanTarget(1, *selector) & BYTE_MASK)) {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].unk_04       = 4;
        g_BattleEffects[slot].arg.unk_09   = 0x18;
        g_BattleEffects[slot].unk_0A       = 4;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    SELF(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEFD0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF014(void) {
    SYS_DISPATCH_BYTE(D_801F03C0, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        func_801EF4F0();
        func_801EF79C();
        PopMatrix();
        func_801EF648();
        func_801EFAA8();
        PopMatrix();
    }
}

MATCH void func_801EF0A4(void) {
    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    SELF(PartyMember)->unk_0C = 0x20000;
    SELF(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
    SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(256);
    SELF(PartyMember)->unk_0C      = -0x6000;
    SELF(PartyMember)->unk_10      = 0;
    Effect_RotatePosition(g_Self);
    SELF(PartyMember)->unk_04       = 0;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 16;
    SELF(PartyMember)->timer        = 4;
    SELF(PartyMember)->header.step += 1;
}

#include "overlays/bmagic/shared/Effect_CountUpWorkByteAndStep.h"

MATCH void func_801EF1F0(void) {
    s32 i;
    u8  slot;
    u8  timer;

    SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed += SELF(PartyMember)->unk_10;
    timer                     = SELF(PartyMember)->unk_09 - 4;
    SELF(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        for (i = 0; i < 32; i++) {
            slot = BMagic_AllocEffect();
            if (slot != 0xFF) {
                BMAGIC_EFFECT_SLOTS[slot].target.party = SELF(PartyMember);
                BMAGIC_EFFECT_SLOTS[slot].header.flags |= 0x41;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B     = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09 = (rand() & 7) + 1;
                SELF(PartyMember)->param.unk_0B += 1;
            }
        }
        if (SELF(PartyMember)->timer == 4) {
            Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
        }
        SELF(PartyMember)->unk_0C = 0x3000;
        SELF(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Self);
        SND_SEQueueSelection(0x100);
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF36C(void) {
    s32 limit;
    u8  count;

    SELF(PartyMember)->pos.x.fixed += SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->pos.y.fixed += SELF(PartyMember)->unk_10;
    limit                     = SELF(PartyMember)->timer == 1 ? 12 : 16;
    count                     = SELF(PartyMember)->unk_09 + 2;
    SELF(PartyMember)->unk_09 = count;
    if (count == limit) {
        if (--SELF(PartyMember)->timer == 0) {
            Battle_MarkDamaged(g_Battle.target_selector);
            SND_SEQueueSelection(0x201);
            g_BattleEffectBattler->param.unk_0B -= 1;
            SELF(PartyMember)->header.step += 1;
        } else {
            SELF(PartyMember)->unk_0C = -0x6000;
            SELF(PartyMember)->unk_10 = 0;
            Effect_RotatePosition(g_Self);
            SELF(PartyMember)->header.step -= 1;
        }
    }
}

MATCH void func_801EF484(void) {
    PartyMember* work;
    PartyMember* active;

    work = SELF(PartyMember);
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
    switch (SELF(PartyMember)->facing) {
        case 0:
            rot.vx = 0;
            rot.vy = ONE - BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            break;
        case 1:
            rot.vx = BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            rot.vy = 0;
            break;
        case 2:
            rot.vx = 0;
            rot.vy = BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            break;
        case 3:
            rot.vx = ONE - BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            rot.vy = 0;
            break;
    }
    rot.vz = 0;
    setVector(&pos, (SELF(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (SELF(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -(COORD_INT(SELF(PartyMember)->pos.z) + 0x20) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EF648(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    switch (SELF(PartyMember)->facing) {
        case 0:
            rot.vx = 0;
            rot.vy = BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            break;
        case 1:
            rot.vx = ONE - BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            rot.vy = 0;
            break;
        case 2:
            rot.vx = 0;
            rot.vy = ONE - BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            break;
        case 3:
            rot.vx = BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09);
            rot.vy = 0;
            break;
    }
    rot.vz = 0;
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
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
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 7), 1, g_Self);
}

MATCH void func_801EFDF8(void) {
    SYS_DISPATCH_BYTE(D_801F03DC, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->unk_09 != 0) {
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

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        phase                          = SELF(PartyMember)->param.unk_0B;
        angle_cell                     = &D_1F800004;
        *angle_cell                    = phase << 7;
        actor                          = g_Battle.selected_actor;
        SELF(PartyMember)->pos.x.fixed = actor->pos.x.fixed + ((rsin(*angle_cell) * 0x100) >> 9);
        SELF(PartyMember)->pos.y.fixed = actor->pos.y.fixed + ((rcos(*angle_cell) * 0x100) >> 9);
        SELF(PartyMember)->pos.z.fixed = actor->pos.z.fixed;
        SELF(PartyMember)->unk_14      = RANDOM_MASK(7) + 0x80;
        SELF(PartyMember)->unk_20      = -0xC;
        SELF(PartyMember)->unk_09      = 16;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EFF88(void) {
    s32* angle_cell;

    angle_cell  = &D_1F800004;
    *angle_cell = SELF(PartyMember)->param.unk_0B << 7;
    SELF(PartyMember)->pos.x.fixed += (rsin(*angle_cell) * 0x400) >> 9;
    SELF(PartyMember)->pos.y.fixed += (rcos(*angle_cell) * 0x400) >> 9;
    SELF(PartyMember)->unk_14 += SELF(PartyMember)->unk_20;
    COORD_INT(SELF(PartyMember)->pos.z) += SELF(PartyMember)->unk_14;
    if (--SELF(PartyMember)->unk_09 == 0) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        SELF(PartyMember)->header.flags = 0;
        SELF(PartyMember)->header.mode  = 0;
        SELF(PartyMember)->header.step  = 0;
        SELF(PartyMember)->unk_03       = 0;
        SELF(PartyMember)->unk_04       = 0;
    }
}

MATCH void func_801F00A8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, BMAGIC_PHASE_ANGLE(SELF(PartyMember)->unk_09));
    BMAGIC_PROJECT_ACTOR_MATRIX(SELF(PartyMember));
}

MATCH void func_801F0164(void) {
    POLY_F3* prim;
    long     depth;
    long     flag;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256), NULL);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    prim = (POLY_F3*)g_GfxPrimCursor;
    SetPolyF3(prim);
    PSX_SET_SEMI_TRANSPARENT(prim);
    setVector(&g_ScratchPadVectors[0], (u32)rsin(0) >> 8, (u32)rcos(0) >> 8, 0);
    setVector(&g_ScratchPadVectors[1], (u32)rsin(DEG(120)) >> 8, (u32)rcos(DEG(120)) >> 8, 0);
    setVector(&g_ScratchPadVectors[2], (u32)rsin(DEG(240)) >> 8, (u32)rcos(DEG(240)) >> 8, 0);
    RotTransPers3(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
    setRGB0(prim, (rand() & 0xF) * SELF(PartyMember)->unk_09, (rand() & 0xF) * SELF(PartyMember)->unk_09, (rand() & 0xF) * SELF(PartyMember)->unk_09);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_F3));
}

/* func_801F0358 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"
