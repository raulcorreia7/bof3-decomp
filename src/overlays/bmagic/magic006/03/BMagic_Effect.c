#include "magic006_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC38(void) {
    BMagic_DispatchTaskPair(func_801EEC90, func_801EEDA4);
}

MATCH void func_801EEC90(void) {
    u32 slot;
    s32 i;

    g_Task->facing = g_BattleEffectBattler->facing;
    WorldPos_Copy(&g_Task->pos, &g_BattleEffectBattler->pos);
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0;
    g_Task->header.mode += 1;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 83) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i + 1;
        g_Task->param.unk_0B += 1;
    }
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE04 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE48(void) {
    BMagicEffectFuncs handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_BYTE(handlers.handlers, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        if (g_Task->param.unk_0B != 0) {
            func_801EFB6C();
        } else {
            func_801EF478();
        }
    }
}

MATCH void func_801EEF28(void) {
    PartyMember* battler;
    u8           value;

    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + TO_COORD(128);
        Battle_ProjectRange();
        battler        = g_Battle.selected_actor;
        g_Task->unk_0C = ratan2(battler->pos.x.fixed - g_Task->pos.x.fixed, battler->pos.y.fixed - g_Task->pos.y.fixed);
        g_Task->unk_10 = 0;
        g_Task->unk_14 = (ratan2((s16)battler->unk_2E.half - (s16)g_Task->unk_2E.half, (s16)battler->unk_30.half - (s16)g_Task->unk_30.half) - 0x200) & 0xFFF;
        SND_QueueSelectionEffect(0x100);
        g_Task->unk_09 = 0x20;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF04C(void) {
    PartyMember* work = g_Task;
    u8           timer;

    work->unk_14 += 0x80;

    timer        = work->unk_09 - 1;
    work->unk_09 = timer;
    if (timer == 0) {
        g_Task->unk_09 = g_Task->param.unk_0B + 0xC;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF0B8(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 1;
    if (work->unk_09 == 0) {
        SND_QueueSelectionEffect(0x101);
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF118(void) {
    PartyMember* actor;
    VECTOR       pos;
    s32          diff;
    u8           ticker;

    actor  = g_BattleSelectedActor;
    pos.vx = (actor->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (actor->pos.y.fixed >> 9) - 0x4000;
    pos.vz = (actor->pos.z.fixed + 0x800000) >> 17;
    func_800AF3A0(pos, 0x60);
    g_Task->unk_10 = g_Task->unk_0C;
    g_Task->unk_0C = ratan2(actor->pos.x.fixed - g_Task->pos.x.fixed, actor->pos.y.fixed - g_Task->pos.y.fixed);
    if (func_800AF66C((BattleRange*)actor, 0x20000) != 0) {
        ticker = g_Task->param.unk_0B;
    } else {
        diff           = (g_Task->unk_10 & 0xFFF) - (g_Task->unk_0C & 0xFFF);
        g_Task->unk_10 = diff;
        if (diff < 0) {
            g_Task->unk_10 = ~diff + 1;
        }
        if ((u32)(g_Task->unk_10 - 0x601) >= 0x3FF) {
            return;
        }
        ticker = g_Task->param.unk_0B;
    }
    if (ticker == 0) {
        Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    }
    g_Task->header.step += 1;
}

MATCH void func_801EF298(void) {
    u8 slot;
    u8 i;

    if (g_Task->param.unk_0B == 0) {
        i = 0;
        do {
            slot                               = Battle_AllocEffect(1, 0x53);
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].unk_0B       = i;
            i++;
            g_BattleEffects[slot].arg.unk_09 = (rand() & 0xF) + 1;
            g_BattleEffectBattler->param.unk_0B += 1;
        } while (i < 8);
        slot                               = Battle_AllocEffect(1, 0x53);
        g_BattleEffects[slot].target.party = g_BattleEffectBattler;
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffectBattler->param.unk_0B += 1;
        SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x02));
        g_Task->unk_09 = 0x10;
        g_Task->header.step += 1;
    } else {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EF478(void) {
    POLY_G4* prim;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    D_1F800000.view.effect.params[2] = 8;
    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;
    for (i = 2; i < 8; i += 2) {
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        D_1F800000.view.effect.params[3] = D_801F0A30[i / 2];
        D_1F800000.view.effect.params[4] = (((i + 1) << 9) + g_Task->unk_14) & 0xFFF;
        prim->x0                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
        prim->y0                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
        D_1F800000.view.effect.params[4] = ((i << 9) + g_Task->unk_14) & 0xFFF;
        prim->x1                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
        prim->y1                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
        D_1F800000.view.effect.params[4] = (((i + 2) << 9) + g_Task->unk_14) & 0xFFF;
        prim->x2                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
        prim->y2                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
        prim->x3                         = D_1F800000.view.effect.params[0];
        prim->y3                         = D_1F800000.view.effect.params[1];
        setRGB0(prim, 16, 64, 16);
        setRGB1(prim, 16, 64, 16);
        setRGB2(prim, 16, 64, 16);
        setRGB3(prim, 64, 64, 64);
        GFX_AddPrim(3, sizeof(POLY_G4));
    }
    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[3] = 64;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x200) & 0xFFF;
    prim->x0                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y0                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    D_1F800000.view.effect.params[3] = 56;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x230) & 0xFFF;
    prim->x1                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y1                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->x2                         = D_1F800000.view.effect.params[0];
    prim->y2                         = D_1F800000.view.effect.params[1];
    D_1F800000.view.effect.params[4] = 0x400;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + D_1F800000.view.effect.params[4]) & 0xFFF;
    prim->x3                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    prim->y3                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    setRGB0(prim, 32, 32, 224);
    setRGB1(prim, 32, 32, 224);
    setRGB2(prim, 224, 224, 224);
    setRGB3(prim, 32, 32, 224);
    GFX_AddPrim(3, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[3] = 64;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x200) & 0xFFF;
    prim->x0                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y0                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    D_1F800000.view.effect.params[3] = 56;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x1D0) & 0xFFF;
    prim->x1                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y1                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->x2                         = D_1F800000.view.effect.params[0];
    prim->y2                         = D_1F800000.view.effect.params[1];
    D_1F800000.view.effect.params[4] = g_Task->unk_14 & 0xFFF;
    prim->x3                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    prim->y3                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    setRGB0(prim, 32, 32, 224);
    setRGB1(prim, 32, 32, 224);
    setRGB2(prim, 128, 128, 128);
    setRGB3(prim, 32, 32, 224);
    GFX_AddPrim(3, sizeof(POLY_G4));
}

MATCH void func_801EFB6C(void) {
    POLY_G4* prim;
    s32      tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    D_1F800000.view.effect.params[2] = 8;
    prim                             = (POLY_G4*)g_GfxPrimCursor;
    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[3] = 64;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x200) & 0xFFF;
    prim->x0                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y0                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    D_1F800000.view.effect.params[3] = 56;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x230) & 0xFFF;
    prim->x1                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y1                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->x2                         = D_1F800000.view.effect.params[0];
    prim->y2                         = D_1F800000.view.effect.params[1];
    D_1F800000.view.effect.params[4] = 0x400;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + D_1F800000.view.effect.params[4]) & 0xFFF;
    prim->x3                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    prim->y3                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    setRGB0(prim, 16, 16, 96);
    setRGB1(prim, 16, 16, 96);
    setRGB2(prim, 16, 16, 48);
    setRGB3(prim, 16, 16, 48);
    GFX_AddPrim(3, sizeof(POLY_G4));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[3] = 64;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x200) & 0xFFF;
    prim->x0                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y0                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    D_1F800000.view.effect.params[3] = 56;
    D_1F800000.view.effect.params[4] = (g_Task->unk_14 + 0x1D0) & 0xFFF;
    prim->x1                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->y1                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[3]);
    prim->x2                         = D_1F800000.view.effect.params[0];
    prim->y2                         = D_1F800000.view.effect.params[1];
    D_1F800000.view.effect.params[4] = g_Task->unk_14 & 0xFFF;
    prim->x3                         = D_1F800000.view.effect.params[0] + FIXED_MUL(rsin(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    prim->y3                         = D_1F800000.view.effect.params[1] + FIXED_MUL(rcos(D_1F800000.view.effect.params[4]), D_1F800000.view.effect.params[2]);
    setRGB0(prim, 16, 16, 96);
    setRGB1(prim, 16, 16, 96);
    setRGB2(prim, 16, 16, 48);
    setRGB3(prim, 16, 16, 48);
    GFX_AddPrim(3, sizeof(POLY_G4));
}

MATCH void func_801F0064(void) {
    Magic006Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        func_801F0308();
    }
}

