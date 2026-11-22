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
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->header.mode += 1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!(Battle_SlotIsBlocked(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 0x6B) & BYTE_MASK;
                work                               = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = index;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffects[slot].arg.unk_09   = BMAGIC_WORK->param.unk_0B * 16 + 1;
                BMAGIC_WORK->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!(Battle_SlotIsBlocked(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 0x6B) & BYTE_MASK;
                work                               = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = i;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffects[slot].arg.unk_09   = BMAGIC_WORK->param.unk_0B * 16 + 1;
                BMAGIC_WORK->param.unk_0B += 1;
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
    SYS_DISPATCH_TASK(D_801EF8A4, 2, g_Task);
}

MATCH void func_801EF048(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           count;
    u8           slot;
    u8           i;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        battler = (PartyMember*)&ENEMY_COMBATANT(BMAGIC_WORK->unk_04);
    } else {
        battler = &g_Game.members[BMAGIC_WORK->unk_04];
    }
    BMAGIC_WORK->pos.x.fixed  = battler->pos.x.fixed;
    BMAGIC_WORK->pos.y.fixed  = battler->pos.y.fixed;
    BMAGIC_WORK->pos.z.fixed  = battler->pos.z.fixed;
    BMAGIC_WORK->param.unk_0B = 0;
    BMAGIC_WORK->unk_09       = 0x10;
    BMAGIC_WORK->timer        = 0;
    BMAGIC_WORK->header.step += 1;
    for (i = 0; i < 7; i++) {
        slot = BMagic_AllocEffect();
        if (slot != 0xFF) {
            work                                   = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 4 + 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            BMAGIC_WORK->param.unk_0B += 1;
        }
    }
    GFX_PaletteFreeFadeTarget(battler);
    BMAGIC_WORK->timer = GFX_PaletteAllocFade(battler, 0, 0, 0, 1);
}

MATCH void func_801EF23C(void) {
    g_PaletteFades[BMAGIC_WORK->timer].offset.r += 1;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g += 1;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b += 1;
    if (--BMAGIC_WORK->unk_09 == 0) {
        BMAGIC_WORK->header.step++;
    }
}

MATCH void func_801EF348(void) {
    g_PaletteFades[BMAGIC_WORK->timer].offset.r -= 1;
    g_PaletteFades[BMAGIC_WORK->timer].offset.g -= 1;
    g_PaletteFades[BMAGIC_WORK->timer].offset.b -= 1;
    if (g_PaletteFades[BMAGIC_WORK->timer].offset.r == 0) {
        GFX_PaletteFreeFade(BMAGIC_WORK->timer);
        Battle_MarkDamaged(BMAGIC_WORK->unk_04);
        BMAGIC_WORK->header.step++;
    }
}

#include "overlays/bmagic/shared/Effect_TickOnZeroTick.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_TASK(D_801EF8B4, 1, g_Task);
}

MATCH void func_801EF524(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8B4 + 1, BMAGIC_WORK->header.step);
    if (BMAGIC_WORK->header.flags != 0 && BMAGIC_WORK->header.step != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF5BC(void) {
    s32          angle;
    u8           count;
    PartyMember* work;

    count               = BMAGIC_WORK->unk_09 - 1;
    BMAGIC_WORK->unk_09 = count;
    if (count == 0) {
        angle                        = BMAGIC_WORK->param.unk_0B & 0x7;
        g_ScratchPad.cells.halves[0] = angle << 9;
        BMAGIC_WORK->pos.x.fixed     = g_BattleEffectBattler->pos.x.fixed + rsin(g_ScratchPad.cells.halves[0]) * 0xC;
        BMAGIC_WORK->pos.y.fixed     = g_BattleEffectBattler->pos.y.fixed + rcos(g_ScratchPad.cells.halves[0]) * 0xC;
        BMAGIC_WORK->pos.z.fixed     = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
        BMAGIC_WORK->unk_25          = 0x1D;
        BMAGIC_WORK->unk_26          = 0;
        BMAGIC_WORK->unk_27          = 0xA0;
        BMAGIC_WORK->unk_28          = 0;
        BMAGIC_WORK->unk_5D          = 0;
        BMAGIC_WORK->unk_5E          = 0;
        BMAGIC_WORK->unk_5F          = 0;
        BMAGIC_WORK->unk_5C          = 0;
        BMAGIC_WORK->unk_2A          = 0;
        BMAGIC_WORK->unk_29          = 4;
        BMAGIC_WORK->unk_24          = 4;
        work                         = g_Task;
        work->unk_2B                 = 1;
        work->unk_2C.value           = 0;
        Script_Select((BMAGIC_WORK->param.unk_0B % 3) & BYTE_MASK);
        BMAGIC_WORK->header.step++;
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
