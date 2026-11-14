#include "magic088_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC20.h"

MATCH void func_801EECA4(void) {
    PartyMember* actor;
    u8           slot;
    u8           i;
    u16*         src;
    u16*         dst;

    actor                = g_Battle.selected_actor;
    g_Task->pos.x.fixed  = actor->pos.x.fixed;
    g_Task->pos.y.fixed  = actor->pos.y.fixed;
    g_Task->pos.z.fixed  = actor->pos.z.fixed;
    g_Task->unk_04       = func_801EF34C();
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 32);
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0;
    g_BattleEffects[slot].unk_0A       = 0;
    g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
    g_Task->param.unk_0B += 1;
    slot                               = Battle_AllocEffect(1, 32);
    g_BattleEffects[slot].target.party = g_Task;
    g_BattleEffects[slot].header.mode  = 1;
    g_BattleEffects[slot].unk_04       = g_Task->unk_04;
    g_BattleEffects[slot].arg.unk_09   = g_Task->unk_09;
    g_BattleEffects[slot].unk_0A       = 16;
    g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
    g_Task->param.unk_0B += 1;
    for (i = 0, dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW), src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW); i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(0x100);
}

MATCH void func_801EEEF4(void) {
    PartyMember* battler;
    u8           value;

    battler        = g_Battle.selected_actor;
    value          = g_Task->unk_09 - 1;
    g_Task->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        battler->unk_5C = 1;
        GFX_FreePaletteFadeTarget(battler);
        g_Task->timer  = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
        g_Task->unk_09 = 8;
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEFA0(void) {
    /* FAKE: retail keeps an 8-byte frame that no statement explains. */
    FAKE_STACK_PADS(u8, 8);
    u8 timer;

    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        g_Task->header.mode = g_Task->header.mode + 1;
    }
}

#include "overlays/bmagic/Effect_Pause.h"

INCLUDE_ASM(func_801EF0A8);

MATCH void func_801EF1AC(void) {
    u32 slot;

    if (g_Task->param.unk_0B != 0) {
        return;
    }
    if (func_800AED5C(D_800B6BF0[g_Task->unk_04], g_Battle.target_selector) & BYTE_MASK) {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].unk_04       = g_Task->unk_04 + 4;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        g_Task->param.unk_0B++;
    } else {
        slot                               = Battle_AllocEffect(1, 72) & BYTE_MASK;
        g_BattleEffects[slot].target.party = g_Task;
        g_BattleEffects[slot].unk_04       = 8;
        g_BattleEffects[slot].arg.unk_09   = 1;
        g_BattleEffects[slot].unk_0A       = 0;
        g_Task->param.unk_0B++;
    }
    g_Task->header.mode++;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

MATCH s32 func_801EF34C(void) {
    s32 result;

    if (LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) {
        switch (LOHU(g_Battle.action_id)) {
            case ABILITY_WEAKEN:
            case 0xC0:
                result = 0;
                break;
            case ABILITY_MOLASSES:
            case ABILITY_SLOW:
            case 0xBE:
                result = 1;
                break;
            case ABILITY_TARBABY:
            case ABILITY_BLUNT:
            case 0xBF:
                result = 2;
                break;
            default:
                result = 3;
                break;
        }
    } else if (LOHU(g_Battle.action_id) == 0x112) {
        g_Battle.action_id = ABILITY_WEAKEN;
        result             = 0;
    } else {
        result = 3;
    }
    return result;
}

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF4E0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF524(void) {
    SYS_DISPATCH_BYTE(D_801F0030, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF68C();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderTwo.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EF68C(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x125 : 0x55;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[5] = g_Task->unk_09 * 12;
    D_1F800000.view.effect.params[0] = 240;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        prim             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[5]);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0x25 : 0x15;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EF900(void) {
    SYS_DISPATCH_BYTE(D_801F005C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Effect_SetActorMatrix();
        func_801EFAE8();
        func_801EFB34();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountDownTimerStep.h"

#include "overlays/bmagic/Effect_CountUpAndStepAt32.h"

MATCH void func_801EFA2C(void) {
    u8 timer_next;

    timer_next    = g_Task->timer - 1;
    g_Task->timer = timer_next;
    if (!(timer_next & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFA94(void) {
    PartyMember* work;

    work         = g_Task;
    work->unk_09 = work->unk_09 - 2;
    if (g_Task->unk_09 == 0) {
        func_801E5988();
    }
}

MATCH void func_801EFAE8(void) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if (i & 0x1) {
            D_801F003C[i] = D_801F003C[i] - 1;
        } else {
            D_801F003C[i] = D_801F003C[i] + 1;
        }
    }
}

MATCH void func_801EFB34(void) {
    POLY_F4* prim;
    long     depth;
    long     flag;
    s32      band;
    s32      i;
    s32      tpage;

    tpage = GetGraphType() == 1 || GetGraphType() == 2 ? 0xA5 : 0x35;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[4] = g_Task->unk_09;
    for (band = 0; band < 6; band++) {
        D_1F800000.view.effect.params[0] = band << 5;
        D_1F800000.view.effect.params[1] = (band + 1) << 5;
        D_1F800000.view.effect.params[5] = D_801EFFE0[g_Task->unk_04][band][0] * (g_Task->unk_09 >> 1);
        D_1F800000.view.effect.params[6] = D_801EFFE0[g_Task->unk_04][band][1] * (g_Task->unk_09 >> 1);
        D_1F800000.view.effect.params[7] = D_801EFFE0[g_Task->unk_04][band][2] * (g_Task->unk_09 >> 1);
        D_1F800000.view.effect.params[3] = (D_801F003C[band] & 0xF) << 8;
        D_1F800014[1].vx                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[1]);
        D_1F800014[1].vy                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[1]);
        D_1F800014[1].vz                 = -(D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[4]));
        D_1F800000.view.effect.params[3] = ((D_801F003C[band] + 1) & 0xF) << 8;
        D_1F800014[3].vx                 = FIXED_MUL(rcos(0), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vy                 = FIXED_MUL(rsin(0), D_1F800000.view.effect.params[0]);
        D_1F800014[3].vz                 = -(D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[4]));
        for (i = 1; i <= 64; i++) {
            D_1F800000.view.effect.params[2] = i << 6;
            D_1F800014[0].vx                 = D_1F800014[1].vx;
            D_1F800014[0].vy                 = D_1F800014[1].vy;
            D_1F800014[0].vz                 = D_1F800014[1].vz;
            D_1F800014[2].vx                 = D_1F800014[3].vx;
            D_1F800014[2].vy                 = D_1F800014[3].vy;
            D_1F800014[2].vz                 = D_1F800014[3].vz;
            D_1F800014[1].vx                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
            D_1F800014[1].vy                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[1]);
            D_1F800014[1].vz                 = -(D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[4]));
            D_1F800000.view.effect.params[3] = ((i + D_801F003C[band] + 1) & 0xF) << 8;
            D_1F800014[3].vx                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
            D_1F800014[3].vy                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
            D_1F800014[3].vz                 = -(D_1F800000.view.effect.params[4] + FIXED_MUL(rsin(D_1F800000.view.effect.params[3]), D_1F800000.view.effect.params[4]));
            prim                             = (POLY_F4*)g_GfxPrimCursor;
            SetPolyF4(prim);
            SetSemiTrans(prim, 1);
            RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
            setRGB0(prim, D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6], D_1F800000.view.effect.params[7]);
            Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_F4));
        }
    }
}
