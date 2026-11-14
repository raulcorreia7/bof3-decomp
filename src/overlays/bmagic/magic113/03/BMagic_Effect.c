#include "magic113_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC24(void) {
    Magic113Steps handlers;

    BMAGIC_DISPATCH_STEP_HANDLERS(D_801EEC04, header.mode);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF4F0();
        PopMatrix();
    }
}

MATCH void func_801EECE0(void) {
    u8   i;
    u16* dst;
    u16* src;

    if ((g_Battle.target_selector < BATTLE_PARTY_CHARACTERS_COUNT && g_Battle.active_battler < BATTLE_PARTY_CHARACTERS_COUNT) ||
        (g_Battle.target_selector >= BATTLE_PARTY_CHARACTERS_COUNT && g_Battle.active_battler >= BATTLE_PARTY_CHARACTERS_COUNT)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    } else {
        i = 0;
        WorldPos_Copy(&g_Task->pos, &g_Battle.selected_actor->pos);
        dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
        src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
        for (; i < 16; i++) {
            dst[i] = src[i] | 0x8000;
        }
        g_GfxPalettePending  = 1;
        g_Task->param.unk_0B = 0;
        g_Task->unk_09       = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE24(void) {
    u8           timer;
    u32          slot;
    PartyMember* work;
    u8           facing;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
        work                                   = g_Task;
        g_BattleEffects[slot].header.mode      = 0;
        g_BattleEffects[slot].unk_0B           = 0;
        g_BattleEffects[slot].target.party     = work;
        facing                                 = g_BattleEffectBattler->facing;
        g_BattleEffects[slot].arg.unk_09       = 0;
        g_BattleEffects[slot].unk_0A           = 0;
        g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
        g_BattleEffects[slot].pos.x            = g_Task->pos.x;
        g_BattleEffects[slot].pos.y            = g_Task->pos.y;
        COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);
        slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
        work                                   = g_Task;
        g_BattleEffects[slot].header.mode      = 0;
        g_BattleEffects[slot].unk_0B           = 1;
        g_BattleEffects[slot].target.party     = work;
        facing                                 = g_BattleEffectBattler->facing;
        g_BattleEffects[slot].arg.unk_09       = 0;
        g_BattleEffects[slot].unk_0A           = 0;
        g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
        g_BattleEffects[slot].pos.x            = g_Task->pos.x;
        g_BattleEffects[slot].pos.y            = g_Task->pos.y;
        COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF000(void) {
    u32          slot;
    PartyMember* work;
    u8           facing;

    if (g_Task->param.unk_0B == 3) {
        MAGIC113_SPAWN_EFFECT(1);
    }
}

MATCH void func_801EF0F0(void) {
    u32          slot;
    PartyMember* work;
    u8           facing;

    if (g_Task->param.unk_0B == 4) {
        MAGIC113_SPAWN_EFFECT(2);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        g_SndVoiceTargetVolume[20] = 0x7F;
        g_SndVoiceVolume[20]       = 0;
    }
}

MATCH void func_801EF1F8(void) {
    u8           i;
    u32          slot;
    PartyMember* work;
    u8           facing;

    func_8015D104(20, 16);
    SND_StartVolumeSweep(20);
    if (g_Task->param.unk_0B == 5) {
        for (i = 0; i < 6; i++) {
            slot                                   = Battle_AllocEffect(1, 3) & BYTE_MASK;
            work                                   = g_Task;
            g_BattleEffects[slot].header.mode      = 3;
            g_BattleEffects[slot].unk_04           = i & 1;
            g_BattleEffects[slot].target.party     = work;
            facing                                 = g_BattleEffectBattler->facing;
            g_BattleEffects[slot].arg.unk_09       = (i >> 1) * 8 + 1;
            g_BattleEffects[slot].unk_0A           = 0;
            g_BattleEffects[slot].unk_0B           = i >> 1;
            g_BattleEffects[slot].unk_08           = (facing + 2) & 3;
            g_BattleEffects[slot].pos.x            = g_Task->pos.x;
            g_BattleEffects[slot].pos.y            = g_Task->pos.y;
            COORD_INT(g_BattleEffects[slot].pos.z) = COORD_INT(g_Task->pos.z);
        }
        g_Task->param.unk_0B = 0;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF35C(void) {
    if (g_Task->param.unk_0B == 6) {
        g_Task->param.unk_0B = 0x84;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EF3A0(void) {
    PartyMember* work;

    work = g_Task;
    if (work->param.unk_0B == 0x80) {
        work->header.mode = (work->header.mode + 1);
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF4F0(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0x125;
    } else if (GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    s_Magic113OrbitRadius = 0x1C0;
    D_1F800014[2].vx      = FIXED_MUL(rsin(0), s_Magic113OrbitRadius);
    D_1F800014[2].vy      = FIXED_MUL(rcos(0), s_Magic113OrbitRadius);
    for (i = 1; i <= 32; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 7), s_Magic113OrbitRadius);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 7), s_Magic113OrbitRadius);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        D_1F800000.view.scenario.math_04 = g_Task->unk_09 * 12;
        setRGB0(prim, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    if (GetGraphType() == 1) {
        tpage = 0x25;
    } else if (GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

/* func_801EF75C */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF7A0(void) {
    SYS_DISPATCH_BYTE(D_801F0BAC, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        s_Magic113OrbitRadius = D_801F0BA4[g_Task->param.unk_0B];
        func_801EF944();
        PopMatrix();
    }
}

MATCH void func_801EF844(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x21) {
        g_BattleEffectBattler->param.unk_0B = 3;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF8A4(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 132) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EF8E4(void) {
    Effect_CountUpTimer();
}

/* Draw the magic113 orbit as up to 32 projected line segments; in step 2 the lines turn
 * semi-transparent and fade with the effect timer. */
MATCH void func_801EF944(void) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800014[0].vx = FIXED_MUL(rsin(0), s_Magic113OrbitRadius);
    D_1F800014[0].vy = FIXED_MUL(rcos(0), s_Magic113OrbitRadius);
    D_1F800014[0].vz = 0;
    for (i = 1; i <= 32; i++) {
        if (i < g_Task->unk_09) {
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            if (g_Task->header.step == 2) {
                SetSemiTrans(prim, 1);
            }
            RotTransPers(&D_1F800014[0], (long*)&prim->x0, &depth, &flag);
            D_1F800014[0].vx = FIXED_MUL(rsin(i << 7), s_Magic113OrbitRadius);
            D_1F800014[0].vy = FIXED_MUL(rcos(i << 7), s_Magic113OrbitRadius);
            D_1F800014[0].vz = 0;
            RotTransPers(&D_1F800014[0], (long*)&prim->x1, &depth, &flag);
            setRGB0(prim, 240, 170, 200);
            if (g_Task->header.step == 2) {
                setRGB0(prim, 240 - g_Task->timer * 20, 170 - g_Task->timer * 14, 200 - g_Task->timer * 16);
            }
            GFX_AddPrim(5, sizeof(LINE_F2));
        }
    }
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EFC28(void) {
    SYS_DISPATCH_BYTE(D_801F0BC0, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EFDA0();
        PopMatrix();
    }
}

MATCH void func_801EFCA0(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x28) {
        g_BattleEffectBattler->param.unk_0B = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFD00(void) {
    PartyMember* active;
    PartyMember* work;

    active = BATTLE_ACTIVE_WORK;
    if (active->param.unk_0B == 132) {
        work              = g_Task;
        work->header.step = work->header.step + 1;
    }
}

MATCH void func_801EFD40(void) {
    Effect_CountUpTimer();
}

/* Draw the magic113 outline as five line segments between the corner angles of D_801F0BB8, each
 * growing over eight steps of the effect size; in step 2 they turn semi-transparent and fade. */
MATCH void func_801EFDA0(void) {
    LINE_F2* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      length;
    s32      left;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    for (i = 0; i < 5; i++) {
        if (i * 8 < g_Task->unk_09) {
            left   = g_Task->unk_09 - i * 8;
            length = 8;
            if (left < 8) {
                length = left;
            }
            prim = (LINE_F2*)g_GfxPrimCursor;
            SetLineF2(prim);
            if (g_Task->header.step == 2) {
                SetSemiTrans(prim, 1);
            }
            D_1F800014[0].vx = FIXED_MUL(rsin(D_801F0BB8[i] * 273), 288);
            D_1F800014[0].vy = FIXED_MUL(rcos(D_801F0BB8[i] * 273), 288);
            D_1F800014[0].vz = 0;
            RotTransPers(&D_1F800014[0], (long*)&prim->x0, &depth, &flag);
            D_1F800014[1].vx = FIXED_MUL(rsin(D_801F0BB8[i + 1] * 273), 288);
            D_1F800014[1].vy = FIXED_MUL(rcos(D_801F0BB8[i + 1] * 273), 288);
            D_1F800014[1].vx = D_1F800014[0].vx + ((D_1F800014[1].vx - D_1F800014[0].vx) / 8) * length;
            D_1F800014[1].vy = D_1F800014[0].vy + ((D_1F800014[1].vy - D_1F800014[0].vy) / 8) * length;
            D_1F800014[1].vz = 0;
            RotTransPers(&D_1F800014[1], (long*)&prim->x1, &depth, &flag);
            setRGB0(prim, 240, 170, 200);
            if (g_Task->header.step == 2) {
                setRGB0(prim, 240 - g_Task->timer * 20, 170 - g_Task->timer * 14, 200 - g_Task->timer * 16);
            }
            GFX_AddPrim(5, sizeof(LINE_F2));
        }
    }
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801F0140(void) {
    SYS_DISPATCH_BYTE(D_801F0BCC, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801F02CC();
        PopMatrix();
    }
}

MATCH void func_801F01B8(void) {
    u8 count;

    count          = g_Task->unk_09 + 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0x31) {
        g_BattleEffectBattler->param.unk_0B = 5;
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0218(void) {
    if (g_BattleEffectBattler->param.unk_0B == 0x84) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x03));
        g_Task->header.step += 1;
    }
}

MATCH void func_801F026C(void) {
    PartyMember* work;
    u8           next;

    work        = g_Task;
    next        = work->timer + 1;
    work->timer = next;
    if (next == 0x10) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        func_801E5988();
    }
}

/* Draw the magic113 wall as up to 32 shaded quads rising from the ring, each one cell-sorted at
 * its own outer corner; the height falls off over the last 16 and flickers while it is full. */
MATCH void func_801F02CC(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      x;
    s32      y;
    s32      tpage;

    if (g_Task->unk_09 < 16) {
        D_1F800000.view.scenario.math_08 = g_Task->unk_09 * 32;
    } else {
        D_1F800000.view.scenario.math_08 = 0x200;
    }
    D_1F800014[1].vx = FIXED_MUL(rcos(0), 304);
    D_1F800014[1].vy = FIXED_MUL(rsin(0), 304);
    D_1F800014[1].vz = g_Task->timer * 8 - D_1F800000.view.scenario.math_08;
    D_1F800014[3].vx = FIXED_MUL(rcos(0), 304);
    D_1F800014[3].vy = FIXED_MUL(rsin(0), 304);
    D_1F800014[3].vz = 0;
    for (i = 1; i <= 32; i++) {
        if (i < g_Task->unk_09) {
            if (g_Task->unk_09 - i < 16) {
                D_1F800000.view.scenario.math_08 = (g_Task->unk_09 - i) * 32;
            } else {
                D_1F800000.view.scenario.math_08 = (rand() & 0x3F) + 0x200;
                if (i == 32) {
                    D_1F800000.view.scenario.math_08 = 0x200;
                }
            }
            D_1F800014[0].vx = D_1F800014[1].vx;
            D_1F800014[0].vy = D_1F800014[1].vy;
            D_1F800014[0].vz = D_1F800014[1].vz;
            D_1F800014[2].vx = D_1F800014[3].vx;
            D_1F800014[2].vy = D_1F800014[3].vy;
            D_1F800014[2].vz = 0;
            D_1F800014[1].vx = FIXED_MUL(rcos(i << 7), 304);
            D_1F800014[1].vy = FIXED_MUL(rsin(i << 7), 304);
            D_1F800014[1].vz = g_Task->timer * 8 - D_1F800000.view.scenario.math_08;
            D_1F800014[3].vx = FIXED_MUL(rcos(i << 7), 304);
            D_1F800014[3].vy = FIXED_MUL(rsin(i << 7), 304);
            D_1F800014[3].vz = 0;
            x                = (D_1F800014[3].vx << 9) + g_Task->pos.x.fixed;
            y                = (D_1F800014[3].vy << 9) + g_Task->pos.y.fixed;
            if (GetGraphType() == 1 || GetGraphType() == 2) {
                tpage = 0xA5;
            } else {
                tpage = 0x35;
            }
            SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
            Area_AddCellPrim(x, y, 0, sizeof(DR_MODE));
            prim = (POLY_G4*)g_GfxPrimCursor;
            SetPolyG4(prim);
            SetSemiTrans(prim, 1);
            D_1F800000.view.scenario.math_04 = 32 - g_Task->timer * 2;
            setRGB0(prim, 1, 1, 1);
            setRGB1(prim, 1, 1, 1);
            setRGB2(prim, 192 - g_Task->timer * 12, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
            setRGB3(prim, 192 - g_Task->timer * 12, D_1F800000.view.scenario.math_04, D_1F800000.view.scenario.math_04);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            Area_AddCellPrim(x, y, 0, sizeof(POLY_G4));
        }
    }
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x25;
    } else {
        tpage = 0x15;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
}

MATCH void func_801F0764(void) {
    GFX_AddDitheredDrawMode(3, getTPage(1, 1, 320, 256));
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0BD8, g_Task->header.step);
    g_Scripts = AREA_SCRIPT_TABLE;
    GFX_AddDitheredDrawMode(3, getTPage(1, 0, 320, 256));
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

MATCH void func_801F08B4(void) {
    PartyMember* task;
    s8           tint;

    g_Task->pos.x.fixed        = g_Task->pos.x.fixed;
    g_Task->pos.y.fixed        = g_Task->pos.y.fixed;
    g_Task->pos.z.part.integer = (s16)g_Task->pos.z.part.integer;
    if (g_Task->param.unk_0B == 2) {
        g_Task->pos.z.fixed += 0x01800000;
    }
    if (g_Task->unk_04 != 0) {
        g_Task->pos.z.fixed += 0x02000000;
    }
    g_Task->unk_25 = 0x1D;
    g_Task->unk_26 = 0;
    g_Task->unk_27 = 0xA0;
    g_Task->unk_28 = 0;
    g_Task->header.flags |= 0x20;
    tint              = -0x40;
    g_Task->unk_5D    = tint;
    g_Task->unk_5E    = tint;
    g_Task->unk_5F    = tint;
    g_Task->unk_5C    = 1;
    g_Task->unk_2A    = g_Task->unk_04;
    g_Task->unk_29    = 4;
    g_Task->unk_24    = 4;
    task              = g_Task;
    task->unk_2B      = 1;
    task->unk_2C.half = 0;
    g_Task->unk_09    = 0;
    g_Task->header.step += 1;
    if (g_Task->param.unk_0B == 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
    }
    Actor_SelectScript(g_Task->param.unk_0B);
}

MATCH void func_801F0A80(void) {
    u8 value;

    if (Actor_StepAnimOnce() & BYTE_MASK) {
        value          = g_Task->unk_09 + 1;
        g_Task->unk_09 = value;
        if ((value & BYTE_MASK) >= 3U) {
            g_BattleEffectBattler->param.unk_0B += 1;
            func_801E5988();
            return;
        }
        g_Task->unk_2A = (g_Task->unk_2A + 0x1) & 1;
        Actor_SelectScript(g_Task->param.unk_0B);
        func_8014D290();
        if (g_Task->param.unk_0B == 0) {
            if (g_Task->unk_09 == 1) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x04));
                return;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        }
    } else {
        func_8014D290();
    }
}
