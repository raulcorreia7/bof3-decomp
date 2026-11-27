#include "magic100_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    PartyMember* counter;
    u8           slot;
    u8           count;
    u32          i;
    u32          odd;

    SELF(PartyMember)->facing       = g_BattleEffectBattler->facing;
    SELF(PartyMember)->pos.x.fixed  = g_BattleEffectBattler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = g_BattleEffectBattler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed  = g_Battle.selected_actor->pos.z.fixed;
    SELF(PartyMember)->unk_09       = 0;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    i   = 0;
    odd = 1;
    do {
        slot                              = Battle_AllocEffect(1, 10) & BYTE_MASK;
        work                              = SELF(PartyMember);
        g_BattleEffects[slot].header.mode = 0;
        g_BattleEffects[slot].unk_0B      = i;
        g_BattleEffects[slot].arg.unk_09  = odd;
        counter                           = SELF(PartyMember);
        /* FAKE: the target link stays before the loop counter update. */
        FAKE_ORDER_LOCK(g_BattleEffects[slot].target.party = work);
        count = counter->param.unk_0B;
        i += 1;
        counter->param.unk_0B = count + 1;
        odd += 2;
    } while (i < 8);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0));
}

MATCH void func_801EED9C(void) {
    if (SELF(PartyMember)->unk_09 != 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        SELF(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEE58 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(D_801EFDD0, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        func_801EF434();
        func_801EF4E8();
        PopMatrix();
        func_801EF8E8();
        func_801EF9D4();
        PopMatrix();
    }
}

MATCH s32 func_801EEF3C(void) {
    PartyMember* battler;
    PartyMember* work;

    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
        SELF(PartyMember)->unk_0C = 0x60000;
        SELF(PartyMember)->unk_10 = 0;
        Effect_RotatePosition(g_Self);
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + SELF(PartyMember)->unk_0C;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + SELF(PartyMember)->unk_10;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        SELF(PartyMember)->facing      = g_BattleEffectBattler->facing;
        battler                        = g_BattleEffectBattler;
        work                           = SELF(PartyMember);
        WorldPos_Copy(&work->pos, &battler->pos);
        SELF(PartyMember)->unk_20 = (ratan2(battler->pos.x.fixed - work->pos.x.fixed, battler->pos.y.fixed - work->pos.y.fixed) + 0x800) & ANGLE_MASK;
        if (SELF(PartyMember)->param.unk_0B & 1) {
            SELF(PartyMember)->unk_18 = -((rand() & 3) + 4);
        } else {
            SELF(PartyMember)->unk_18 = (rand() & 3) + 4;
        }
        SELF(PartyMember)->unk_1C = (rand() & 0x30) + 0x50;
        SELF(PartyMember)->timer  = 0;
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF0D8(void) {
    u32          slot;
    PartyMember* battler;
    u8           timer;

    slot = LOBU(g_Battle.target_selector);
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    if (SELF(PartyMember)->param.unk_0B & 0x1) {
        SELF(PartyMember)->unk_20 = (SELF(PartyMember)->unk_20 + 0x200) & ANGLE_MASK;
    } else {
        SELF(PartyMember)->unk_20 = (SELF(PartyMember)->unk_20 - 0x200) & ANGLE_MASK;
    }
    SELF(PartyMember)->unk_14 = func_800AF4A0(battler, 0xC000, SELF(PartyMember)->unk_18 << 6);
    timer                     = SELF(PartyMember)->timer + 4;
    SELF(PartyMember)->timer  = timer;
    if (timer == 16) {
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF1DC(void) {
    u32          slot;
    PartyMember* battler;

    slot = LOBU(g_Battle.target_selector);
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    if (SELF(PartyMember)->param.unk_0B & 0x1) {
        SELF(PartyMember)->unk_20 = (SELF(PartyMember)->unk_20 + 0x200) & ANGLE_MASK;
    } else {
        SELF(PartyMember)->unk_20 = (SELF(PartyMember)->unk_20 - 0x200) & ANGLE_MASK;
    }
    SELF(PartyMember)->unk_10 = SELF(PartyMember)->unk_14;
    SELF(PartyMember)->unk_14 = func_800AF4A0(battler, 0xC000, SELF(PartyMember)->unk_18 << 6);
    if (func_800AF66C((BattleRange*)battler, 0xC000) == 0) {
        SELF(PartyMember)->unk_10 = (SELF(PartyMember)->unk_10 & ANGLE_MASK) - (SELF(PartyMember)->unk_14 & ANGLE_MASK);
        if (SELF(PartyMember)->unk_10 < 0) {
            SELF(PartyMember)->unk_10 = ~SELF(PartyMember)->unk_10 + 1;
        }
        if (SELF(PartyMember)->unk_10 <= 0x400 || SELF(PartyMember)->unk_10 >= 0xC00) {
            return;
        }
    }
    g_BattleEffectBattler->unk_09++;
    SELF(PartyMember)->header.step++;
}

MATCH void func_801EF358(void) {
    PartyMember* setup_task;
    PartyMember* position_task;
    PartyMember* timer_task;
    PartyMember* battler;
    s32          angle;
    u8           timer;

    setup_task         = SELF(PartyMember);
    setup_task->unk_0C = 0x1000;
    setup_task->unk_10 = 0;
    Effect_RotatePosition(setup_task);
    position_task              = SELF(PartyMember);
    position_task->pos.x.fixed = position_task->pos.x.fixed + position_task->unk_0C;
    position_task->pos.y.fixed = position_task->pos.y.fixed + position_task->unk_10;
    COORD_INT(position_task->pos.z) += 0x40;
    if (position_task->param.unk_0B & 1) {
        angle = position_task->unk_20 + ANGLE_45;
    } else {
        angle = position_task->unk_20 - ANGLE_45;
    }
    position_task->unk_20 = angle & ANGLE_MASK;
    FAKE_BARRIER(); /* FAKE: keeps the timer load after the angle store. */
    timer_task        = SELF(PartyMember);
    timer             = timer_task->timer - 1;
    timer_task->timer = timer;
    if (timer == 0) {
        battler = g_BattleEffectBattler;
        battler->param.unk_0B -= 1;
        Effect_Reset();
    }
}

MATCH void func_801EF434(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    setVector(&rot, 0, 0, 0);
    setVector(&pos, (SELF(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (SELF(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -(COORD_INT(SELF(PartyMember)->pos.z) + 0x100) / 2);
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EF4E8(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    s16      phase;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_1C + FIXED_MUL(rsin(0), SELF(PartyMember)->unk_1C / 2);
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_1C;
    phase                        = (SELF(PartyMember)->unk_20 / 64) & 0x3F;
    g_ScratchPad.cells.halves[4] = phase;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->timer * 12;
    g_ScratchPad.cells.halves[3] = SELF(PartyMember)->timer;
    g_ScratchPad.cells.halves[5] = phase << 6;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(phase << 6), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]);
    for (i = 1; i < 32; i++) {
        g_ScratchPad.cells.halves[5] = ((i + g_ScratchPad.cells.halves[4]) & 0x3F) * 64;
        g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_1C + FIXED_MUL(rsin(i << 6), SELF(PartyMember)->unk_1C / 2);
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = 0;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[0]), 0);
        setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, 0);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]), 0);
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        PSX_SET_SEMI_TRANSPARENT(prim);
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        setRGB3(prim, g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3], g_ScratchPad.cells.halves[3]);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF8E8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, 0);
    pos.vx = (SELF(PartyMember)->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (SELF(PartyMember)->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    if (SELF(PartyMember)->header.step < 3) {
        pos.vz = -COORD_INT(SELF(PartyMember)->pos.z) / 2;
    } else {
        pos.vz = -(s16)Area_HeightSample(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed) / 2;
    }
    RotTransMatrix(&pos, matrix, &flags);
    Camera_SetModelMatrix(&rot, &matrix);
}

MATCH void func_801EF9D4(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      tpage;
    s32      i;
    s16      phase;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_1C - 0x20;
    g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] + FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1] / 2);
    phase                        = (SELF(PartyMember)->unk_20 / 64) & 0x3F;
    g_ScratchPad.cells.halves[4] = phase;
    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->timer * 2;
    g_ScratchPad.cells.halves[5] = phase << 6;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(phase << 6), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]);
    for (i = 1; i < 32; i++) {
        g_ScratchPad.cells.halves[5] = ((i + g_ScratchPad.cells.halves[4]) & 0x3F) * 64;
        g_ScratchPad.cells.halves[0] = g_ScratchPad.cells.halves[1] + FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[1] / 2);
        g_ScratchPadVectors[0].vx    = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy    = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz    = 0;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[0]), 0);
        setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, 0);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(g_ScratchPad.cells.halves[5]), g_ScratchPad.cells.halves[1]), 0);
        prim = GFX_BeginPolyG4(1);
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_AddDitheredDrawMode(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}