MATCH void func_801F0100(void) {
    PartyMember* actor;
    PartyMember* work;
    s16*         angle_cell;
    u8           count;
    u8           phase;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        phase                        = g_Task->param.unk_0B;
        angle_cell                   = &D_1F800008;
        *angle_cell                  = phase << 9;
        actor                        = g_Battle.selected_actor;
        g_Task->pos.x.fixed          = actor->pos.x.fixed + ((rcos((s16)(phase << 9)) * 0xC000) >> 12);
        (work = g_Task)->pos.y.fixed = actor->pos.y.fixed + ((rsin(*angle_cell) * 0xC000) >> 12);
        work->pos.z.fixed            = actor->pos.z.fixed;
        work->unk_09                 = 0;
        g_Task->timer                = 4;
        g_Task->header.step++;
    }
}

MATCH void func_801F020C(void) {
    u8 counter;

    if (g_FrameCount & 0x1) {
        g_Task->timer += 1;
    }
    counter        = g_Task->unk_09 + 0x10;
    g_Task->unk_09 = counter;
    if ((counter & BYTE_MASK) == 0x80) {
        g_Task->header.step += 1;
    }
}

/* func_801F0290 */
MATCH void Effect_CountDownTimer(void) {
    BMagic_CountDownEffectTimer(8);
}

