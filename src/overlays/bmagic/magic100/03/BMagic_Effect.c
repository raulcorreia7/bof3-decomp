#include "magic100_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

MATCH void func_801EED9C(void) {
    if (g_Task->unk_09 != 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10U);
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE58 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE9C(void) {
    SYS_DISPATCH_BYTE(D_801EFDD0, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
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

    if (--g_Task->unk_09 == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = 0x60000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
        g_Task->facing      = g_BattleEffectBattler->facing;
        battler             = g_BattleEffectBattler;
        work                = g_Task;
        WorldPos_Copy(&work->pos, &battler->pos);
        g_Task->unk_20 = (ratan2(battler->pos.x.fixed - work->pos.x.fixed, battler->pos.y.fixed - work->pos.y.fixed) + 0x800) & ANGLE_MASK;
        if (g_Task->param.unk_0B & 1) {
            g_Task->unk_18 = -((rand() & 3) + 4);
        } else {
            g_Task->unk_18 = (rand() & 3) + 4;
        }
        g_Task->unk_1C = (rand() & 0x30) + 0x50;
        g_Task->timer  = 0;
        g_Task->header.step++;
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
    if (g_Task->param.unk_0B & 0x1) {
        g_Task->unk_20 = (g_Task->unk_20 + 0x200) & ANGLE_MASK;
    } else {
        g_Task->unk_20 = (g_Task->unk_20 - 0x200) & ANGLE_MASK;
    }
    g_Task->unk_14 = func_800AF4A0(battler, 0xC000, g_Task->unk_18 << 6);
    timer          = g_Task->timer + 4;
    g_Task->timer  = timer;
    if (timer == 16) {
        g_Task->header.step++;
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
    if (g_Task->param.unk_0B & 0x1) {
        g_Task->unk_20 = (g_Task->unk_20 + 0x200) & ANGLE_MASK;
    } else {
        g_Task->unk_20 = (g_Task->unk_20 - 0x200) & ANGLE_MASK;
    }
    g_Task->unk_10 = g_Task->unk_14;
    g_Task->unk_14 = func_800AF4A0(battler, 0xC000, g_Task->unk_18 << 6);
    if (func_800AF66C((BattleRange*)battler, 0xC000) == 0) {
        g_Task->unk_10 = (g_Task->unk_10 & ANGLE_MASK) - (g_Task->unk_14 & ANGLE_MASK);
        if (g_Task->unk_10 < 0) {
            g_Task->unk_10 = ~g_Task->unk_10 + 1;
        }
        if (g_Task->unk_10 <= 0x400 || g_Task->unk_10 >= 0xC00) {
            return;
        }
    }
    g_BattleEffectBattler->unk_09++;
    g_Task->header.step++;
}

INCLUDE_ASM(func_801EF358);

MATCH void func_801EF434(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    ;
    PushMatrix();
    setVector(&rot, 0, 0, 0);
    setVector(&pos, (g_Task->pos.x.fixed >> 9) - AREA_CELL_ORIGIN, (g_Task->pos.y.fixed >> 9) - AREA_CELL_ORIGIN, -(COORD_INT(g_Task->pos.z) + 0x100) / 2);
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

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_1C + FIXED_MUL(rsin(0), g_Task->unk_1C / 2);
    D_1F800000.view.effect.params[1] = g_Task->unk_1C;
    phase                            = (g_Task->unk_20 / 64) & 0x3F;
    D_1F800000.view.effect.params[4] = phase;
    D_1F800000.view.effect.params[2] = g_Task->timer * 12;
    D_1F800000.view.effect.params[3] = g_Task->timer;
    D_1F800000.view.effect.params[5] = phase << 6;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(phase << 6), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]);
    for (i = 1; i < 32; i++) {
        D_1F800000.view.effect.params[5] = ((i + D_1F800000.view.effect.params[4]) & 0x3F) * 64;
        D_1F800000.view.effect.params[0] = g_Task->unk_1C + FIXED_MUL(rsin(i << 6), g_Task->unk_1C / 2);
        D_1F800014[0].vx                 = D_1F800014[1].vx;
        D_1F800014[0].vy                 = D_1F800014[1].vy;
        D_1F800014[0].vz                 = 0;
        setVector(&D_1F800014[1], FIXED_MUL(rsin(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[0]),
                  FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[0]), 0);
        setVector(&D_1F800014[2], D_1F800014[3].vx, D_1F800014[3].vy, 0);
        setVector(&D_1F800014[3], FIXED_MUL(rsin(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]),
                  FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]), 0);
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB1(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB2(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB3(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G4));
    }
}

MATCH void func_801EF8E8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    setVector(&rot, 0, 0, 0);
    pos.vx = (g_Task->pos.x.fixed >> 9) - AREA_CELL_ORIGIN;
    pos.vy = (g_Task->pos.y.fixed >> 9) - AREA_CELL_ORIGIN;
    if (g_Task->header.step < 3) {
        pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    } else {
        pos.vz = -(s16)Area_SampleHeight(g_Task->pos.x.fixed, g_Task->pos.y.fixed) / 2;
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

    tpage = getTPage(0, 2, 320, 256);
    GFX_AddDitheredDrawMode(5, tpage);
    D_1F800000.view.effect.params[1] = g_Task->unk_1C - 0x20;
    D_1F800000.view.effect.params[0] = D_1F800000.view.effect.params[1] + FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1] / 2);
    phase                            = (g_Task->unk_20 / 64) & 0x3F;
    D_1F800000.view.effect.params[4] = phase;
    D_1F800000.view.effect.params[2] = g_Task->timer * 2;
    D_1F800000.view.effect.params[5] = phase << 6;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(phase << 6), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]);
    for (i = 1; i < 32; i++) {
        D_1F800000.view.effect.params[5] = ((i + D_1F800000.view.effect.params[4]) & 0x3F) * 64;
        D_1F800000.view.effect.params[0] = D_1F800000.view.effect.params[1] + FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[1] / 2);
        D_1F800014[0].vx                 = D_1F800014[1].vx;
        D_1F800014[0].vy                 = D_1F800014[1].vy;
        D_1F800014[0].vz                 = 0;
        setVector(&D_1F800014[1], FIXED_MUL(rsin(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[0]),
                  FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[0]), 0);
        setVector(&D_1F800014[2], D_1F800014[3].vx, D_1F800014[3].vy, 0);
        setVector(&D_1F800014[3], FIXED_MUL(rsin(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]),
                  FIXED_MUL(rcos(D_1F800000.view.effect.params[5]), D_1F800000.view.effect.params[1]), 0);
        prim = GFX_BeginPolyG4(1);
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB1(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
    tpage = getTPage(0, 0, 320, 256);
    GFX_AddDitheredDrawMode(5, tpage);
}
