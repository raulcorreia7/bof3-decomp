#include "magic159_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback handlers[2] = {func_801EEC5C, func_801EED84};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

MATCH void func_801EEC5C(void) {
    PartyMember* work;
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    work               = g_Task;
    work->pos.x.fixed  = g_BattleSelectedActor->pos.x.fixed;
    work->pos.y.fixed  = g_BattleSelectedActor->pos.y.fixed;
    work->pos.z.fixed  = g_BattleSelectedActor->pos.z.fixed;
    work->param.unk_0B = 0;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 88) & BYTE_MASK;
    target                             = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 8;
    g_BattleEffects[slot].target.party = target;
    g_Task->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEDE4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE28(void) {
    SYS_DISPATCH_BYTE(D_801EF424, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        Battle_ProjectRange();
        g_Task->unk_2E.half += 8;
        g_Task->unk_30.half -= 0x10;
        func_801EF08C();
    }
}

MATCH void func_801EEEC8(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--g_Task->unk_09 == 0) {
        src              = g_BattleEffectBattler;
        dst              = g_Task;
        dst->pos.x.fixed = src->pos.x.fixed;
        dst->pos.y.fixed = src->pos.y.fixed;
        dst->pos.z       = src->pos.z;
        dst->unk_09      = 0x10;
        g_Task->timer    = 0;
        g_Task->header.step++;
    }
}

MATCH void func_801EEF58(void) {
    PartyMember* work;

    work = g_Task;
    work->unk_09++;
    work = g_Task;
    work->timer += 2;
    if (work->timer == 16) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EEFC4(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer > 32) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801EF014(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = g_Task;
    work->unk_09++;
    work        = g_Task;
    count       = work->timer - 2;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        func_801E5988();
    }
}

MATCH void func_801EF08C(void) {
    POLY_GT4* prim;
    s32       tpage;

    if (GetGraphType() == 1 || GetGraphType() == 2) {
        tpage = 0xA5;
    } else {
        tpage = 0x35;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(DR_MODE));
    D_1F800000.view.effect.params[0] = g_Task->unk_09 << 1;
    D_1F800000.view.effect.params[1] = g_Task->timer << 3;
    D_1F800000.view.effect.params[2] = g_Task->timer;
    prim                             = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    prim->x0    = g_Task->unk_2E.half + FIXED_MUL(rcos(3584), D_1F800000.view.effect.params[0]);
    prim->y0    = g_Task->unk_30.half + FIXED_MUL(rsin(3584), D_1F800000.view.effect.params[0]);
    prim->x1    = g_Task->unk_2E.half + FIXED_MUL(rcos(2560), D_1F800000.view.effect.params[0]);
    prim->y1    = g_Task->unk_30.half + FIXED_MUL(rsin(2560), D_1F800000.view.effect.params[0]);
    prim->x2    = g_Task->unk_2E.half + FIXED_MUL(rcos(512), D_1F800000.view.effect.params[0]);
    prim->y2    = g_Task->unk_30.half + FIXED_MUL(rsin(512), D_1F800000.view.effect.params[0]);
    prim->x3    = g_Task->unk_2E.half + FIXED_MUL(rcos(1536), D_1F800000.view.effect.params[0]);
    prim->y3    = g_Task->unk_30.half + FIXED_MUL(rsin(1536), D_1F800000.view.effect.params[0]);
    prim->tpage = GetTPage(0, 1, 832, 256);
    prim->clut  = GetClut(0, 506);
    prim->u0    = 8;
    prim->v0    = 8;
    prim->u1    = 87;
    prim->v1    = 8;
    prim->u2    = 8;
    prim->v2    = 72;
    prim->u3    = 87;
    prim->v3    = 72;
    setRGB0(prim, D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[1]);
    setRGB1(prim, D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[1], D_1F800000.view.effect.params[1]);
    setRGB2(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
    setRGB3(prim, D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2], D_1F800000.view.effect.params[2]);
    Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 2, sizeof(POLY_GT4));
}
