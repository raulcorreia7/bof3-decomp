#include "battle_03.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E7BA0(void) {
    PartyMember* temp_a0_288;
    PartyMember* temp_a0_409;
    PartyMember* temp_a1_349;
    PartyMember* temp_a1_458;
    PartyMember* var_a3_198;
    PartyMember* var_s1;
    s32          temp_a0_132;
    s32          temp_a0_363;
    s32          temp_a0_392;
    s32          temp_a0_435;
    s32          temp_a0_92;
    s32          temp_v0_339;
    s32          temp_v0_494;
    s32          temp_v0_532;
    s32          temp_v1_165;
    s32          temp_v1_302;
    s32          var_s0;
    s32          var_v0_49;
    u16          temp_a0_154;
    u32          temp_v0_176;
    u32          temp_v0_76;
    u8           temp_a0_460;
    u8           temp_a0_475;
    u8           temp_a1_490;
    u8           temp_a1_528;
    u8           temp_v0_311;
    u8           temp_v0_323;
    u8           temp_v1_135;
    u8           temp_v1_191;
    u8           temp_v1_366;
    void*        temp_t0_202;
    void*        var_a2_201;

    if (EMI_IsReady() != 0) {
        GFX_FreePaletteFadeTarget(&g_Game.members[g_BattleEffectBattler->slot]);
        if (*(u16*)(&g_Battle.state) & BATTLE_STATE_RELOAD_PARTY) {
            g_Battle.living_party_count = 0;
            g_Battle.party_count        = D_801463CF;
            var_s0                      = 0;
            if (D_801463CF != 0) {
                var_v0_49 = 0 & BYTE_MASK;
                do {
                    if (!(*(&D_801EBFA0 + (var_v0_49 * BATTLE_PARTY_STRIDE)) & 0x4000)) {
                        FIELD(u8, (&g_Battle.state), 0x9u) = (u8)(FIELD(u8, (&g_Battle.state), 0x9u) + 1);
                    }
                    var_s0 += 1;
                    var_v0_49 = var_s0 & BYTE_MASK;
                } while ((u32)(var_s0 & BYTE_MASK) < (u8)FIELD(u8, (&g_Battle.state), 0x8u));
            }
            D_8014835E = g_Battle.party_count;
            temp_v0_76 = g_Battle.party_count & BYTE_MASK;
            D_80148358 = (s16) * (&D_801EB4BF + temp_v0_76);
            var_s0     = 1;
            if (temp_v0_76 > 1U) {
                var_s1 = g_Game.members;
                var_s1 = g_Game.members;
                do {
                    temp_a0_92 = var_s0 & BYTE_MASK;
                    var_s0 += 1;
                    g_BattleEffects[Battle_AllocEffect(0U, 0x11U) & BYTE_MASK].target.party = &g_Game.members[temp_a0_92];
                } while ((u32)(var_s0 & BYTE_MASK) < (u8)g_Battle.party_count);
            }
        }
        var_s1 = SP_PTR(PartyMember, 0x0);
        var_s1 = g_Task;
        TASK_SET(g_BattleEffectBattler);
        g_Game.current = &g_Game.members[g_BattleEffectBattler->slot];
        temp_a0_132    = g_BattleEffectBattler->slot * BATTLE_PARTY_STRIDE;
        temp_v1_135    = g_Game.members[g_BattleEffectBattler->slot].chr.level;
        if ((temp_v1_135 == 7) || (temp_v1_135 == 0)) {
            D_801EB4C8  = g_Game.members[g_BattleEffectBattler->slot].chr.ap;
            temp_a0_154 = g_Game.members[g_BattleEffectBattler->slot].chr.status;
            D_801EB4CC  = temp_a0_154;
            temp_v1_165 = *(&D_80145FB4 + (g_BattleEffectBattler->slot * BATTLE_PARTY_STRIDE));
            D_801EB4D0  = temp_v1_165;
            temp_v0_176 = g_Game.members[g_BattleEffectBattler->slot].turn.action_flags.volatile_value;
            D_801EB4CC  = temp_a0_154 & 0xBFFF;
            D_801EB4D0  = temp_v1_165 & 0xFFFE7FFF;
            D_801EB4D4  = temp_v0_176;
            D_801EB4D4  = temp_v0_176 & 0xFFF884FD;
        }
        temp_v1_191 = (g_Task)->slot;
        var_a3_198  = &g_Game.members[temp_v1_191];
        var_a2_201  = &s_BattleBattlerTemplates[temp_v1_191];
        temp_t0_202 = var_a2_201 + BATTLE_PARTY_STRIDE;
        do {
            *(s32*)(var_a3_198)          = (s32) * (s32*)(var_a2_201);
            FIELD(s32, var_a3_198, 0x4u) = (s32)FIELD(s32, var_a2_201, 0x4u);
            var_a3_198->facing           = (s32)FIELD(s32, var_a2_201, 0x8u);
            var_a3_198->unk_0C           = FIELD(s32, var_a2_201, 0xCu);
            var_a2_201 += 0x10;
            var_a3_198 += 0x10;
        } while (var_a2_201 != temp_t0_202);
        *(D_80145E91 + ((g_Task)->slot * 0x140))       = 6;
        *(D_80145E92 + ((g_Task)->slot * 0x140))       = 4;
        *(D_80145E93 + ((g_Task)->slot * 0x140))       = 4;
        *(D_80145E94 + ((g_Task)->slot * 0x140))       = 1;
        g_Game.members[(g_Task)->slot].facing          = g_Game.members[temp_v1_191].facing;
        *(&D_80145ED8 + ((g_Task)->slot * 0x140))      = 2;
        temp_a0_288                                    = g_Task;
        *(&D_80145ED0 + (temp_a0_288->slot * 0x140))   = 0;
        temp_v1_302                                    = temp_a0_288->slot * BATTLE_PARTY_STRIDE;
        *(&D_80145FB4 + temp_v1_302)                   = *(&D_80145FB4 + temp_v1_302) | 0x2000;
        temp_v0_311                                    = temp_a0_288->slot;
        g_BattleEffects[temp_v0_311].pos.x             = g_EncounterParty[temp_v0_311].x;
        temp_v0_323                                    = temp_a0_288->slot;
        g_BattleEffects[temp_v0_323].pos.y             = g_EncounterParty[temp_v0_323].y;
        temp_v0_339                                    = temp_a0_288->slot;
        temp_a1_349                                    = g_Task;
        g_BattleEffects[temp_a1_349->slot].pos.z.fixed = Area_SampleHeight(g_BattleEffects[temp_v0_339].pos.x.fixed, g_BattleEffects[temp_v0_339].pos.y.fixed) << 0x10;
        temp_a0_363                                    = temp_a1_349->slot * BATTLE_PARTY_STRIDE;
        temp_v1_366                                    = g_Game.members[temp_a1_349->slot].chr.level;
        if ((temp_v1_366 == 7) || (temp_v1_366 == 0)) {
            g_Game.members[temp_a1_349->slot].chr.ap                           = D_801EB4C8;
            g_Game.members[temp_a1_349->slot].chr.status                       = D_801EB4CC;
            temp_a0_392                                                        = temp_a1_349->slot * BATTLE_PARTY_STRIDE;
            g_Game.members[temp_a1_349->slot].chr.fatigue                      = g_Characters[(&g_Game.members[0].character_index)[temp_a0_392]].fatigue;
            temp_a0_409                                                        = g_Task;
            var_s0                                                             = 0;
            *(&D_80145FB4 + (temp_a0_409->slot * 0x140))                       = D_801EB4D0;
            g_Game.members[temp_a0_409->slot].turn.action_flags.volatile_value = D_801EB4D4;
            do {
                temp_a0_435 = var_s0 & BYTE_MASK;
                var_s0 += 1;
                *(((g_Task)->slot * 0x140) + &D_80145FBC + temp_a0_435) = 0;
            } while ((u32)(var_s0 & BYTE_MASK) < 8U);
            func_801E0B64();
        }
        Battle_RescaleStats((g_Task)->slot);
        temp_a1_458                                   = g_Task;
        temp_a0_460                                   = temp_a1_458->slot;
        *(&D_80148344 + ((temp_a0_460 + 0xD) * 0x24)) = g_Game.members[temp_a0_460].chr.hp;
        temp_a0_475                                   = temp_a1_458->slot;
        *(&D_80148346 + ((temp_a0_475 + 0xD) * 0x24)) = g_Game.members[temp_a0_475].chr.ap;
        temp_a1_490                                   = temp_a1_458->slot;
        temp_v0_494                                   = temp_a1_490 * BATTLE_PARTY_STRIDE;
        *(&D_8014833B + ((temp_a1_490 + 0xD) * 0x24)) = (s8)((s32)(g_Game.members[temp_a1_490].chr.hp * 0x37) / (s32)g_Game.members[temp_a1_490].chr.stats.max_hp);
        temp_a1_528                                   = (g_Task)->slot;
        temp_v0_532                                   = temp_a1_528 * BATTLE_PARTY_STRIDE;
        g_MenuPanelTasks[temp_a1_528 + 0xD].unk_0C    = (u8)((s32)(g_Game.members[temp_a1_528].chr.ap * 0x37) / (s32)g_Game.members[temp_a1_528].chr.stats.max_ap);
        Actor_SelectScript(((g_Task)->facing + 4) & BYTE_MASK);
        GFX_LoadPalette(((g_Task)->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, 0U);
        func_801DDAB4((u32) * (D_80145F10 + ((g_Task)->slot * BATTLE_PARTY_STRIDE)));
        GFX_UploadPaletteRows();
        if (*(u16*)(&g_Battle.state) & BATTLE_STATE_RELOAD_PARTY) {
            *D_801454F5 = D_801463D4;
            *D_801454F6 = D_801463D5;
        } else {
            *(D_801454F5 + ((g_Task)->slot * 3)) = D_801463D4;
            *(D_801454F6 + ((g_Task)->slot * 3)) = D_801463D5;
        }
        g_Task = var_s1;
        *(u16*)(&g_Battle.state) &= ~BATTLE_STATE_RELOAD_PARTY;
        var_s1->header.mode += 1;
    }
}
#else
INCLUDE_ASM(func_801E7BA0);
#endif
