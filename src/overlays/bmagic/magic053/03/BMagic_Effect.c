#include "magic053_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC10(void) {
    Magic053Steps handlers = D_801EEC04;
    PartyMember*  saved_task;
    PartyMember*  saved_battler;
    u8            i;

    SYS_DISPATCH_BYTE(handlers.steps, g_Task->header.mode);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801F0578[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801F0578[i];
            g_BattleEffectBattler = D_801F0578[i].target.party;
            func_801EFD50();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

MATCH void func_801EED18(void) {
    PartyMember* owner;
    s32          i;
    u8           slot;

    BMAGIC_CLEAR_EFFECTS(i);
    Battle_CenterCamera();
    Battle_ProjectRange();
    if (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) {
        if (!BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            g_Task->facing = D_8014637C->facing;
        } else {
            g_Task->facing = D_8014637C->facing ^ 2;
        }
    } else {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            g_Task->facing = D_8014637C->facing;
        } else {
            g_Task->facing = D_8014637C->facing ^ 2;
        }
    }
    g_Task->param.unk_0B = 0;
    g_Task->unk_09       = 16;
    g_Task->header.mode += 1;
    for (i = 0; i < 8; i++) {
        slot                               = Battle_AllocEffect(1, 94);
        owner                              = g_Task;
        g_BattleEffects[slot].header.mode  = 0;
        g_BattleEffects[slot].target.party = owner;
        g_BattleEffects[slot].unk_04       = D_801F0548[i] >> 4;
        g_BattleEffects[slot].unk_0B       = i;
        g_BattleEffects[slot].arg.unk_09   = D_801F0548[i] + 1;
        g_Task->param.unk_0B += 1;
    }
    for (i = 0; i < AREA_PALETTE_COLORS; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW))[i] | PSX_COLOR_STP_BIT;
    }
    for (i = 0; i < 16; i++) {
        MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW))[i] = MEM_PTR(u16, AREA_PALETTE_ARENA_33C00)[i] | PSX_COLOR_STP_BIT;
    }
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BATL_OVR_ROW)) = *MEM_PTR(u16, AREA_PALETTE_ARENA_ROW(AREA_PALETTE_BATL_OVR_ROW));
    *MEM_PTR(u16, AREA_PALETTE_UPLOAD_ROW(AREA_PALETTE_BMAGIC_ROW))   = *MEM_PTR(u16, AREA_PALETTE_ARENA_33C00);
    g_GfxPalettePending                                               = 1;
}
