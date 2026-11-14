#include "magic062_03.h"
#include "menu/clock.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_DispatchMode.h"

MATCH void func_801EEC94(void) {
    PartyMember* actor;
    u16*         dst;
    u16*         src;
    PartyMember* owner;
    PartyMember* spawner;
    u8           i;
    u8           slot;

    actor                = g_Battle.selected_actor;
    g_Task->facing       = actor->facing;
    g_Task->pos.x.fixed  = actor->pos.x.fixed;
    g_Task->pos.y.fixed  = actor->pos.y.fixed;
    g_Task->pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 74);
    owner                              = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 0;
    g_BattleEffects[slot].target.party = owner;
    g_BattleEffects[slot].pos.x.fixed  = g_Task->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = g_Task->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = g_Task->pos.z.fixed;
    g_Task->param.unk_0B += 1;
    for (i = 0; i < 4; i++) {
        slot                               = Battle_AllocEffect(1, 74);
        spawner                            = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i * 8;
        g_BattleEffects[slot].unk_04       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 8 + 1;
        g_BattleEffects[slot].target.party = spawner;
        g_BattleEffects[slot].unk_0A       = g_Task->unk_09;
        g_Task->param.unk_0B += 1;
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_ReplacePaletteFade.h"

/* func_801EEF68 */
#include "overlays/bmagic/Effect_BrightenPalette.h"

/* func_801EF078 */
MATCH void Effect_NextStep(void) {
    BMagic_AdvanceEffectStep(2);
}

MATCH void func_801EF0C0(void) {
    s32          i;
    PartyMember* owner;
    u8           slot;

    g_PaletteFades[g_Task->timer].offset.red--;
    g_PaletteFades[g_Task->timer].offset.green--;
    g_PaletteFades[g_Task->timer].offset.blue--;
    if (--g_Task->unk_09 == 0) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        func_800AF814(g_Battle.target_selector);
        for (i = 0; i < 4; i++) {
            func_801EF2F0(D_800B6BF0[i]);
            slot                               = Battle_AllocEffect(1, 72);
            owner                              = g_Task;
            g_BattleEffects[slot].unk_04       = i;
            g_BattleEffects[slot].arg.unk_09   = i * 5 + 1;
            g_BattleEffects[slot].unk_0A       = i * 12 + 1;
            g_BattleEffects[slot].target.party = owner;
            g_Task->param.unk_0B++;
        }
        g_Task->header.mode++;
    }
}

MATCH void func_801EF2A0(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0) {
        flags                     = &g_Battle.state;
        g_GameCelerityTimer.hours = 5;
        *flags |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF2F0);

#include "overlays/bmagic/Effect_SetActorMatrix.h"

