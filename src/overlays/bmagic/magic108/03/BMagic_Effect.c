#include "magic108_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED1C};
    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* src;
    u32          slot;

    src                                = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, 26) & BYTE_MASK;
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].unk_08       = src->facing;
    g_BattleEffects[slot].pos.x.fixed  = src->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = src->pos.y.fixed;
    g_BattleEffects[slot].pos.z        = src->pos.z;
    g_Task->param.unk_0B               = 0;
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EED7C(void) {
    SYS_DISPATCH_BYTE(D_801EFC9C, g_Task->header.mode);
    if (g_Task->header.flags != 0) {
        func_801EF5C0();
        func_801EF6C0();
        PopMatrix();
        func_801EF180();
        func_801EF2D4();
        PopMatrix();
    }
}

MATCH void func_801EEE0C(void) {
    PartyMember* battler;
    u32          slot;

    g_Task->unk_0C = 0x20000;
    g_Task->unk_10 = 0;
    func_801DD350(g_Task);
    g_Task->pos.x.fixed += g_Task->unk_0C;
    g_Task->pos.y.fixed += g_Task->unk_10;
    COORD_INT(g_Task->pos.z) = COORD_INT(g_Task->pos.z) + 0xC0;
    g_Task->unk_18           = g_Task->pos.x.fixed;
    g_Task->unk_1C           = g_Task->pos.y.fixed;
    g_Task->unk_20           = g_Task->pos.z.fixed;
    FAKE_BARRIER(); /* FAKE: keeps the g_Battle.active_battler read below the coord copy stores */
    slot = g_Battle.active_battler;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    g_Task->pos.x.fixed  = battler->pos.x.fixed;
    g_Task->pos.y.fixed  = battler->pos.y.fixed;
    g_Task->pos.z.fixed  = battler->pos.z.fixed + TO_COORD(192);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.mode += 1;
    SND_QueueSelectionEffect(0x100);
}

MATCH void func_801EEF48(void) {
    s32 vec[4];

    g_Task->timer += 1;
    vec[0] = (g_Task->unk_18 >> 9) - 0x4000;
    vec[1] = (g_Task->unk_1C >> 9) - 0x4000;
    vec[2] = g_Task->unk_20 >> 0x11;
    /* The retail build passes the never-written slot after the vector. */
    func_800AF3A0(vec[0], vec[1], vec[2], vec[3], 0x20);
    if (func_800AF6B8(g_Task->unk_18, g_Task->unk_1C, g_Task->unk_20, 0x8000) != 0) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF020(void) {
    u8 temp_v0;

    temp_v0       = g_Task->timer + 1;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & 0x1F)) {
        SND_QueueSelectionEffect(0x101);
        g_Task->timer = 0;
        g_Task->header.mode += 1;
    }
}

#include "overlays/bmagic/Effect_AdvanceOnTick.h"

MATCH void func_801EF0E0(void) {
    u8 timer;

    timer         = g_Task->timer + 1;
    g_Task->timer = timer;
    if (timer == 96) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

MATCH void func_801EF130(void) {
    u8 timer_next;

    timer_next    = g_Task->timer + 1;
    g_Task->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x80) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

#ifdef NON_MATCHING
NON_MATCHING void func_801EF180(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      timer;

    PushMatrix();
    switch (g_Task->facing) {
        case 0:
            timer  = g_Task->timer;
            rot.vy = 0;
            rot.vz = 0x800;
            rot.vx = (~timer & 0x1F) << 7;
            break;
        case 1:
            rot.vx = 0;
            timer  = g_Task->timer;
            rot.vz = 0xC00;
            rot.vy = (~timer & 0x1F) << 7;
            break;
        case 2:
            timer  = g_Task->timer;
            rot.vy = 0;
            rot.vz = 0;
            rot.vx = (~timer & 0x1F) << 7;
            break;
        case 3:
            rot.vx = 0;
            timer  = g_Task->timer;
            rot.vz = 0x400;
            rot.vy = (~timer & 0x1F) << 7;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}
#else
INCLUDE_ASM(func_801EF180);
#endif

/* Draws a fan of projected LINE_F2 rays, one per count up to the effect counter 0x09: each ray swings by an
 * thirty-second of a turn more and its x falls with the timer; in mode 5 the rays turn semi-transparent and fade. */
MATCH void func_801EF2D4(void) {
    LINE_F2* prim;
    long     p;
    long     flag;
    s32      semi;
    s32      tpage;
    s32      i;

    semi                             = g_Task->header.mode == 5;
    D_1F800000.view.scenario.math_00 = 0;
    D_1F800014[0].vx                 = g_Task->timer;
    D_1F800014[0].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vz                 = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
    for (i = 1; D_1F800000.view.scenario.math_00 < g_Task->unk_09; i++) {
        if (GetGraphType() == 1 || GetGraphType() == 2) {
            tpage = ((semi & 3) << 7) | 0x25;
        } else {
            tpage = ((semi & 3) << 5) | 0x15;
        }
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, semi);
        RotTransPers(&D_1F800014[0], (long*)&prim->x0, &p, &flag);
        if (i < g_Task->timer) {
            D_1F800014[0].vx = g_Task->timer - i;
        } else {
            D_1F800014[0].vx = 0;
        }
        D_1F800014[0].vy = FIXED_MUL(rcos(i << 7), D_1F800000.view.scenario.math_00);
        D_1F800014[0].vz = FIXED_MUL(rsin(i << 7), D_1F800000.view.scenario.math_00);
        RotTransPers(&D_1F800014[0], (long*)&prim->x1, &p, &flag);
        if (g_Task->header.mode == 5) {
            D_1F800000.view.scenario.math_04 = 0x60 - (g_Task->timer - 0x60) * 3;
            D_1F800000.view.scenario.math_0C = 0x40 - (g_Task->timer - 0x60) * 2;
            setRGB0(prim, D_1F800000.view.scenario.math_0C, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_0C);
        } else {
            setRGB0(prim, 0x80, 0xC0, 0x80);
        }
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(LINE_F2));
        D_1F800000.view.scenario.math_00++;
    }
}

