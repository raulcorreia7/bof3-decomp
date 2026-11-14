#include "magic143_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED24};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* src;
    u32          slot;
    PartyMember* task;

    src                                = g_Battle.selected_actor;
    slot                               = Battle_AllocEffect(1, 53) & BYTE_MASK;
    task                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = task;
    g_BattleEffects[slot].pos.x.fixed  = src->pos.x.fixed;
    g_BattleEffects[slot].pos.y.fixed  = src->pos.y.fixed;
    g_BattleEffects[slot].pos.z.fixed  = src->pos.z.fixed;
    g_Task->param.unk_0B               = 1;
    SND_QueueSelectionEffect(0x100);
    g_Task->header.mode += 1;
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EED70 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEDB4(void) {
    SYS_DISPATCH_BYTE((g_BMagicEffectModes + 1), g_Task->header.step);
    func_800AF764();
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        Effect_SetActorMatrixRolled();
        func_801EF23C(48, 16, 0x3);
        g_Task->param.unk_0B += 4;
        func_801EF23C(32, 80, 0xF);
        g_Task->param.unk_0B += 2;
        Effect_DrawBolt();
        g_Task->param.unk_0B += 4;
        func_801EF23C(24, BOLT_RADIUS, BOLT_FLICKER_MASK);
        g_Task->param.unk_0B -= 10;
        g_Task->unk_2E.half += 16;
        func_801EFC74();
        g_Task->unk_2E.half -= 32;
        func_801EFC74();
        PopMatrix();
    }
}

MATCH void func_801EEF10(void) {
    g_Task->param.unk_0B = RANDOM_MASK(15);
    g_Task->unk_09       = 0;
    g_Task->timer        = 0;
    g_Task->header.step++;
}

MATCH void func_801EEF78(void) {
    u8 timer;

    g_Task->timer += 4;
    g_Task->param.unk_0B += 1;
    timer = g_Task->timer;
    if (timer == 16) {
        GFX_FreePaletteFadeTarget(g_Battle.selected_actor);
        GFX_AllocPaletteFade(g_Battle.selected_actor, -8, -8, -8, 1);
        Battle_ApplyDamageFlags(g_Battle.target_selector, 16);
        g_Task->unk_09 = 32;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF054(void) {
    u8  timer;
    u8* selector;

    g_Task->param.unk_0B++;
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (timer == 0) {
        selector = &g_BattleTargetSelector;
        Battle_MarkDamaged(*selector);
        func_80196718(g_BattleSelectedActor);
        func_800AF814(*selector);
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_CountDownByTwoAndFinish.h"

#include "overlays/bmagic/Effect_SetActorMatrixRolled.h"

INCLUDE_ASM(func_801EF23C);

#include "overlays/bmagic/Effect_DrawBolt.h"

MATCH void func_801EFC74(void) {
    POLY_G3* prim;
    s32*     radius;
    s32      i;

    D_1F800000 = (rand() & 7) + g_Task->timer * 4;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0xA5 : 0x35, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    i      = 0;
    radius = &D_1F800000;
    for (; i < 8; i++) {
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 9), *radius), g_Task->unk_30.half + FIXED_MUL(rcos(i << 9), *radius),
               g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 9), *radius), g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 9), *radius));
        setRGB0(prim, g_Task->timer * 8, g_Task->timer * 8, g_Task->timer * 6);
        setRGB1(prim, 1, 1, 1);
        setRGB2(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_G3));
    }
}
