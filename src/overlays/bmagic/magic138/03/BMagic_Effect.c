#include "magic138_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/BMagic_DispatchMode.h"

MATCH void func_801EEC88(void) {
    PartyMember* work;
    PartyMember* saved_work;
    u16*         src;
    u16*         dst;
    u8           i;

    work                 = SELF(PartyMember);
    work->screen_x.value = 240;
    work->screen_y.value = 250;
    i                    = 0;
    dst                  = g_AreaPaletteCopy->rows[26].colors;
    src                  = g_AreaPaletteArena->rows[26].colors;
    for (; i < 16; i++) {
        dst[i] = src[i];
    }
    g_GfxPalettePending             = 1;
    SELF(PartyMember)->param.unk_0B = 0;
    SELF(PartyMember)->unk_09       = 0;
    saved_work                      = SELF(PartyMember);
    SELF_SET(g_BattleEffectBattler);
    Script_AnimStepLoop();
    SELF_SET(saved_work);
    saved_work->header.mode += 1;
}

MATCH void func_801EED60(void) {
    PartyMember* saved_work;
    u8           slot;

    if ((g_FrameCount & 7) == 0) {
        slot = Battle_AllocEffect(1, 86);
        if (slot != 0xFF) {
            g_BattleEffects[slot].header.mode = 0;
            g_BattleEffects[slot].header.step = 0;
            g_BattleEffects[slot].screen_x    = 220;
            g_BattleEffects[slot].screen_y    = 250;
            if (SELF(PartyMember)->unk_09 & 1) {
                g_BattleEffects[slot].screen_x += 20;
            }
            g_BattleEffects[slot].unk_0A       = SELF(PartyMember)->unk_09;
            g_BattleEffects[slot].target.party = SELF(PartyMember);
            SELF(PartyMember)->unk_09 += 1;
            SELF(PartyMember)->param.unk_0B += 1;
        }
        if (SELF(PartyMember)->unk_09 == 6) {
            SELF(PartyMember)->header.mode += 1;
        }
        saved_work = SELF(PartyMember);
        SELF_SET(g_BattleEffectBattler);
        Script_AnimStepLoop();
        SELF_SET(saved_work);
    }
}

MATCH void func_801EEED8(void) {
    PartyMember* saved_work;

    saved_work = SELF(PartyMember);
    SELF_SET(g_BattleEffectBattler);
    Script_AnimStepLoop();
    SELF_SET(saved_work);
    if (saved_work->param.unk_0B == 0) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.flags |= BATTLE_STATE_EFFECT_PLAYING;
        Effect_Reset();
    }
}

