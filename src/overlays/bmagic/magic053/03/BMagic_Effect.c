#include "magic053_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic053Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F0578[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F0578[i];
            g_BattleEffectBattler = D_801F0578[i].target.party;
            func_801EFD50();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED18(void) {
    PartyMember* owner;
    s32          i;
    u8           slot;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    Battle_CenterCamera();
    Battle_ProjectRange();
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (!BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            g_Task->facing = D_8014637C->facing;
        } else {
            g_Task->facing = D_8014637C->facing ^ 2;
        }
    } else {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            g_Task->facing = D_8014637C->facing;
        } else {
            g_Task->facing = D_8014637C->facing ^ 2;
        }
    }
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 94);
        owner                              = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = owner;
        g_BattleEffects[slot].unk_04       = D_801F0548[i] >> 4;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = D_801F0548[i] + 1;
        g_Task->param.unk_0B += 1;
    }
    for (i = 0; i < 256; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW)[i] | 0x8000;
    }
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00)[i] | 0x8000;
    }
    *MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW) = *MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    *MEM_PTR(u16, AREA_PALETTE_WORK + 2 * AREA_PALETTE_ROW)  = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                      = 1;
}

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EF064 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF0A8(void) {
    g_ScriptTable = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801F0554, g_Task->header.step);
    if (g_Task->header.flags & 0x1) {
        if (g_Task->header.step != 0) {
            if (g_Task->header.step < 4) {
                Battle_ProjectRange();
                func_8014D290();
                Effect_SetActiveActorMatrix();
                Effect_DrawShadedDisc();
                BMagic_DrawDarkRing();
                PopMatrix();
            }
        }
    }
    g_ScriptTable = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF174(void) {
    PartyMember* work;
    PartyMember* sprite;
    s16*         angle;
    u8           count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        angle                            = &D_1F800000.view.effect.params[2];
        *angle                           = g_Task->param.unk_0B << 9;
        D_1F800000.view.effect.params[0] = (rand() & 0x10) + 0x18;
        g_Task->pos.x.fixed              = g_BattleEffectBattler->pos.x.fixed + rsin(*angle) * D_1F800000.view.effect.params[0];
        g_Task->pos.y.fixed              = g_BattleEffectBattler->pos.y.fixed + rcos(*angle) * D_1F800000.view.effect.params[0];
        g_Task->facing                   = g_BattleEffectBattler->facing;
        g_Task->unk_0C                   = 0x20000;
        g_Task->unk_10                   = 0;
        g_Task->unk_14                   = TO_COORD(1536);
        func_801DD350(g_Task);
        g_Task->pos.x.fixed += g_Task->unk_0C;
        g_Task->pos.y.fixed += g_Task->unk_10;
        g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + g_Task->unk_14;
        g_Task->unk_0C      = -0x2000;
        g_Task->unk_10      = 0;
        g_Task->unk_20      = 0x600000;
        func_801DD350(g_Task);
        g_Task->unk_25      = 0x1D;
        g_Task->unk_26      = 0;
        g_Task->unk_27      = 0x1A;
        g_Task->unk_28      = 1;
        work                = g_Task;
        work->unk_48        = 2;
        work->scale.x       = 0x10000;
        work->scale.y       = 0x10000;
        g_Task->unk_5D      = 0;
        g_Task->unk_5E      = 0;
        g_Task->unk_5F      = 0;
        g_Task->unk_5C      = 0;
        g_Task->unk_2A      = 0;
        g_Task->unk_29      = 4;
        sprite              = g_Task;
        sprite->unk_2B      = 1;
        sprite->unk_2C.half = 0;
        g_Task->unk_24      = 0;
        Actor_SelectScript(0);
        g_Task->param.unk_0B = 0;
        g_Task->unk_09       = 16;
        g_Task->timer        = 16;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF420(void) {
    PartyMember* work;
    PartyMember* owner;
    u8           count;
    u8           i;
    u8           slot;

    work = g_Task;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    work->unk_14 -= work->unk_20;
    work->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + work->unk_14;
    work->param.unk_0B += 8;
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        if (g_Task->unk_04 & 1) {
            SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x01));
        } else {
            SND_QueueSelectionFx(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
        }
        g_Task->unk_04 = 0;
        for (i = 0; i < 8; i++) {
            slot = BMagic_AllocEffect();
            if (slot != GAME_NONE) {
                owner                                  = g_Task;
                BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
                BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
                BMAGIC_EFFECT_SLOTS[slot].target.party = owner;
                g_Task->unk_04++;
            }
        }
        Actor_SelectScript(1);
        g_AreaCameraAngle.vx += 0x14;
        g_Task->unk_09 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF5C0(void) {
    s16* state;
    u16  angle;
    u8   timer;

    Actor_StepAnimOnce();
    if (g_Task->unk_09 & 0x1) {
        state = &g_AreaCameraAngle.vx;
        angle = *state + 0x14;
    } else {
        state = &g_AreaCameraAngle.vx;
        angle = *state - 0x14;
    }
    *state         = angle;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_AreaCameraAngle.vx = -0x2AAU;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF674(void) {
    u8 timer;

    timer = g_Task->timer;
    if (timer != 0) {
        g_Task->timer = timer - 2;
    }
    if (Actor_StepAnimOnce() & BYTE_MASK) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF6D8(void) {
    PartyMember* work;

    if (g_Task->unk_04 == 0) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        func_801E5988();
    }
}

#include "overlays/bmagic/Effect_SetActiveActorMatrix.h"

/* func_801EF7E0 */
#include "overlays/bmagic/Effect_DrawShadedDisc.h"

#include "overlays/bmagic/BMagic_DrawDarkRing.h"

MATCH void func_801EFD50(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 6), 1, g_Task);
}

