#include "magic159_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* func_801EEC04 */
MATCH void BMagic_GloomUpdate(void) {
    Callback handlers[2] = {BMagic_GloomInit, Effect_MarkDamagedOnZeroTick};

    SYS_DISPATCH_TASK(handlers, 1, g_Task);
}

/* func_801EEC5C */
MATCH void BMagic_GloomInit(void) {
    PartyMember* work;
    PartyMember* target;
    u16*         src;
    u16*         dst;
    u16          i;
    u32          slot;

    work               = TASK(PartyMember);
    work->pos.x.fixed  = g_BattleSelectedActor->pos.x.fixed;
    work->pos.y.fixed  = g_BattleSelectedActor->pos.y.fixed;
    work->pos.z.fixed  = g_BattleSelectedActor->pos.z.fixed;
    work->param.unk_0B = 0;
    TASK(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, BMAGIC_EFFECT_GLOOM) & BYTE_MASK;
    target                             = TASK(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].arg.unk_09   = 8;
    g_BattleEffects[slot].target.party = target;
    TASK(PartyMember)->param.unk_0B += 1;
    BMAGIC_BRIGHTEN_PALETTE_ROW(dst, src, i);
    g_GfxPalettePending = 1;
    Battle_ApplyDamageFlags(g_Battle.target_selector, 0x10);
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/shared/Effect_MarkDamagedOnZeroTick.h"

/* func_801EEDE4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

/* func_801EEE28 */
MATCH void BMagic_GloomFlareUpdate(void) {
    SYS_DISPATCH_BYTE(g_BMagicGloomFlareSteps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0 && TASK(PartyMember)->header.step != 0) {
        Battle_ProjectRange();
        TASK(PartyMember)->screen_x.value += 8;
        TASK(PartyMember)->screen_y.value -= 0x10;
        BMagic_GloomDrawFlare();
    }
}

/* func_801EEEC8 */
MATCH void BMagic_GloomFlareWait(void) {
    PartyMember* src;
    PartyMember* dst;

    if (--TASK(PartyMember)->unk_09 == 0) {
        src                      = g_BattleEffectBattler;
        dst                      = TASK(PartyMember);
        dst->pos.x.fixed         = src->pos.x.fixed;
        dst->pos.y.fixed         = src->pos.y.fixed;
        dst->pos.z               = src->pos.z;
        dst->unk_09              = 0x10;
        TASK(PartyMember)->timer = 0;
        TASK(PartyMember)->header.step++;
    }
}

/* func_801EEF58 */
MATCH void BMagic_GloomFlareGrow(void) {
    PartyMember* work;

    work = TASK(PartyMember);
    work->unk_09++;
    work = TASK(PartyMember);
    work->timer += 2;
    if (work->timer == 16) {
        work = TASK(PartyMember);
        work->header.step++;
    }
}

/* func_801EEFC4 */
MATCH void BMagic_GloomFlareHold(void) {
    u8 timer;

    timer                     = TASK(PartyMember)->unk_09 + 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer > 32) {
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

/* func_801EF014 */
MATCH void BMagic_GloomFlareEnd(void) {
    PartyMember* work;
    PartyMember* active;
    u8           count;

    work = TASK(PartyMember);
    work->unk_09++;
    work        = TASK(PartyMember);
    count       = work->timer - 2;
    work->timer = count;
    if (count == 0) {
        active = BATTLE_ACTIVE_WORK;
        active->param.unk_0B--;
        Effect_Reset();
    }
}

/* func_801EF08C */
MATCH void BMagic_GloomDrawFlare(void) {
    POLY_GT4* prim;
    s32       tpage;

    tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(DR_MODE));
    g_ScratchPad.cells.halves[0] = TASK(PartyMember)->unk_09 << 1;
    g_ScratchPad.cells.halves[1] = TASK(PartyMember)->timer << 3;
    g_ScratchPad.cells.halves[2] = TASK(PartyMember)->timer;
    prim                         = (POLY_GT4*)g_GfxPrimCursor;
    SetPolyGT4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(3584), g_ScratchPad.cells.halves[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(3584), g_ScratchPad.cells.halves[0]),
           TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(2560), g_ScratchPad.cells.halves[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(2560), g_ScratchPad.cells.halves[0]),
           TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(512), g_ScratchPad.cells.halves[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(512), g_ScratchPad.cells.halves[0]),
           TASK(PartyMember)->screen_x.value + FIXED_MUL(rcos(1536), g_ScratchPad.cells.halves[0]), TASK(PartyMember)->screen_y.value + FIXED_MUL(rsin(1536), g_ScratchPad.cells.halves[0]));
    prim->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 832, 256);
    prim->clut  = GetClut(0, 506);
    setUVWH(prim, 8, 8, 79, 64);
    setRGB0(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
    setRGB1(prim, g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1], g_ScratchPad.cells.halves[1]);
    setRGB2(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    setRGB3(prim, g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2], g_ScratchPad.cells.halves[2]);
    Area_CellAddPrim(TASK(PartyMember)->pos.x.fixed, TASK(PartyMember)->pos.y.fixed, 2, sizeof(POLY_GT4));
}