MATCH void func_801F0308(void) {
    POLY_G4* prim;
    s32      tpage;

    D_1F800000.view.effect.params[2] = g_Task->unk_09;
    D_1F800000.view.effect.params[3] = g_Task->timer;
    D_1F800000.view.effect.params[0] = g_Task->unk_2E.half;
    D_1F800000.view.effect.params[1] = g_Task->unk_30.half;
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
    prim->x0 = D_1F800000.view.effect.params[0] - D_1F800000.view.effect.params[3];
    prim->y0 = D_1F800000.view.effect.params[1] - D_1F800000.view.effect.params[2];
    prim->x1 = D_1F800000.view.effect.params[0] + D_1F800000.view.effect.params[3];
    prim->y1 = D_1F800000.view.effect.params[1] - D_1F800000.view.effect.params[2];
    prim->x2 = D_1F800000.view.effect.params[0] - D_1F800000.view.effect.params[3];
    prim->y2 = D_1F800000.view.effect.params[1];
    prim->x3 = D_1F800000.view.effect.params[0] + D_1F800000.view.effect.params[3];
    prim->y3 = D_1F800000.view.effect.params[1];
    setRGB0(prim, 1, 1, 1);
    setRGB1(prim, 1, 1, 1);
    setRGB2(prim, 0x80, 0x20, 1);
    setRGB3(prim, 0x80, 0x20, 1);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_G4));
}

MATCH void func_801F04F4(void) {
    Magic006SecondSteps handlers;

    handlers = D_801EEC28;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F0790();
        PopMatrix();
    }
}

MATCH void func_801F05A4(void) {
    PartyMember* src;

    src                 = g_Battle.selected_actor;
    g_Task->pos.x.fixed = src->pos.x.fixed;
    g_Task->pos.y.fixed = src->pos.y.fixed;
    g_Task->pos.z       = src->pos.z;
    g_Task->unk_09      = 0;
    g_Task->header.step = g_Task->header.step + 1;
}

MATCH void func_801F05F4(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 4;
    g_Task->unk_09 = timer;
    if (timer == 16) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_NextStepOnLastTick.h"

MATCH void Effect_TickOnTimerZero3(void) {
    PartyMember* work;

    BMAGIC_TICK_ON_TIMER_ZERO(EFFECT_TIMER_TICK);
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801F0790(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = 0x100;
    D_1F800000.view.effect.params[5] = g_Task->unk_09 << 3;
    D_1F800000.view.effect.params[6] = g_Task->unk_09 << 1;
    D_1F800000.view.effect.params[7] = 1;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[1].vz                 = 0;
    D_1F800014[0].vz                 = 0;

    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG3(1);
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
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
