#include "battle_03.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E8684(void) {
    PartyMember* temp_a0_112;
    PartyMember* temp_a0_233;
    PartyMember* temp_a1_173;
    PartyMember* temp_a1_282;
    PartyMember* temp_v1_420;
    PartyMember* var_s0;
    s32          temp_a0_187;
    s32          temp_a0_216;
    s32          temp_a0_259;
    s32          temp_v0_163;
    s32          temp_v0_318;
    s32          temp_v0_356;
    s32          temp_v1_126;
    s32          var_a1_247;
    u8           temp_a0_284;
    u8           temp_a0_299;
    u8           temp_a1_314;
    u8           temp_a1_352;
    u8           temp_v0_135;
    u8           temp_v0_147;
    u8           temp_v1_190;
    u8           temp_v1_31;

    var_s0 = SP_PTR(PartyMember, 0x0);
    var_s0 = g_Task;
    TASK_SET(g_BattleEffectBattler);
    g_Game.current                                 = &g_Game.members[g_BattleEffectBattler->slot];
    temp_v1_31                                     = g_BattleEffectBattler->slot;
    g_BattleEffectBattler->scale.x                 = 0;
    g_Game.members[temp_v1_31]                     = s_BattleBattlerTemplates[temp_v1_31];
    *(D_80145E91 + ((g_Task)->slot * 0x140))       = 6;
    *(D_80145E92 + ((g_Task)->slot * 0x140))       = 4;
    *(D_80145E93 + ((g_Task)->slot * 0x140))       = 4;
    *(D_80145E94 + ((g_Task)->slot * 0x140))       = 1;
    *(&D_80145ED8 + ((g_Task)->slot * 0x140))      = 2;
    temp_a0_112                                    = g_Task;
    *(&D_80145ED0 + (temp_a0_112->slot * 0x140))   = 0;
    temp_v1_126                                    = temp_a0_112->slot * BATTLE_PARTY_STRIDE;
    *(&D_80145FB4 + temp_v1_126)                   = *(&D_80145FB4 + temp_v1_126) | 0x2000;
    temp_v0_135                                    = temp_a0_112->slot;
    g_BattleEffects[temp_v0_135].pos.x             = g_EncounterParty[temp_v0_135].x;
    temp_v0_147                                    = temp_a0_112->slot;
    g_BattleEffects[temp_v0_147].pos.y             = g_EncounterParty[temp_v0_147].y;
    temp_v0_163                                    = temp_a0_112->slot;
    temp_a1_173                                    = g_Task;
    g_BattleEffects[temp_a1_173->slot].pos.z.fixed = Area_SampleHeight(g_BattleEffects[temp_v0_163].pos.x.fixed, g_BattleEffects[temp_v0_163].pos.y.fixed) << 0x10;
    temp_a0_187                                    = temp_a1_173->slot * BATTLE_PARTY_STRIDE;
    temp_v1_190                                    = g_Game.members[temp_a1_173->slot].chr.level;
    if ((temp_v1_190 == 7) || (temp_v1_190 == 0)) {
        g_Game.members[temp_a1_173->slot].chr.ap                           = D_801EB4C8;
        g_Game.members[temp_a1_173->slot].chr.status                       = D_801EB4CC;
        temp_a0_216                                                        = temp_a1_173->slot * BATTLE_PARTY_STRIDE;
        g_Game.members[temp_a1_173->slot].chr.fatigue                      = g_Characters[(&g_Game.members[0].character_index)[temp_a0_216]].fatigue;
        temp_a0_233                                                        = g_Task;
        *(&D_80145FB4 + (temp_a0_233->slot * 0x140))                       = D_801EB4D0;
        var_a1_247                                                         = 0;
        g_Game.members[temp_a0_233->slot].turn.action_flags.volatile_value = D_801EB4D4;
        do {
            temp_a0_259 = var_a1_247 & BYTE_MASK;
            var_a1_247 += 1;
            *(((g_Task)->slot * 0x140) + &D_80145FBC + temp_a0_259) = 0;
        } while ((u32)(var_a1_247 & BYTE_MASK) < 8U);
        func_801E0B64();
    }
    Battle_RescaleStats((g_Task)->slot);
    temp_a1_282                                   = g_Task;
    temp_a0_284                                   = temp_a1_282->slot;
    *(&D_80148344 + ((temp_a0_284 + 0xD) * 0x24)) = g_Game.members[temp_a0_284].chr.hp;
    temp_a0_299                                   = temp_a1_282->slot;
    *(&D_80148346 + ((temp_a0_299 + 0xD) * 0x24)) = g_Game.members[temp_a0_299].chr.ap;
    temp_a1_314                                   = temp_a1_282->slot;
    temp_v0_318                                   = temp_a1_314 * BATTLE_PARTY_STRIDE;
    *(&D_8014833B + ((temp_a1_314 + 0xD) * 0x24)) = (s8)((s32)(g_Game.members[temp_a1_314].chr.hp * 0x37) / (s32)g_Game.members[temp_a1_314].chr.stats.max_hp);
    temp_a1_352                                   = (g_Task)->slot;
    temp_v0_356                                   = temp_a1_352 * BATTLE_PARTY_STRIDE;
    g_MenuPanelTasks[temp_a1_352 + 0xD].unk_0C    = (u8)((s32)(g_Game.members[temp_a1_352].chr.ap * 0x37) / (s32)g_Game.members[temp_a1_352].chr.stats.max_ap);
    Actor_SelectScript(((g_Task)->facing + 4) & BYTE_MASK);
    GFX_LoadPalette(((g_Task)->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, 0U);
    func_801DDAB4((u32) * (D_80145F10 + ((g_Task)->slot * BATTLE_PARTY_STRIDE)));
    GFX_UploadPaletteRows();
    temp_v1_420 = g_Task;
    temp_v1_420->header.flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task = var_s0;
    var_s0->header.mode += 1;
}
#else
INCLUDE_ASM(func_801E8684);
#endif