/* func_801EF4C4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF508(void) {
    SYS_DISPATCH_BYTE(D_801F0C18, g_Task->header.step);
    if (g_Task->header.flags != 0) {
        Effect_SetActorMatrix();
        func_801EF678();
        func_801EF934();
        PopMatrix();
    }
}

#include "overlays/bmagic/Effect_CountUpAndStep.h"

#include "overlays/bmagic/Effect_StepWhileTickUnderThree.h"

#include "overlays/bmagic/Effect_TickOnTimerZero.h"

MATCH void func_801EF678(void) {
    POLY_G3* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800000.view.effect.params[3] = g_Task->unk_09 * 5;
    D_1F800000.view.effect.params[4] = ((rand() & 3) + 3) * g_Task->unk_09;
    D_1F800000.view.effect.params[5] = ((rand() & 3) + 3) * g_Task->unk_09;
    D_1F800000.view.effect.params[6] = ((rand() & 3) + 3) * g_Task->unk_09;
    D_1F800014[2].vx                 = FIXED_MUL(rsin(0), 128U);
    D_1F800014[2].vy                 = FIXED_MUL(rcos(0), 128U);
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = 0;
        D_1F800014[0].vy = 0;
        D_1F800014[1].vx = D_1F800014[2].vx;
        D_1F800014[1].vy = D_1F800014[2].vy;
        D_1F800014[2].vx = FIXED_MUL(rsin(i << 8), 128U);
        D_1F800014[2].vy = FIXED_MUL(rcos(i << 8), 128U);
        prim             = (POLY_G3*)g_GfxPrimCursor;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        RotTransPers3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3], D_1F800000.view.effect.params[3]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        GFX_AddPrim(5, sizeof(POLY_G3));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EF934(void) {
    POLY_G4* prim;
    long     depth;
    long     flag;
    s32      i;
    s32      tpage;

    tpage = getTPage(0, 1, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
    D_1F800014[1].vx = FIXED_MUL(rsin(0), 128U);
    D_1F800014[1].vy = FIXED_MUL(rcos(0), 128U);
    D_1F800014[3].vx = FIXED_MUL(rsin(0), 256U);
    D_1F800014[3].vy = FIXED_MUL(rcos(0), 256U);
    for (i = 1; i <= 16; i++) {
        D_1F800014[0].vx = D_1F800014[1].vx;
        D_1F800014[0].vy = D_1F800014[1].vy;
        D_1F800014[2].vx = D_1F800014[3].vx;
        D_1F800014[2].vy = D_1F800014[3].vy;
        D_1F800014[1].vx = FIXED_MUL(rsin(i << 8), 128U);
        D_1F800014[1].vy = FIXED_MUL(rcos(i << 8), 128U);
        D_1F800014[3].vx = FIXED_MUL(rsin(i << 8), 256U);
        D_1F800014[3].vy = FIXED_MUL(rcos(i << 8), 256U);
        prim             = (POLY_G4*)g_GfxPrimCursor;
        D_1F800014[3].vz = 0;
        D_1F800014[2].vz = 0;
        D_1F800014[1].vz = 0;
        D_1F800014[0].vz = 0;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        GFX_AddPrim(5, sizeof(POLY_G4));
    }
    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(5, sizeof(DR_MODE));
}

MATCH void func_801EFBBC(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectModes + 5), 2, g_Task);
}

#include "overlays/bmagic/Effect_CountDownAndStep.h"

INCLUDE_ASM(func_801EFC4C);

MATCH void func_801EFD80(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    func_801F0910((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F026C();
    PopMatrix();
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        reset         = g_Task;
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFE74(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    func_801F0910((RANDOM_MASK(3)) | 0x18);
    Effect_SetActorMatrix();
    func_801F026C();
    PopMatrix();
    if (g_FrameCount & 0x1) {
        g_Task->unk_09 += 1;
    }
    task         = g_Task;
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->timer = 28 - g_Task->param.unk_0B;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EFF68(void) {
    s32 value;
    s32 value2;
    u8  value3;

    Battle_ProjectRange();
    if ((g_Task->unk_0C == 4) && (g_Task->timer < 5U)) {
        value2 = RANDOM_MASK(3) | 0x40;
    } else {
        value2 = RANDOM_MASK(3) | 0x18;
    }
    func_801F0910(value2);
    Effect_SetActorMatrix();
    func_801F026C();
    PopMatrix();
    if (g_Task->unk_0C < 4) {
        value          = g_Task->unk_10 + 1;
        g_Task->unk_10 = value;
        if (!(value & 0x7)) {
            g_Task->unk_0C += 1;
        }
    }
    g_Task->unk_09 += g_Task->unk_0C;
    if (g_Task->unk_0C == 4) {
        value3        = g_Task->timer - 1;
        g_Task->timer = value3;
        if (!(value3 & BYTE_MASK)) {
            if (g_Task->param.unk_0B == 0) {
                SND_QueueSelectionEffect(0x101);
            }
            g_Task->unk_10 = 8;
            g_Task->unk_14 = 8;
            g_Task->unk_20 = 8;
            g_Task->header.step += 1;
        }
    }
}

INCLUDE_ASM(func_801F00EC);

MATCH void func_801F026C(void) {
    POLY_G3* prim;
    u8*      first;
    s32      x;
    s32      y;
    s32      depths[16];
    long     p;
    long     flag;
    s32      tpage;
    s32      i;

    tpage = getTPage(0, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    first = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        D_1F800000.view.effect.params[1] = 0x50;
        D_1F800000.view.effect.params[0] = 0x30;
        D_1F800000.view.effect.params[7] = (i - g_Task->unk_09) / 8;
        D_1F800000.view.effect.params[4] = D_801F0BA4[g_Task->unk_04][D_1F800000.view.effect.params[7]][0];
        D_1F800000.view.effect.params[5] = D_801F0BA4[g_Task->unk_04][D_1F800000.view.effect.params[7]][1];
        D_1F800000.view.effect.params[6] = D_801F0BA4[g_Task->unk_04][D_1F800000.view.effect.params[7]][2];
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = 0;
        D_1F800014[0].vz                 = D_1F800000.view.effect.params[1];
        D_1F800000.view.effect.params[2] = (i & 0x1F) << 7;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        D_1F800000.view.effect.params[2] = ((i + 8) & 0x1F) << 7;
        D_1F800014[2].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz                 = 0;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - g_Task->unk_09) / 8] = RotAverage3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, depths, first, 4, sizeof(POLY_G3), 2);
    first = g_GfxPrimCursor;
    for (i = g_Task->unk_09; i < g_Task->unk_09 + 32; i += 8) {
        D_1F800000.view.effect.params[7] = (i - g_Task->unk_09) / 8;
        D_1F800000.view.effect.params[4] = D_801F0BD4[g_Task->unk_04][D_1F800000.view.effect.params[7]][0];
        D_1F800000.view.effect.params[5] = D_801F0BD4[g_Task->unk_04][D_1F800000.view.effect.params[7]][1];
        D_1F800000.view.effect.params[6] = D_801F0BD4[g_Task->unk_04][D_1F800000.view.effect.params[7]][2];
        D_1F800014[0].vx                 = 0;
        D_1F800014[0].vy                 = 0;
        D_1F800014[0].vz                 = -D_1F800000.view.effect.params[1];
        D_1F800000.view.effect.params[2] = (i & 0x1F) << 7;
        D_1F800014[1].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[1].vz                 = 0;
        D_1F800000.view.effect.params[2] = ((i + 8) & 0x1F) << 7;
        D_1F800014[2].vx                 = FIXED_MUL(rsin(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vy                 = FIXED_MUL(rcos(D_1F800000.view.effect.params[2]), D_1F800000.view.effect.params[0]);
        D_1F800014[2].vz                 = 0;
        prim                             = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 0);
        depths[(i - g_Task->unk_09) / 8] = RotAverage3(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, &p, &flag);
        setRGB0(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB1(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        setRGB2(prim, D_1F800000.view.effect.params[4], D_1F800000.view.effect.params[5], D_1F800000.view.effect.params[6]);
        g_GfxPrimCursor += sizeof(POLY_G3);
    }
    x = g_Task->pos.x.fixed;
    y = g_Task->pos.y.fixed;
    func_800AF0F8(x, y, depths, first, 4, sizeof(POLY_G3), 2);
}

INCLUDE_ASM(func_801F0910);