/* func_801EEF60 */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EEFA4(void) {
    Magic138Steps handlers;

    handlers  = D_801EEC10;
    g_Scripts = BMAGIC_SCRIPT_TABLE;
    SYS_DISPATCH_TASK(handlers.steps, 2, g_Self);
    if (SELF(PartyMember)->header.flags & 0x1) {
        Area_AddActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF04C(void) {
    s32 left;

    if (g_Battle.active_battler < 3) {
        if (g_BattleEffectBattler->unk_09 & 1) {
            left                      = SELF(PartyMember)->screen_x.signed_value - 40;
            SELF(PartyMember)->unk_0C = ((g_Game.members[g_Battle.active_battler].screen_x.signed_value - left) << 4) / 8;
            SELF(PartyMember)->unk_10 = ((g_Game.members[g_Battle.active_battler].screen_y.signed_value - SELF(PartyMember)->screen_y.signed_value) << 4) / 8;
        } else {
            left                      = SELF(PartyMember)->screen_x.signed_value - 20;
            SELF(PartyMember)->unk_0C = ((g_Game.members[g_Battle.active_battler].screen_x.signed_value - left) << 4) / 8;
            SELF(PartyMember)->unk_10 = ((g_Game.members[g_Battle.active_battler].screen_y.signed_value - SELF(PartyMember)->screen_y.signed_value) << 4) / 8;
        }
    } else {
        if (g_BattleEffectBattler->unk_09 & 1) {
            left                      = SELF(PartyMember)->screen_x.signed_value - 40;
            SELF(PartyMember)->unk_0C = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].screen_x - left) << 4) / 8;
            SELF(PartyMember)->unk_10 = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].screen_y - SELF(PartyMember)->screen_y.signed_value) << 4) / 8;
        } else {
            left                      = SELF(PartyMember)->screen_x.signed_value - 20;
            SELF(PartyMember)->unk_0C = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].screen_x - left) << 4) / 8;
            SELF(PartyMember)->unk_10 = ((g_BattleEnemyBattlers[g_Battle.active_battler - 3].screen_y - SELF(PartyMember)->screen_y.signed_value) << 4) / 8;
        }
    }
    SELF(PartyMember)->unk_18       = SELF(PartyMember)->screen_x.signed_value << 4;
    SELF(PartyMember)->unk_1C       = SELF(PartyMember)->screen_y.signed_value << 4;
    SELF(PartyMember)->unk_25       = 30;
    SELF(PartyMember)->unk_26       = 0;
    SELF(PartyMember)->unk_48       = 1;
    SELF(PartyMember)->unk_27       = 0xA0;
    SELF(PartyMember)->unk_28       = 0;
    SELF(PartyMember)->unk_24       = 0x84;
    SELF(PartyMember)->unk_5D       = 0;
    SELF(PartyMember)->unk_5E       = 0;
    SELF(PartyMember)->unk_5F       = 0;
    SELF(PartyMember)->unk_5C       = 0;
    SELF(PartyMember)->unk_2A       = 0;
    SELF(PartyMember)->unk_29       = 3;
    SELF(PartyMember)->unk_2C.value = 0;
    SELF(PartyMember)->unk_2B       = 0;
    Script_Select((g_Battle.target_selector - 3) & 1);
    SELF(PartyMember)->unk_09 = 3;
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF3A0(void) {
    u8 slot;

    SELF(PartyMember)->screen_x.value = SELF(PartyMember)->unk_18 >> 4;
    SELF(PartyMember)->screen_y.value = SELF(PartyMember)->unk_1C >> 4;
    SELF(PartyMember)->unk_18 += SELF(PartyMember)->unk_0C;
    SELF(PartyMember)->unk_1C += SELF(PartyMember)->unk_10;
    if (g_Battle.active_battler < 3) {
        if (SELF(PartyMember)->screen_y.signed_value < g_Game.members[g_Battle.active_battler].screen_y.signed_value - 20) {
            slot                               = Battle_AllocEffect(1, 86);
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].header.step  = 0;
            g_BattleEffects[slot].screen_x     = SELF(PartyMember)->screen_x.value;
            g_BattleEffects[slot].screen_y     = SELF(PartyMember)->screen_y.value;
            g_BattleEffects[slot].unk_0A       = SELF(PartyMember)->timer;
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            SELF(PartyMember)->header.step += 1;
        }
    } else {
        if (SELF(PartyMember)->screen_y.signed_value < g_BattleEnemyBattlers[g_Battle.active_battler - 3].screen_y - 40) {
            slot                               = Battle_AllocEffect(1, 86);
            g_BattleEffects[slot].header.mode  = 1;
            g_BattleEffects[slot].header.step  = 0;
            g_BattleEffects[slot].screen_x     = SELF(PartyMember)->screen_x.value;
            g_BattleEffects[slot].screen_y     = SELF(PartyMember)->screen_y.value;
            g_BattleEffects[slot].unk_0A       = SELF(PartyMember)->timer;
            g_BattleEffects[slot].target.party = g_BattleEffectBattler;
            SELF(PartyMember)->header.step += 1;
        }
    }
    Script_AnimStepLoop();
}

MATCH void func_801EF50C(void) {
    Effect_Reset();
}

MATCH void func_801EF52C(void) {
    Magic138Steps handlers;

    handlers  = D_801EEC1C;
    g_Scripts = BATTLE_SCRIPT_TABLE;
    SYS_DISPATCH_BYTE(handlers.steps, SELF(PartyMember)->header.step);
    if (SELF(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
    g_Scripts = AREA_SCRIPT_TABLE;
}

MATCH void func_801EF5D0(void) {
    PartyMember* work;
    SELF(PartyMember)->unk_29 = 0;
    SELF(PartyMember)->unk_25 = 0x1D;
    SELF(PartyMember)->unk_26 = 0;
    SELF(PartyMember)->unk_24 = 0x84;
    SELF(PartyMember)->unk_27 = 0xB4;
    SELF(PartyMember)->unk_28 = 0;
    work                      = SELF(PartyMember);
    work->unk_2B              = 0;
    work->unk_2C.value        = 0;
    SELF(PartyMember)->unk_2A = 0;
    Script_Select(5);
    SND_SEPlay((SELF(PartyMember)->timer & 0x1) | 0x100);
    SELF(PartyMember)->header.step += 1;
}

MATCH void func_801EF6A4(void) {
    if (Script_AnimStepLoop() != 0u) {
        SELF(PartyMember)->header.step = SELF(PartyMember)->header.step + 1;
    } else {
        Area_AddActor();
    }
}

#include "overlays/bmagic/shared/Effect_TickDownAndClear.h"