MATCH void func_801EFD94(void) {
    SYS_DISPATCH_BYTE(D_801F056C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801F01C0();
        PopMatrix();
    }
}

MATCH void func_801EFE1C(void) {
    s32  r;
    s32  direction;
    s16* angle = &D_1F800004;

    r                   = rand();
    direction           = g_Task->param.unk_0B;
    g_Task->unk_0C      = (r & 0x7) + 8;
    *angle              = direction << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + (rsin(*angle) * g_Task->unk_0C);
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + (rcos(*angle) * g_Task->unk_0C);
    g_Task->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed;
    g_Task->unk_09      = 8;
    g_Task->timer       = 16;
    g_Task->header.step += 1;
}

MATCH void func_801EFF24(void) {
    PartyMember* task;
    s16*         angle_cell;
    s32          direction;
    s32          velocity;

    task       = g_Task;
    angle_cell = &D_1F800004;
    direction  = task->param.unk_0B;
    task->unk_0C += 2;
    *angle_cell         = direction << 9;
    velocity            = rsin((s16)(direction << 9)) * g_Task->unk_0C;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + velocity;
    velocity            = rcos(*angle_cell) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + velocity;
    if (--g_Task->unk_09 == 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801F0018(void) {
    s16* angle_cell;
    s32  phase;
    u8   count;

    angle_cell = &D_1F800004;
    phase      = g_Task->param.unk_0B;
    g_Task->unk_0C += 1;
    *angle_cell         = phase << 9;
    g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin((s16)(phase << 9)) * g_Task->unk_0C;
    g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(*angle_cell) * g_Task->unk_0C;
    count               = g_Task->timer - 1;
    g_Task->timer       = count;
    if (count == 0) {
        g_BattleEffectBattler->unk_04 -= 1;
        Actor_Clear();
    }
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

MATCH void func_801F01C0(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0x125;
    } else {
        tpage = 0x55;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    D_1F800000.view.effect.params[0] = 0x100;
    D_1F80000A                       = g_Task->timer * 6;
    D_1F800014[0].vx                 = FIXED_MUL(rcos(ANGLE_45), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vy                 = FIXED_MUL(rsin(ANGLE_45), D_1F800000.view.effect.params[0]);
    D_1F800014[0].vz                 = 0;
    D_1F800014[1].vx                 = FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vy                 = FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    D_1F800014[1].vz                 = 0;
    D_1F800014[2].vx                 = FIXED_MUL(rcos(3584), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rsin(3584), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vz                 = 0;
    D_1F800014[3].vx                 = FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vy                 = FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    D_1F800014[3].vz                 = 0;
    setTPage(prim, 0, 1, 832, 256);
    /* FAKE: a volatile store keeps the clut write ahead of the texture-point stores; the best pure-C body is 0x2C8 against retail's 0x2D4. */
    VOL(u16, prim->clut) = GetClut(0, 482);
    setUV4(prim, 0, 128, 32, 128, 0, 160, 32, 160);
    setRGB0(prim, D_1F80000A, D_1F80000A, D_1F80000A);
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    GFX_AddPrim(5, sizeof(POLY_FT4));
}

/* func_801F0494 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F8 */
#include "overlays/bmagic/Actor_Clear.h"
