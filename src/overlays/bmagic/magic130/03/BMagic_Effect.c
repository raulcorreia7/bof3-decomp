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
    g_Task->facing       = g_BattleEffectBattler->facing;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 30;
    g_Task->header.mode += 1;
    slot                               = Battle_AllocEffect(1, 102) & BYTE_MASK;
    work                               = g_Task;
    g_BattleEffects[slot].header.mode  = 0;
    g_BattleEffects[slot].target.party = work;
    g_Task->param.unk_0B += 1;
    for (i = 0; i < 6; i++) {
        slot                               = Battle_AllocEffect(1, 102) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 1;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].target.party = work;
        g_Task->param.unk_0B += 1;
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < AREA_PALETTE_COLORS; i++) {
        *dst++ = *src++ | PSX_COLOR_STP_BIT;
    }
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW)) = *MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW));
    g_GfxPalettePending                                               = 1;
    SND_QueueSelectionSE(0x100);
    SND_QueueSelectionSE(0x101);
}
