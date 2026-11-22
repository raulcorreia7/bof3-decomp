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
    BMAGIC_WORK->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 88) & BYTE_MASK;
    target                             = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 8;
    g_BattleEffects[slot].target.party = target;
    BMAGIC_WORK->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEDE4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEE28(void) {
    SYS_DISPATCH_BYTE(D_801EF424, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Battle_ProjectRange();
        BMAGIC_WORK->screen_x.value += 8;
        BMAGIC_WORK->screen_y.value -= 0x10;
        func_801EF08C();
    }
}

MATCH void func_801EEEC8(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--BMAGIC_WORK->unk_09 == 0) {
        src                = g_BattleEffectBattler;
        dst                = g_Task;
        dst->pos.x.fixed   = src->pos.x.fixed;
        dst->pos.y.fixed   = src->pos.y.fixed;
        dst->pos.z         = src->pos.z;
        dst->unk_09        = 0x10;
        BMAGIC_WORK->timer = 0;
        BMAGIC_WORK->header.step++;
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

    timer               = BMAGIC_WORK->unk_09 + 1;
    BMAGIC_WORK->unk_09 = timer;
    if (timer > 32) {
        BMAGIC_WORK->header.step = BMAGIC_WORK->header.step + 1;
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
        Effect_Reset();
    }
}

MATCH void func_801EF08C(void) {
    POLY_GT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = BMAGIC_WORK->unk_09 << 1;
    g_ScratchPad.cells.halves[1] = BMAGIC_WORK->timer << 3;
    g_ScratchPad.cells.halves[2] = BMAGIC_WORK->timer;
    prim                         = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]),
           BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]),
           BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]), BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]),
           BMAGIC_WORK->screen_x.value + FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), BMAGIC_WORK->screen_y.value + FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 8, 8, 79, 64);
    setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
    setRGB1(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
    setRGB2(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    setRGB3(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    Area_CellAddPrim(BMAGIC_WORK->pos.x.fixed, BMAGIC_WORK->pos.y.fixed, 2, sizeof(POLY_GT4));
}