MATCH void func_801EF5C0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      angle;

    PushMatrix();
    if (g_Task->facing & 0x1) {
        rot.vx = 0;
        angle  = g_Task->timer & 0x1F;
        rot.vy = (s16)(angle << 7);
        rot.vz = 1024;
    } else {
        angle  = g_Task->timer & 0x1F;
        rot.vx = (s16)(angle << 7);
        rot.vy = 0;
        rot.vz = 0;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

/* Draws two semi-transparent diamonds as projected POLY_G4 quads, the second turned an eighth of a turn from the
 * first: the radius grows with the timer in mode 1 up to 0xC0, and the shade fades with the timer in mode 5. */
MATCH void func_801EF6C0(void) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (g_Task->header.mode == 1) {
        D_1F800000.view.scenario.math_00 = g_Task->timer * 8;
        if (D_1F800000.view.scenario.math_00 > 0xC0) {
            D_1F800000.view.scenario.math_00 = 0xC0;
        }
    } else {
        D_1F800000.view.scenario.math_00 = 0xC0;
    }
    D_1F800014[0].vx = 0;
    D_1F800014[0].vy = FIXED_MUL(rcos(0x200), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vz = FIXED_MUL(rsin(0x200), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vx = 0;
    D_1F800014[1].vy = FIXED_MUL(rcos(0x600), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vz = FIXED_MUL(rsin(0x600), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vx = 0;
    D_1F800014[2].vy = FIXED_MUL(rcos(0xE00), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vz = FIXED_MUL(rsin(0xE00), D_1F800000.view.scenario.math_00);
    D_1F800014[3].vx = 0;
    D_1F800014[3].vy = FIXED_MUL(rcos(0xA00), D_1F800000.view.scenario.math_00);
    D_1F800014[3].vz = FIXED_MUL(rsin(0xA00), D_1F800000.view.scenario.math_00);
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
    if (g_Task->header.mode == 5) {
        D_1F800000.view.scenario.math_04 = 0x60 - (g_Task->timer - 0x60) * 3;
    } else {
        D_1F800000.view.scenario.math_04 = 0x60;
    }
    setRGB0(prim, D_1F800000.view.scenario.math_04, 1, D_1F800000.view.scenario.math_04);
    setRGB1(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, 1);
    setRGB2(prim, D_1F800000.view.scenario.math_04, 1, D_1F800000.view.scenario.math_04);
    setRGB3(prim, D_1F800000.view.scenario.math_04, 1, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_G4));
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    D_1F800014[0].vx = 0;
    D_1F800014[0].vy = FIXED_MUL(rcos(0), D_1F800000.view.scenario.math_00);
    D_1F800014[0].vz = FIXED_MUL(rsin(0), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vx = 0;
    D_1F800014[1].vy = FIXED_MUL(rcos(0x400), D_1F800000.view.scenario.math_00);
    D_1F800014[1].vz = FIXED_MUL(rsin(0x400), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vx = 0;
    D_1F800014[2].vy = FIXED_MUL(rcos(0xC00), D_1F800000.view.scenario.math_00);
    D_1F800014[2].vz = FIXED_MUL(rsin(0xC00), D_1F800000.view.scenario.math_00);
    D_1F800014[3].vx = 0;
    D_1F800014[3].vy = FIXED_MUL(rcos(0x800), D_1F800000.view.scenario.math_00);
    D_1F800014[3].vz = FIXED_MUL(rsin(0x800), D_1F800000.view.scenario.math_00);
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p, &flag);
    setRGB0(prim, D_1F800000.view.scenario.math_04, 1, D_1F800000.view.scenario.math_04);
    setRGB1(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, 1);
    setRGB2(prim, D_1F800000.view.scenario.math_04, 1, D_1F800000.view.scenario.math_04);
    setRGB3(prim, D_1F800000.view.scenario.math_04, 1, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_G4));
}
