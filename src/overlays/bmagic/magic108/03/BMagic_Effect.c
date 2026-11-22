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
    TASK(PartyMember)->param.unk_0B    = 0;
    TASK(PartyMember)->header.mode += 1;
}

#include "overlays/bmagic/shared/Effect_PlayOnIdleTick.h"

MATCH void func_801EED7C(void) {
    SYS_DISPATCH_BYTE(D_801EFC9C, TASK(PartyMember)->header.mode);
    if (TASK(PartyMember)->header.flags != 0) {
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

    TASK(PartyMember)->unk_0C = 0x20000;
    TASK(PartyMember)->unk_10 = 0;
    Effect_RotatePosition(g_Task);
    TASK(PartyMember)->pos.x.fixed += TASK(PartyMember)->unk_0C;
    TASK(PartyMember)->pos.y.fixed += TASK(PartyMember)->unk_10;
    COORD_INT(TASK(PartyMember)->pos.z) = COORD_INT(TASK(PartyMember)->pos.z) + 0xC0;
    TASK(PartyMember)->unk_18           = TASK(PartyMember)->pos.x.fixed;
    TASK(PartyMember)->unk_1C           = TASK(PartyMember)->pos.y.fixed;
    TASK(PartyMember)->unk_20           = TASK(PartyMember)->pos.z.fixed;
    slot                                = g_Battle.active_battler;
    if (slot < BATTLE_PARTY_CHARACTERS_COUNT) {
        battler = &g_Game.members[slot];
    } else {
        battler = (PartyMember*)(g_BattleEnemies + slot * BATTLE_ENEMY_STRIDE);
    }
    TASK(PartyMember)->pos.x.fixed  = battler->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = battler->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = battler->pos.z.fixed + TO_COORD(192);
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 0;
    TASK(PartyMember)->timer        = 0;
    TASK(PartyMember)->header.mode += 1;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEF48(void) {
    s32 vec[4];

    TASK(PartyMember)->timer += 1;
    vec[0] = (TASK(PartyMember)->unk_18 >> 9) - AREA_CELL_ORIGIN;
    vec[1] = (TASK(PartyMember)->unk_1C >> 9) - AREA_CELL_ORIGIN;
    vec[2] = TASK(PartyMember)->unk_20 >> 0x11;
    /* The retail build passes the never-written slot after the vector. */
    Battle_StepRangeToward(vec[0], vec[1], vec[2], vec[3], 0x20);
    if (func_800AF6B8(TASK(PartyMember)->unk_18, TASK(PartyMember)->unk_1C, TASK(PartyMember)->unk_20, 0x8000) != 0) {
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF020(void) {
    u8 temp_v0;

    temp_v0                  = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = temp_v0;
    if (!(temp_v0 & 0x1F)) {
        SND_SEQueueSelection(0x101);
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.mode += 1;
    }
}

#include "overlays/bmagic/shared/Effect_AdvanceOnTick.h"

MATCH void func_801EF0E0(void) {
    u8 timer;

    timer                    = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer;
    if (timer == 96) {
        TASK(PartyMember)->header.mode = TASK(PartyMember)->header.mode + 1;
    }
}

MATCH void func_801EF130(void) {
    u8 timer_next;

    timer_next               = TASK(PartyMember)->timer + 1;
    TASK(PartyMember)->timer = timer_next;
    if ((timer_next & BYTE_MASK) == 0x80) {
        g_BattleEffectBattler->param.unk_0B = 0xFF;
        Effect_Reset();
    }
}

MATCH void func_801EF180(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    switch (TASK(PartyMember)->facing) {
        case 0: {
            u8 timer;

            timer  = TASK(PartyMember)->timer;
            rot.vy = 0;
            rot.vz = 0x800;
            rot.vx = (~timer & 0x1F) << 7;
            break;
        }
        case 1: {
            u8 timer;

            rot.vx = 0;
            timer  = TASK(PartyMember)->timer;
            rot.vz = 0xC00;
            rot.vy = (~timer & 0x1F) << 7;
            break;
        }
        case 2: {
            u8 timer;

            timer  = TASK(PartyMember)->timer;
            rot.vy = 0;
            rot.vz = 0;
            rot.vx = (~timer & 0x1F) << 7;
            break;
        }
        case 3: {
            u8 timer;

            rot.vx = 0;
            timer  = TASK(PartyMember)->timer;
            rot.vz = 0x400;
            rot.vy = (~timer & 0x1F) << 7;
            break;
        }
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

/* Draws a fan of projected LINE_F2 rays, one per count up to the effect counter 0x09: each ray swings by an
 * thirty-second of a turn more and its x falls with the timer; in mode 5 the rays turn semi-transparent and fade. */
MATCH void func_801EF2D4(void) {
    LINE_F2* prim;
    long     p;
    long     flag;
    s32      semi;
    s32      tpage;
    s32      i;

    semi                        = TASK(PartyMember)->header.mode == 5;
    g_ScratchPad.cells.words[0] = 0;
    setVector(&g_ScratchPadVectors[0], TASK(PartyMember)->timer, FIXED_MUL(rcos(0), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0), g_ScratchPad.cells.words[0]));
    for (i = 1; g_ScratchPad.cells.words[0] < TASK(PartyMember)->unk_09; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, semi, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
        prim = (LINE_F2*)g_GfxPrimCursor;
        SetLineF2(prim);
        SetSemiTrans(prim, semi);
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x0, &p, &flag);
        if (i < TASK(PartyMember)->timer) {
            g_ScratchPadVectors[0].vx = TASK(PartyMember)->timer - i;
        } else {
            g_ScratchPadVectors[0].vx = 0;
        }
        g_ScratchPadVectors[0].vy = FIXED_MUL(rcos(i << 7), g_ScratchPad.cells.words[0]);
        g_ScratchPadVectors[0].vz = FIXED_MUL(rsin(i << 7), g_ScratchPad.cells.words[0]);
        RotTransPers(&g_ScratchPadVectors[0], (long*)&prim->x1, &p, &flag);
        if (TASK(PartyMember)->header.mode == 5) {
            g_ScratchPad.cells.words[1] = 0x60 - (TASK(PartyMember)->timer - 0x60) * 3;
            g_ScratchPad.cells.words[3] = 0x40 - (TASK(PartyMember)->timer - 0x60) * 2;
            setRGB0(prim, g_ScratchPad.cells.words[3], g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[3]);
        } else {
            setRGB0(prim, 0x80, 0xC0, 0x80);
        }
        Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(LINE_F2));
        g_ScratchPad.cells.words[0]++;
    }
}

MATCH void func_801EF5C0(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;
    u8      angle;

    PushMatrix();
    if (TASK(PartyMember)->facing & 0x1) {
        rot.vx = 0;
        angle  = TASK(PartyMember)->timer & 0x1F;
        rot.vy = (s16)(angle << 7);
        rot.vz = 1024;
    } else {
        angle = TASK(PartyMember)->timer & 0x1F;
        setVector(&rot, (s16)(angle << 7), 0, 0);
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(TASK(PartyMember));
}

/* Draws two semi-transparent diamonds as projected POLY_G4 quads, the second turned an eighth of a turn from the
 * first: the radius grows with the timer in mode 1 up to 0xC0, and the shade fades with the timer in mode 5. */
MATCH void func_801EF6C0(void) {
    POLY_G4* prim;
    long     p;
    long     flag;
    s32      tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    if (TASK(PartyMember)->header.mode == 1) {
        g_ScratchPad.cells.words[0] = TASK(PartyMember)->timer * 8;
        if (g_ScratchPad.cells.words[0] > 0xC0) {
            g_ScratchPad.cells.words[0] = 0xC0;
        }
    } else {
        g_ScratchPad.cells.words[0] = 0xC0;
    }
    setVector(&g_ScratchPadVectors[0], 0, FIXED_MUL(rcos(0x200), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0x200), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[1], 0, FIXED_MUL(rcos(0x600), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0x600), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[2], 0, FIXED_MUL(rcos(0xE00), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0xE00), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[3], 0, FIXED_MUL(rcos(0xA00), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0xA00), g_ScratchPad.cells.words[0]));
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                  &flag);
    if (TASK(PartyMember)->header.mode == 5) {
        g_ScratchPad.cells.words[1] = 0x60 - (TASK(PartyMember)->timer - 0x60) * 3;
    } else {
        g_ScratchPad.cells.words[1] = 0x60;
    }
    setRGB0(prim, g_ScratchPad.cells.words[1], 1, g_ScratchPad.cells.words[1]);
    setRGB1(prim, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1], 1);
    setRGB2(prim, g_ScratchPad.cells.words[1], 1, g_ScratchPad.cells.words[1]);
    setRGB3(prim, g_ScratchPad.cells.words[1], 1, 1);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    setVector(&g_ScratchPadVectors[0], 0, FIXED_MUL(rcos(0), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[1], 0, FIXED_MUL(rcos(0x400), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0x400), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[2], 0, FIXED_MUL(rcos(0xC00), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0xC00), g_ScratchPad.cells.words[0]));
    setVector(&g_ScratchPadVectors[3], 0, FIXED_MUL(rcos(0x800), g_ScratchPad.cells.words[0]), FIXED_MUL(rsin(0x800), g_ScratchPad.cells.words[0]));
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &p,
                  &flag);
    setRGB0(prim, g_ScratchPad.cells.words[1], 1, g_ScratchPad.cells.words[1]);
    setRGB1(prim, g_ScratchPad.cells.words[1], g_ScratchPad.cells.words[1], 1);
    setRGB2(prim, g_ScratchPad.cells.words[1], 1, g_ScratchPad.cells.words[1]);
    setRGB3(prim, g_ScratchPad.cells.words[1], 1, 1);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
}
