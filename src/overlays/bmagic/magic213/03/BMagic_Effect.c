#include "magic213_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/Effect_RunSlotsWithSetup.h"

MATCH void func_801EED04(void) {
    PartyMember* work;
    u16*         dst;
    u16*         src;
    u32          slot;
    u8           index;
    u8           i;

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        BMAGIC_EFFECT_SLOTS[i].header.flags = 0;
        BMAGIC_EFFECT_SLOTS[i].header.mode  = 0;
        BMAGIC_EFFECT_SLOTS[i].header.step  = 0;
    }
    g_Task->param.unk_0B = 0;
    g_Task->header.mode += 1;
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        for (i = 0; i < 8; i++) {
            index = i + BATTLE_PARTY_CHARACTERS_COUNT;
            if (!(func_801DB524(index) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 0x6B) & BYTE_MASK;
                work                               = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = index;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffects[slot].arg.unk_09   = g_Task->param.unk_0B * 16 + 1;
                g_Task->param.unk_0B += 1;
            }
        }
    } else {
        for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
            if (!(func_801DB524(i) & BYTE_MASK)) {
                slot                               = Battle_AllocEffect(1, 0x6B) & BYTE_MASK;
                work                               = g_Task;
                g_BattleEffects[slot].header.mode  = 0;
                g_BattleEffects[slot].unk_04       = i;
                g_BattleEffects[slot].target.party = work;
                g_BattleEffects[slot].arg.unk_09   = g_Task->param.unk_0B * 16 + 1;
                g_Task->param.unk_0B += 1;
            }
        }
    }
    i   = 0;
    dst = MEM_PTR(u16, AREA_PALETTE_WORK + 26 * AREA_PALETTE_ROW);
    src = MEM_PTR(u16, AREA_PALETTE_ARENA + 26 * AREA_PALETTE_ROW);
    for (; i < 16; i++) {
        dst[i] = src[i];
    }
    g_GfxPalettePending = 1;
    SND_QueueSelectionEffect(EMI_CUE_ID(SND_BANK_COMMON, 0x00));
}

#include "overlays/bmagic/Effect_StartOnZeroTick.h"

/* func_801EEFC0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EF004(void) {
    SYS_DISPATCH_TASK(D_801EF8A4, 2, g_Task);
}

MATCH void func_801EF048(void) {
    PartyMember* battler;
    PartyMember* work;
    u8           count;
    u8           slot;
    u8           i;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count != 0) {
        return;
    }
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        battler = (PartyMember*)&ENEMY_COMBATANT(g_Task->unk_04);
    } else {
        battler = &g_Game.members[g_Task->unk_04];
    }
    g_Task->pos.x.fixed  = battler->pos.x.fixed;
    g_Task->pos.y.fixed  = battler->pos.y.fixed;
    g_Task->pos.z.fixed  = battler->pos.z.fixed;
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 0x10;
    g_Task->timer        = 0;
    g_Task->header.step += 1;
    for (i = 0; i < 7; i++) {
        slot = BMagic_AllocEffect();
        if (slot != 0xFF) {
            work                                   = g_Task;
            BMAGIC_EFFECT_SLOTS[slot].header.mode  = 0;
            BMAGIC_EFFECT_SLOTS[slot].unk_0B       = i;
            BMAGIC_EFFECT_SLOTS[slot].arg.unk_09   = i * 4 + 1;
            BMAGIC_EFFECT_SLOTS[slot].target.party = work;
            g_Task->param.unk_0B += 1;
        }
    }
    GFX_FreePaletteFadeTarget(battler);
    g_Task->timer = GFX_AllocPaletteFade(battler, 0, 0, 0, 1);
}

INCLUDE_ASM(func_801EF23C);

MATCH void func_801EF348(void) {
    g_PaletteFades[g_Task->timer].offset.red -= 1;
    g_PaletteFades[g_Task->timer].offset.green -= 1;
    g_PaletteFades[g_Task->timer].offset.blue -= 1;
    if (g_PaletteFades[g_Task->timer].offset.red == 0) {
        GFX_FreePaletteFade(g_Task->timer);
        Battle_MarkDamaged(g_Task->unk_04);
        g_Task->header.step++;
    }
}

#include "overlays/bmagic/Effect_TickOnZeroTick.h"

MATCH void func_801EF4E0(void) {
    SYS_DISPATCH_TASK(D_801EF8B4, 1, g_Task);
}

MATCH void func_801EF524(void) {
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(D_801EF8B4 + 1, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_8014D290();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF5BC(void) {
    s32          angle;
    u8           count;
    PartyMember* work;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (count == 0) {
        angle                               = g_Task->param.unk_0B & 0x7;
        D_1F800000.view.area.entity_counter = angle << 9;
        g_Task->pos.x.fixed                 = g_BattleEffectBattler->pos.x.fixed + rsin(D_1F800000.view.area.entity_counter) * 0xC;
        g_Task->pos.y.fixed                 = g_BattleEffectBattler->pos.y.fixed + rcos(D_1F800000.view.area.entity_counter) * 0xC;
        g_Task->pos.z.fixed                 = g_BattleEffectBattler->pos.z.fixed + 0x01800000;
        g_Task->unk_25                      = 0x1D;
        g_Task->unk_26                      = 0;
        g_Task->unk_27                      = 0xA0;
        g_Task->unk_28                      = 0;
        g_Task->unk_5D                      = 0;
        g_Task->unk_5E                      = 0;
        g_Task->unk_5F                      = 0;
        g_Task->unk_5C                      = 0;
        g_Task->unk_2A                      = 0;
        g_Task->unk_29                      = 4;
        g_Task->unk_24                      = 4;
        work                                = g_Task;
        work->unk_2B                        = 1;
        work->unk_2C.half                   = 0;
        Actor_SelectScript((g_Task->param.unk_0B % 3) & BYTE_MASK);
        g_Task->header.step++;
    }
}

MATCH void func_801EF7A0(void) {
    PartyMember* work;

    if (Actor_StepAnimOnce() != 0u) {
        work               = (PartyMember*)g_BattleEffectBattler;
        work->param.unk_0B = work->param.unk_0B - 1;
        Actor_Clear();
    }
}

/* func_801EF7EC */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801EF850 */
#include "overlays/bmagic/Actor_Clear.h"
