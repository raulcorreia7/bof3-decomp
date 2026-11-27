#include "magic058_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC28(void) {
    Magic058Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.mode);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, func_801EF36C);
}

MATCH void func_801EED30(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;
    u32          slot;
    u8           i;

    BMAGIC_CLEAR_EFFECTS(i);
    for (i = 0; i < 11; i++) {
        D_801F0FD4[i] = 0;
    }
    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    work                      = SELF(PartyMember);
    actor                     = g_BattleEffectBattler;
    work->pos.x.fixed         = actor->pos.x.fixed;
    work->pos.y.fixed         = actor->pos.y.fixed;
    z                         = actor->pos.z.fixed;
    work->param.unk_0B        = 0;
    work->pos.z.fixed         = z;
    SELF(PartyMember)->header.mode += 1;
    slot                                           = Battle_AllocEffect(1, 63);
    g_BattleEffects[slot & BYTE_MASK].target.party = SELF(PartyMember);
    g_BattleEffects[slot & BYTE_MASK].header.mode  = 0;
    SELF(PartyMember)->param.unk_0B += 1;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEE78(void) {
    if (SELF(PartyMember)->param.unk_0B == 0) {
        func_801DE8C0(1, 0x3C, UI_MessageGetText(0x14U));
        SELF(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEEDC(void) {
    if (D_801EC2E4 == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EEF30 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF74(void) {
    Magic058Steps handlers;

    handlers = D_801EEC10;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    BMAGIC_DRAW_IF_ALIVE(func_801EF74C);
}

MATCH void func_801EF008(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    SELF(PartyMember)->facing = g_BattleEffectBattler->facing;
    work                      = SELF(PartyMember);
    actor                     = g_BattleEffectBattler;
    work->pos.x.fixed         = actor->pos.x.fixed;
    work->pos.y.fixed         = actor->pos.y.fixed;
    z                         = actor->pos.z.fixed;
    work->timer               = 16;
    work->unk_0C              = 8;
    work->pos.z.fixed         = z;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF080(void) {
    u8 i;
    u8 j;
    u8 slot;

    SELF(PartyMember)->unk_0C += 32;
    g_ScratchPadHalves = SELF(PartyMember)->unk_0C;
    for (i = 0; i < 8; i++) {
        if (D_801F0FD4[i + 3] == 0 && !(Battle_SlotIsBlocked((u8)(i + 3)) & BYTE_MASK) && func_801EFDD4(&g_BattleEnemyBattlers[i]) && g_Battle.active_battler != i + 3) {
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
        if (D_801F0FD4[i] == 0 && !(Battle_SlotIsBlocked((u8)i) & BYTE_MASK) && func_801EFDD4(&g_Game.members[i]) && g_Battle.active_battler != i) {
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
    if (SELF(PartyMember)->unk_0C > 0x600) {
        SELF(PartyMember)->header.step += 1;
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"

MATCH void func_801EF36C(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 1), 1, g_Self);
}

MATCH void func_801EF3B0(void) {
    Magic058Steps handlers;

    handlers = D_801EEC1C;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    BMAGIC_DRAW_IF_RUNNING(func_801EFA78);
}

MATCH void func_801EF454(void) {
    PartyMember* work;
    u8           count;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        work = SELF(PartyMember);
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
        SELF(PartyMember)->unk_0C = 16;
        SELF(PartyMember)->unk_18 = 16;
        SELF(PartyMember)->timer  = 16;
        SELF(PartyMember)->header.step += 1;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF5D4(void) {
    PartyMember* work;

    work         = SELF(PartyMember);
    work->unk_0C = work->unk_0C + work->unk_18;
    if (--work->unk_18 == 0x10) {
        work->header.step++;
    }
}

MATCH void func_801EF61C(void) {
    PartyMember* work;
    u8           timer;
    work = SELF(PartyMember);
    work->unk_0C += work->unk_18;
    if (g_FrameCount & 1) {
        work->unk_18 -= 1;
        timer       = work->timer - 1;
        work->timer = timer;
        if (timer == 0) {
            g_BattleEffectBattler->param.unk_0B -= 1;
            Actor_Clear();
        }
    }
}

#include "overlays/bmagic/shared/Effect_SetActorMatrix.h"

MATCH void func_801EF74C(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_0C + 0x80;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_0C;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);

    for (i = 1; i <= 64; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = 0;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[0]), 0);
        setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, 0);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(i << 6), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(i << 6), g_ScratchPad.cells.halves[1]), 0);
        setRGB0(prim, 0x60, 0x60, 0x60);
        setRGB1(prim, 0x60, 0x60, 0x60);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH void func_801EFA78(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    g_ScratchPad.cells.halves[2] = SELF(PartyMember)->timer * 6;
    g_ScratchPad.cells.halves[0] = SELF(PartyMember)->unk_0C + 0x40;
    g_ScratchPad.cells.halves[1] = SELF(PartyMember)->unk_0C;
    g_ScratchPadVectors[1].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[1].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[0]);
    g_ScratchPadVectors[3].vx    = FIXED_MUL(rsin(0), g_ScratchPad.cells.halves[1]);
    g_ScratchPadVectors[3].vy    = FIXED_MUL(rcos(0), g_ScratchPad.cells.halves[1]);
    tpage                        = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);

    for (i = 1; i <= 16; i++) {
        prim                      = GFX_BeginPolyG4(1);
        g_ScratchPadVectors[0].vx = g_ScratchPadVectors[1].vx;
        g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy;
        g_ScratchPadVectors[0].vz = 0;
        setVector(&g_ScratchPadVectors[1], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[0]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[0]), 0);
        setVector(&g_ScratchPadVectors[2], g_ScratchPadVectors[3].vx, g_ScratchPadVectors[3].vy, 0);
        setVector(&g_ScratchPadVectors[3], FIXED_MUL(rsin(i << 8), g_ScratchPad.cells.halves[1]), FIXED_MUL(rcos(i << 8), g_ScratchPad.cells.halves[1]), 0);
        setRGB0(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB1(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        GFX_AddPrim(BMAGIC_LAYER_BEHIND_BATTLERS, sizeof(POLY_G4));
    }

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(BMAGIC_LAYER_BEHIND_BATTLERS, tpage);
}

MATCH s32 func_801EFDD4(void* battler) {
    Actor* actor;
    s32    dx;
    s32    dz;
    s32    horizontal;
    s32    radius;
    s32    record_y;

    actor      = battler;
    dx         = (actor->pos.x.fixed >> 9) - (SELF(PartyMember)->pos.x.fixed >> 9);
    record_y   = SELF(PartyMember)->pos.y.fixed >> 9;
    dz         = (actor->pos.y.fixed >> 9) - record_y;
    horizontal = dx * dx + dz * dz;
    radius     = g_ScratchPadHalves;
    record_y   = radius * radius;
    return horizontal <= record_y;
}

/* func_801EFE38 */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EFE9C */
#include "overlays/bmagic/shared/Actor_Clear.h"
