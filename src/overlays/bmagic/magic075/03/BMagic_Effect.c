#include "magic075_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u8           i;
    u16*         dst;
    u16*         src;

    actor                = g_Battle.selected_actor;
    g_Task->pos.x.fixed  = actor->pos.x.fixed;
    g_Task->pos.y.fixed  = actor->pos.y.fixed;
    g_Task->pos.z.fixed  = actor->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 37) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 5 + 1;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = work;
        i++;
    } while (i < 7);
    GFX_FreePaletteFadeTarget(actor);
    g_Task->timer = GFX_AllocPaletteFade(actor, 0, 0, 0, 1);
    i             = 0;
    dst           = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src           = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i] = src[i];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(0x100);
}

INCLUDE_ASM(func_801EEDE0);

INCLUDE_ASM(func_801EEEB0);

/* func_801EEFF4 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF038(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF7A0 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF0D0(void) {
    s32          angle;
    s32*         angle_cell;
    u8           count;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle                      = (g_Task->param.unk_0B & 0x7) << 9;
        angle_cell                 = &D_1F800000;
        *angle_cell                = angle;
        g_Task->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle) * 0xA000) >> 12);
        g_Task->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0xA000) >> 12);
        g_Task->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer + 0x180;
        g_Task->unk_25             = 0x1D;
        g_Task->unk_26             = 0;
        g_Task->unk_27             = 0xA0;
        g_Task->unk_28             = 0;
        g_Task->unk_5D             = 0;
        g_Task->unk_5E             = 0;
        g_Task->unk_5F             = 0;
        g_Task->unk_5C             = 0;
        g_Task->unk_2A             = 0;
        g_Task->unk_29             = 4;
        g_Task->unk_24             = 4;
        work                       = g_Task;
        work->unk_2B               = 1;
        work->unk_2C.half          = 0;
        Actor_SelectScript((g_Task->param.unk_0B / 3) & BYTE_MASK);
        g_Task->header.step++;
    }
}

MATCH void func_801EF2A8(void) {
    PartyMember* work;

    if (Actor_StepAnimOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B + 1;
        func_801E5988();
    }
}

MATCH void func_801EF2F4(s32 radius) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    radius += g_FrameCount & 1;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, g_Task->unk_2E.half, g_Task->unk_30.half, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 8), radius), g_Task->unk_30.half + FIXED_MUL(rcos(i << 8), radius),
               g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 8), radius), g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 8), radius));
        setRGB0(prim, 0x60, 0x60, 0x60);
        setRGB1(prim, 0x20, 0x20, 0x40);
        setRGB2(prim, 0x20, 0x20, 0x40);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_G3));
    }
}

MATCH void func_801EF500(s32 outer, s32 inner) {
    POLY_G4* prim;
    s32      i;
    s32      tpage;

    outer += g_FrameCount & 1;
    inner += g_FrameCount & 1;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(0, 1, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY4(prim, g_Task->unk_2E.half + FIXED_MUL(rsin(i << 8), outer), g_Task->unk_30.half + FIXED_MUL(rcos(i << 8), outer), g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 8), outer),
               g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 8), outer), g_Task->unk_2E.half + FIXED_MUL(rsin(i << 8), inner), g_Task->unk_30.half + FIXED_MUL(rcos(i << 8), inner),
               g_Task->unk_2E.half + FIXED_MUL(rsin((i + 1) << 8), inner), g_Task->unk_30.half + FIXED_MUL(rcos((i + 1) << 8), inner));
        setRGB0(prim, 0x20, 0x20, 0x40);
        setRGB1(prim, 0x20, 0x20, 0x40);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        Area_AddCellPrim(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 0, sizeof(POLY_G4));
    }
}
