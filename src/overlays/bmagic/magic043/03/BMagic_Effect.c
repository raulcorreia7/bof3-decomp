#include "magic043_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC18(void) {
    Magic043Steps handlers;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);

    BMAGIC_RUN_EFFECT_SLOTS(BMAGIC_EFFECT_SLOTS, BMagic_DispatchEffectMode);
}

MATCH void func_801EED30(void) {
    PartyMember* actor;
    PartyMember* work;
    u16*         src;
    u16*         dst;
    u8           slot;
    u8           i;

    BMAGIC_CLEAR_EFFECTS(i);
    actor                           = g_BattleSelectedActor;
    TASK(PartyMember)->facing       = actor->facing;
    TASK(PartyMember)->pos.x.fixed  = actor->pos.x.fixed;
    TASK(PartyMember)->pos.y.fixed  = actor->pos.y.fixed;
    TASK(PartyMember)->pos.z.fixed  = actor->pos.z.fixed;
    TASK(PartyMember)->param.unk_0B = 0;
    TASK(PartyMember)->unk_09       = 9;
    TASK(PartyMember)->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot = BMagic_AllocEffect();
        if (slot != 0xFF) {
            work                                   = TASK(PartyMember);
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 8 + 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            TASK(PartyMember)->param.unk_0B += 1;
        }
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i]      = src[i];
        dst[i + 16] = src[i + 16];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

MATCH void func_801EEEF0(void) {
    PartyMember* battler;
    u8           value;

    battler                   = g_Battle.selected_actor;
    value                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = value;
    if (!(value & BYTE_MASK)) {
        GFX_PaletteFreeFadeTarget(battler);
        TASK(PartyMember)->timer  = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
        TASK(PartyMember)->unk_09 = 4;
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EEF98(void) {
    u8 count;

    g_PaletteFades[TASK(PartyMember)->timer].offset.r += 2;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g += 2;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b += 2;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count == 0) {
        TASK(PartyMember)->unk_09 = 4;
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF0B4(void) {
    u8*          selector;
    u8           slot;
    PartyMember* work;
    u8           count;

    g_PaletteFades[TASK(PartyMember)->timer].offset.r -= 2;
    g_PaletteFades[TASK(PartyMember)->timer].offset.g -= 2;
    g_PaletteFades[TASK(PartyMember)->timer].offset.b -= 2;
    count                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (TASK(PartyMember)->param.unk_0B < 2) {
        GFX_PaletteFreeFade(TASK(PartyMember)->timer);
        selector = (u8*)&g_Battle.target_selector;
        Battle_FadePoisonedBattler(*selector);
        if (g_Battle.action_id == ABILITY_WARDOFLIGHT) {
            if (Battle_CanTarget(1, *selector) & BYTE_MASK) {
                slot                               = Battle_AllocEffect(1, 72);
                work                               = TASK(PartyMember);
                g_BattleEffects[slot].unk_04       = 0;
                g_BattleEffects[slot].arg.unk_09   = 1;
                g_BattleEffects[slot].unk_0A       = 0;
                g_BattleEffects[slot].target.party = work;
                TASK(PartyMember)->param.unk_0B += 1;
            } else {
                slot                               = Battle_AllocEffect(1, 72);
                work                               = TASK(PartyMember);
                g_BattleEffects[slot].unk_04       = 8;
                g_BattleEffects[slot].arg.unk_09   = 1;
                g_BattleEffects[slot].unk_0A       = 0;
                g_BattleEffects[slot].target.party = work;
                TASK(PartyMember)->param.unk_0B += 1;
            }
        }
        TASK(PartyMember)->header.mode += 1;
    } else {
        TASK(PartyMember)->unk_09 = 4;
        TASK(PartyMember)->header.mode -= 1;
    }
}
