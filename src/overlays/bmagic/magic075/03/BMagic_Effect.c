#include "magic075_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* actor;
    PartyMember* work;
    u32          slot;
    u8           i;
    u16*         dst;
    u16*         src;

    actor                           = g_Battle.selected_actor;
    SELF(PartyMember)->pos.x.fixed  = actor->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = actor->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed  = actor->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    i = 0;
    do {
        slot                               = Battle_AllocEffect(1, 37) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = i * 5 + 1;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = work;
        i++;
    } while (i < 7);
    GFX_PaletteFreeFadeTarget(actor);
    SELF(PartyMember)->timer = GFX_PaletteAllocFade(actor, 0, 0, 0, 1);
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i] = src[i];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(0x100);
}

MATCH void func_801EEDE0(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r = SELF(PartyMember)->param.unk_0B * 2;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g = SELF(PartyMember)->param.unk_0B * 2;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b = SELF(PartyMember)->param.unk_0B * 2;
    if (SELF(PartyMember)->param.unk_0B == 7) {
        SELF(PartyMember)->header.mode++;
    }
}

MATCH void func_801EEEB0(void) {
    u16* flags;

    g_PaletteFades[SELF(PartyMember)->timer].offset.r -= 2;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g -= 2;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b -= 2;
    if (g_PaletteFades[SELF(PartyMember)->timer].offset.r == 0) {
        GFX_PaletteFreeFade(SELF(PartyMember)->timer);
        Battle_MarkDamaged(g_Battle.target_selector);
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        Effect_Reset();
    }
}

/* func_801EEFF4 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF038(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF7A0 + 1, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF0D0(void) {
    s32          angle;
    s32*         angle_cell;
    u8           count;
    PartyMember* work;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        angle                                 = (SELF(PartyMember)->param.unk_0B & 0x7) << 9;
        angle_cell                            = &g_ScratchPad;
        *angle_cell                           = angle;
        SELF(PartyMember)->pos.x.fixed        = g_BattleEffectBattler->pos.x.fixed + ((rsin(angle) * 0xA000) >> 12);
        SELF(PartyMember)->pos.y.fixed        = g_BattleEffectBattler->pos.y.fixed + ((rcos(*angle_cell) * 0xA000) >> 12);
        SELF(PartyMember)->pos.z.part.integer = g_BattleEffectBattler->pos.z.part.integer + 0x180;
        SELF(PartyMember)->unk_25             = 0x1D;
        SELF(PartyMember)->unk_26             = 0;
        SELF(PartyMember)->unk_27             = 0xA0;
        SELF(PartyMember)->unk_28             = 0;
        SELF(PartyMember)->unk_5D             = 0;
        SELF(PartyMember)->unk_5E             = 0;
        SELF(PartyMember)->unk_5F             = 0;
        SELF(PartyMember)->unk_5C             = 0;
        SELF(PartyMember)->unk_2A             = 0;
        SELF(PartyMember)->unk_29             = 4;
        SELF(PartyMember)->unk_24             = 4;
        work                                  = SELF(PartyMember);
        work->unk_2B                          = 1;
        work->unk_2C.value                    = 0;
        Script_Select((SELF(PartyMember)->param.unk_0B / 3) & BYTE_MASK);
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF2A8(void) {
    PartyMember* work;

    if (Script_AnimStepOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B + 1;
        Effect_Reset();
    }
}

MATCH void func_801EF2F4(s32 radius) {
    POLY_G3* prim;
    s32      i;
    s32      tpage;

    radius += g_FrameCount & 1;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
        prim = (POLY_G3*)g_GfxPrimCursor;
        SetPolyG3(prim);
        SetSemiTrans(prim, 1);
        setXY3(prim, SELF(PartyMember)->screen_x.value, SELF(PartyMember)->screen_y.value, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), radius),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), radius), SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 8), radius),
               SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 8), radius));
        setRGB0(prim, 0x60, 0x60, 0x60);
        setRGB1(prim, 0x20, 0x20, 0x40);
        setRGB2(prim, 0x20, 0x20, 0x40);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G3));
    }
}

MATCH void func_801EF500(s32 outer, s32 inner) {
    POLY_G4* prim;
    s32      i;
    s32      tpage;

    outer += g_FrameCount & 1;
    inner += g_FrameCount & 1;
    for (i = 0; i < 16; i++) {
        tpage = getTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 320, 256);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(DR_MODE));
        prim = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(prim);
        SetSemiTrans(prim, 1);
        setXY4(prim, SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), outer), SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), outer),
               SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 8), outer), SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 8), outer),
               SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin(i << 8), inner), SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos(i << 8), inner),
               SELF(PartyMember)->screen_x.value + FIXED_MUL(rsin((i + 1) << 8), inner), SELF(PartyMember)->screen_y.value + FIXED_MUL(rcos((i + 1) << 8), inner));
        setRGB0(prim, 0x20, 0x20, 0x40);
        setRGB1(prim, 0x20, 0x20, 0x40);
        setRGB2(prim, 1, 1, 1);
        setRGB3(prim, 1, 1, 1);
        Area_CellAddPrim(SELF(PartyMember)->pos.x.fixed, SELF(PartyMember)->pos.y.fixed, 0, sizeof(POLY_G4));
    }
}
