#include "magic213_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_RunSlotsWithSetup.h"

MATCH void func_801EED04(void) {
    PartyMember* work;
    u16*         dst;
    u16*         src;
    u32          slot;
    u8           index;
    u8           i;

    BMAGIC_CLEAR_EFFECTS(i);
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->header.mode += 1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 107) & BYTE_MASK;
                work                               = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = index;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffects[slot].arg.unk_09   = SELF(PartyMember)->param.unk_0B * 16 + 1;
                SELF(PartyMember)->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 107) & BYTE_MASK;
                work                               = SELF(PartyMember);
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = i;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffects[slot].arg.unk_09   = SELF(PartyMember)->param.unk_0B * 16 + 1;
                SELF(PartyMember)->param.unk_0B += 1;
            }
        }
    }
    BMAGIC_POINT_AT_PALETTE_ROW(dst, src, i);
    for (; i < 16; i++) {
        dst[i] = src[i];
    }
    g_GfxPalettePending = 1;
    SND_SEQueueSelection(EMI_SE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/shared/Effect_StartOnZeroTick.h"

/* func_801EEFC0 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF004(void) {
    SYS_DISPATCH_TASK(D_801EF8A4, 2, g_Self);
}

MATCH void func_801EF048(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           count;
    u8           slot;
    u8           i;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        battler = (PartyMember*)&ENEMY_COMBATANT(SELF(PartyMember)->unk_04);
    } else {
        battler = &g_Game.members[SELF(PartyMember)->unk_04];
    }
    SELF(PartyMember)->pos.x.fixed  = battler->pos.x.fixed;
    SELF(PartyMember)->pos.y.fixed  = battler->pos.y.fixed;
    SELF(PartyMember)->pos.z.fixed  = battler->pos.z.fixed;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0x10;
    SELF(PartyMember)->timer        = 0;
    SELF(PartyMember)->header.step += 1;
    for (i = 0; i < 7; i++) {
        slot = BMagic_AllocEffect();
        if (slot != 0xFF) {
            work                                   = SELF(PartyMember);
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 4 + 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            SELF(PartyMember)->param.unk_0B += 1;
        }
    }
    GFX_PaletteFreeFadeTarget(battler);
    SELF(PartyMember)->timer = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
}

MATCH void func_801EF23C(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r += 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g += 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b += 1;
    if (--SELF(PartyMember)->unk_09 == 0) {
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF348(void) {
    g_PaletteFades[SELF(PartyMember)->timer].offset.r -= 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.g -= 1;
    g_PaletteFades[SELF(PartyMember)->timer].offset.b -= 1;
    if (g_PaletteFades[SELF(PartyMember)->timer].offset.r == 0) {
        GFX_PaletteFreeFade(SELF(PartyMember)->timer);
        Battle_MarkDamaged(SELF(PartyMember)->unk_04);
        SELF(PartyMember)->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_TASK(D_801EF8B4, 1, g_Self);
}

MATCH void func_801EF524(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8B4 + 1, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0 && SELF(PartyMember)->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF5BC(void) {
    s32          angle;
    u8           count;
    PartyMember* work;

    count                     = SELF(PartyMember)->unk_09 - 1;
    SELF(PartyMember)->unk_09 = count;
    if (count == 0) {
        angle                          = SELF(PartyMember)->param.unk_0B & 0x7;
        g_ScratchPad.cells.halves[0]   = angle << 9;
        SELF(PartyMember)->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + rsin(g_ScratchPad.cells.halves[0]) * 0xC;
        SELF(PartyMember)->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + rcos(g_ScratchPad.cells.halves[0]) * 0xC;
        SELF(PartyMember)->pos.z.fixed = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
        SELF(PartyMember)->unk_25      = 0x1D;
        SELF(PartyMember)->unk_26      = 0;
        SELF(PartyMember)->unk_27      = 0xA0;
        SELF(PartyMember)->unk_28      = 0;
        SELF(PartyMember)->unk_5D      = 0;
        SELF(PartyMember)->unk_5E      = 0;
        SELF(PartyMember)->unk_5F      = 0;
        SELF(PartyMember)->unk_5C      = 0;
        SELF(PartyMember)->unk_2A      = 0;
        SELF(PartyMember)->unk_29      = 4;
        SELF(PartyMember)->unk_24      = 4;
        work                           = SELF(PartyMember);
        work->unk_2B                   = 1;
        work->unk_2C.value             = 0;
        Script_Select((SELF(PartyMember)->param.unk_0B % 3) & BYTE_MASK);
        SELF(PartyMember)->header.step++;
    }
}

MATCH void func_801EF7A0(void) {
    PartyMember* work;

    if (Script_AnimStepOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

/* func_801EF7EC */
#include "overlays/bmagic/shared/BMagic_AllocEffect.h"

/* func_801EF850 */
#include "overlays/bmagic/shared/Actor_Clear.h"
