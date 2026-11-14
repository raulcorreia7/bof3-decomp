#include "magic058_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    Magic058Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (BMAGIC_EFFECT_SLOTS[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&BMAGIC_EFFECT_SLOTS[i];
            g_BattleEffectBattler = BMAGIC_EFFECT_SLOTS[i].target.party;
            func_801EF36C();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED30);

MATCH void func_801EEE78(void) {
    if (g_Task->param.unk_0B == 0) {
        func_801DE8C0(1, 0x3C, Message_GetText(0x14U));
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEEDC(void) {
    if (D_801EC2E4 == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EEF30 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF74(void) {
    Magic058Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF74C();
        PopMatrix();
    }
}

MATCH void func_801EF008(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    g_Task->facing    = g_BattleEffectBattler->facing;
    work              = g_Task;
    actor             = g_BattleEffectBattler;
    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->timer       = 16;
    work->unk_0C      = 8;
    work->pos.z.fixed = z;
    g_Task->header.step += 1;
}

MATCH void func_801EF080(void) {
    u8 i;
    u8 j;
    u8 slot;

    g_Task->unk_0C += 32;
    D_1F800000_HALF = g_Task->unk_0C;
    for (i = 0; i < 8; i++) {
        if (D_801F0FD4[i + 3] == 0 && !(func_801DB524(i + 3) & BYTE_MASK) && func_801EFDD4(&g_BattleEnemyBattlers[i]) && g_Battle.active_battler != i + 3) {
            D_801F0FD4[i + 3] = -1;
            for (j = 0; j < 2; j++) {
                slot                                   = BMagic_AllocEffect();
                BMAGIC_EFFECT_SLOTS[slot].target.party = g_BattleEffectBattler;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i + 3;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = j * 12 + 1;
                g_BattleEffectBattler->param.unk_0B += 1;
            }
        }
    }
    for (i = 0; i < 3; i++) {
        if (D_801F0FD4[i] == 0 && !(func_801DB524(i) & BYTE_MASK) && func_801EFDD4(&g_Game.members[i]) && g_Battle.active_battler != i) {
            D_801F0FD4[i] = -1;
            for (j = 0; j < 2; j++) {
                slot                                   = BMagic_AllocEffect();
                BMAGIC_EFFECT_SLOTS[slot].target.party = g_BattleEffectBattler;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = j * 12 + 1;
                g_BattleEffectBattler->param.unk_0B += 1;
            }
        }
    }
    if (g_Task->unk_0C > 0x600) {
        g_Task->header.step += 1;
    }
}

#include "overlays/bmagic/Effect_TickDownAndClear.h"

MATCH void func_801EF36C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Task);
}

MATCH void func_801EF3B0(void) {
    Magic058Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFA78();
        PopMatrix();
    }
}

MATCH void func_801EF454(void) {
    PartyMember* work;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        work = g_Task;
        /* kept: retail reloads the battler row at each access; a PartyMember* local changes the bytes. */
        if (BATTLER_IS_PLAYER(work->param.unk_0B)) {
            work->pos.x.fixed = g_Game.members[work->param.unk_0B].pos.x.fixed;
            work->pos.y.fixed = g_Game.members[work->param.unk_0B].pos.y.fixed;
            work->pos.z.fixed = g_Game.members[work->param.unk_0B].pos.z.fixed;
        } else {
            work->pos.x.fixed = ENEMY_COMBATANT(work->param.unk_0B).pos.x.fixed;
            work->pos.y.fixed = ENEMY_COMBATANT(work->param.unk_0B).pos.y.fixed;
            work->pos.z.fixed = ENEMY_COMBATANT(work->param.unk_0B).pos.z.fixed;
        }
        g_Task->unk_0C = 16;
        g_Task->unk_18 = 16;
        g_Task->timer  = 16;
        g_Task->header.step += 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF5D4(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_0C = work->unk_0C + work->unk_18;
    if (--work->unk_18 == 0x10) {
        work->header.step++;
    }
}

INCLUDE_ASM(func_801EF61C);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801EF74C(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    D_1F800000.view.effect.params[0] = g_Task->unk_0C + 0x80;
    D_1F800000.view.effect.params[1] = g_Task->unk_0C;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));

    for (i = 1; i <= 64; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = 0;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[2].vz = 0;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 6), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 6), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vz = 0;
        setRGB0(prim, 0x60, 0x60, 0x60);
        setRGB1(prim, 0x60, 0x60, 0x60);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G4));
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

MATCH void func_801EFA78(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    D_1F800000.view.effect.params[2] = g_Task->timer * 6;
    D_1F800000.view.effect.params[0] = g_Task->unk_0C + 0x40;
    D_1F800000.view.effect.params[1] = g_Task->unk_0C;
    D_1F800014[1].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
    D_1F800014[3].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
    if (GetGraphType() == 1) {
        tpage = 0xA5;
    } else if (GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));

    for (i = 1; i <= 16; i++) {
        prim             = GFX_BeginPolyG4(1);
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[0].vz = 0;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz = 0;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[2].vz = 0;
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[1]);
        D_1F800014[3].vz = 0;
        setRGB0(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB1(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        GFX_AddPrim(5, sizeof(POLY_G4));
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

INCLUDE_ASM(func_801EFDD4);

/* func_801EFE38 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EFE9C */
#include "overlays/bmagic/Actor_Clear.h"
