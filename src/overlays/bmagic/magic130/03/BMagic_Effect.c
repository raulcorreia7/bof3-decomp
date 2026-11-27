#include "magic130_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    u32          slot;
    s32          i;
    u16*         dst;
    u16*         src;

    Battle_CenterCamera();
    SELF(PartyMember)->facing       = g_BattleEffectBattler->facing;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 30;
    SELF(PartyMember)->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 102) & BYTE_MASK;
    work                               = SELF(PartyMember);
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    SELF(PartyMember)->param.unk_0B += 1;
    for (i = 0; i < 6; i++) {
        slot                               = Battle_AllocEffect(1, 102) & BYTE_MASK;
        work                               = SELF(PartyMember);
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = work;
        SELF(PartyMember)->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    g_AreaPaletteCopy->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0] = g_AreaPaletteArena->rows[AREA_PALETTE_BATL_OVR_ROW].colors[0];
    g_GfxPalettePending                                          = 1;
    SND_SEQueueSelection(0x100);
    SND_SEQueueSelection(0x101);
}
