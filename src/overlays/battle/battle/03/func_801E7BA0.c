#include "battle_03.h"

/* nonmatching unmeasured: the first draft rebuilt on the typed work records; the loader gate, the blocked-slot walk and
 * the panel row writes follow retail. resume: the branch and register diffs in the state block. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E7BA0(void) {
    PartyBattler* temp_a0_288;
    PartyBattler* temp_a0_409;
    PartyBattler* temp_a1_349;
    PartyBattler* temp_a1_458;
    PartyBattler* var_a3_198;
    PartyBattler* var_s1;
    s32           temp_a0_132;
    s32           temp_a0_363;
    s32           temp_a0_392;
    s32           temp_a0_435;
    s32           temp_a0_92;
    s32           temp_v0_195;
    s32           temp_v0_339;
    s32           temp_v0_494;
    s32           temp_v0_532;
    s32           temp_v1_165;
    s32           temp_v1_302;
    s32           var_s0;
    s32           var_v0_49;
    u16           temp_a0_154;
    u32           temp_v0_176;
    u32           temp_v0_76;
    u8            temp_a0_460;
    u8            temp_a0_475;
    u8            temp_a1_490;
    u8            temp_a1_528;
    u8            temp_v0_311;
    u8            temp_v0_323;
    u8            temp_v1_135;
    u8            temp_v1_191;
    u8            temp_v1_366;
    void*         temp_t0_202;
    void*         var_a2_201;

    if (EMI_LoaderIsReady() != 0) {
        GFX_FreePaletteFadeTarget(&g_BattlePartyBattlers[D_801EB4E0->slot]);
        if (*(u16*)(&g_BattleState) & BATTLE_STATE_RELOAD_PARTY) {
            g_BattleLivingPartyCount = 0;
            g_BattlePartyCount       = D_801463CF;
            var_s0                   = 0;
            if (D_801463CF != 0) {
                var_v0_49 = 0 & BYTE_MASK;
                do {
                    if (!(*(&D_801EBFA0 + (var_v0_49 * BATTLE_PARTY_STRIDE)) & 0x4000)) {
                        FIELD(u8, (&g_BattleState), 0x9u) = (u8)(FIELD(u8, (&g_BattleState), 0x9u) + 1);
                    }
                    var_s0 += 1;
                    var_v0_49 = var_s0 & BYTE_MASK;
                } while ((u32)(var_s0 & BYTE_MASK) < (u8)FIELD(u8, (&g_BattleState), 0x8u));
            }
            D_8014835E = g_BattlePartyCount;
            temp_v0_76 = g_BattlePartyCount & BYTE_MASK;
            D_80148358 = (s16) * (&D_801EB4BF + temp_v0_76);
            var_s0     = 1;
            if (temp_v0_76 > 1U) {
                var_s1 = g_BattlePartyBattlers;
                var_s1 = g_BattlePartyBattlers;
                do {
                    temp_a0_92 = var_s0 & BYTE_MASK;
                    var_s0 += 1;
                    *(u32*)(D_801EC3A4 + ((Battle_AllocEffect(0U, 0x11U) & BYTE_MASK) * 0x78)) =
                        (u32)&g_BattlePartyBattlers[temp_a0_92];
                } while ((u32)(var_s0 & BYTE_MASK) < (u8)g_BattlePartyCount);
            }
        }
        var_s1 = SP_PTR(PartyBattler, 0x0);
        var_s1 = SP_REF(PartyBattler*, 0x44);
        TASK_SET(D_801EB4E0);
        g_GameState = &g_BattlePartyBattlers[D_801EB4E0->slot];
        temp_a0_132 = D_801EB4E0->slot * BATTLE_PARTY_STRIDE;
        temp_v1_135 = g_BattlePartyBattlers[D_801EB4E0->slot].stats.level;
        if ((temp_v1_135 == 7) || (temp_v1_135 == 0)) {
            D_801EB4C8  = *(D_80145F1A + temp_a0_132);
            temp_a0_154 = *(D_80145F10 + (D_801EB4E0->slot * BATTLE_PARTY_STRIDE));
            D_801EB4CC  = temp_a0_154;
            temp_v1_165 = *(&D_80145FB4 + (D_801EB4E0->slot * BATTLE_PARTY_STRIDE));
            D_801EB4D0  = temp_v1_165;
            temp_v0_176 = g_BattlePartyBattlers[D_801EB4E0->slot].flags_128.volatile_value;
            D_801EB4CC  = temp_a0_154 & 0xBFFF;
            D_801EB4D0  = temp_v1_165 & 0xFFFE7FFF;
            D_801EB4D4  = temp_v0_176;
            D_801EB4D4  = temp_v0_176 & 0xFFF884FD;
        }
        temp_v1_191 = (g_Task)->slot;
        temp_v0_195 = temp_v1_191 * BATTLE_PARTY_STRIDE;
        var_a3_198  = &g_BattlePartyBattlers[temp_v1_191];
        var_a2_201  = temp_v0_195 + s_BattleBattlerTemplates;
        temp_t0_202 = var_a2_201 + BATTLE_PARTY_STRIDE;
        do {
            *(s32*)(var_a3_198)          = (s32) * (s32*)(var_a2_201);
            FIELD(s32, var_a3_198, 0x4u) = (s32)FIELD(s32, var_a2_201, 0x4u);
            FIELD(s32, var_a3_198, 0x8u) = (s32)FIELD(s32, var_a2_201, 0x8u);
            var_a3_198->unk_0C           = FIELD(s32, var_a2_201, 0xCu);
            var_a2_201 += 0x10;
            var_a3_198 += 0x10;
        } while (var_a2_201 != temp_t0_202);
        *(D_80145E91 + ((g_Task)->slot * 0x140))     = 6;
        *(D_80145E92 + ((g_Task)->slot * 0x140))     = 4;
        *(D_80145E93 + ((g_Task)->slot * 0x140))     = 4;
        *(D_80145E94 + ((g_Task)->slot * 0x140))     = 1;
        g_BattlePartyBattlers[(g_Task)->slot].unk_08 = g_BattlePartyBattlers[temp_v1_191].unk_08;
        *(&D_80145ED8 + ((g_Task)->slot * 0x140))    = 2;
        temp_a0_288                                  = g_Task;
        *(&D_80145ED0 + (temp_a0_288->slot * 0x140)) = 0;
        temp_v1_302                                  = temp_a0_288->slot * BATTLE_PARTY_STRIDE;
        *(&D_80145FB4 + temp_v1_302)                 = *(&D_80145FB4 + temp_v1_302) | 0x2000;
        temp_v0_311                                  = temp_a0_288->slot;
        *(D_801EC364 + (temp_v0_311 * 0x78))         = *(D_80143F2C + (temp_v0_311 * 8));
        temp_v0_323                                  = temp_a0_288->slot;
        *(D_801EC368 + (temp_v0_323 * 0x78))         = *(D_80143F30 + (temp_v0_323 * 8));
        temp_v0_339                                  = temp_a0_288->slot * 0x78;
        temp_a1_349                                  = g_Task;
        *(D_801EC36C + (temp_a1_349->slot * 0x78)) =
            Area_SampleHeight(*(D_801EC364 + temp_v0_339), *(D_801EC368 + temp_v0_339)) << 0x10;
        temp_a0_363 = temp_a1_349->slot * BATTLE_PARTY_STRIDE;
        temp_v1_366 = g_BattlePartyBattlers[temp_a1_349->slot].stats.level;
        if ((temp_v1_366 == 7) || (temp_v1_366 == 0)) {
            *(D_80145F1A + temp_a0_363)                  = D_801EB4C8;
            *(D_80145F10 + (temp_a1_349->slot * 0x140))  = D_801EB4CC;
            temp_a0_392                                  = temp_a1_349->slot * BATTLE_PARTY_STRIDE;
            *(D_80145F1E + temp_a0_392)                  = g_Characters[*(D_80145FCC + temp_a0_392)].fatigue;
            temp_a0_409                                  = g_Task;
            var_s0                                       = 0;
            *(&D_80145FB4 + (temp_a0_409->slot * 0x140)) = D_801EB4D0;
            g_BattlePartyBattlers[temp_a0_409->slot].flags_128.volatile_value = D_801EB4D4;
            do {
                temp_a0_435 = var_s0 & BYTE_MASK;
                var_s0 += 1;
                *(((g_Task)->slot * 0x140) + &D_80145FBC + temp_a0_435) = 0;
            } while ((u32)(var_s0 & BYTE_MASK) < 8U);
            func_801E0B64();
        }
        func_800A9BD8((g_Task)->slot);
        temp_a1_458                                   = g_Task;
        temp_a0_460                                   = temp_a1_458->slot;
        *(&D_80148344 + ((temp_a0_460 + 0xD) * 0x24)) = *(D_80145F18 + (temp_a0_460 * 0x140));
        temp_a0_475                                   = temp_a1_458->slot;
        *(&D_80148346 + ((temp_a0_475 + 0xD) * 0x24)) = *(D_80145F1A + (temp_a0_475 * 0x140));
        temp_a1_490                                   = temp_a1_458->slot;
        temp_v0_494                                   = temp_a1_490 * BATTLE_PARTY_STRIDE;
        *(&D_8014833B + ((temp_a1_490 + 0xD) * 0x24)) =
            (s8)((s32)(*(D_80145F18 + temp_v0_494) * 0x37) / (s32) * (D_80145F20 + temp_v0_494));
        temp_a1_528 = (g_Task)->slot;
        temp_v0_532 = temp_a1_528 * BATTLE_PARTY_STRIDE;
        *D_8014833C[temp_a1_528 + 0xD] =
            (u8)((s32)(*(D_80145F1A + temp_v0_532) * 0x37) / (s32) * (D_80145F22 + temp_v0_532));
        Actor_SelectScript(((g_Task)->unk_08 + 4) & BYTE_MASK);
        GFX_StagePalette(((g_Task)->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, 0U);
        func_801DDAB4((u32) * (D_80145F10 + ((g_Task)->slot * BATTLE_PARTY_STRIDE)));
        GFX_UploadPaletteRows();
        if (*(u16*)(&g_BattleState) & BATTLE_STATE_RELOAD_PARTY) {
            *D_801454F5 = D_801463D4;
            *D_801454F6 = D_801463D5;
        } else {
            *(D_801454F5 + ((g_Task)->slot * 3)) = D_801463D4;
            *(D_801454F6 + ((g_Task)->slot * 3)) = D_801463D5;
        }
        g_Task = var_s1;
        *(u16*)(&g_BattleState) &= ~BATTLE_STATE_RELOAD_PARTY;
        var_s1->mode += 1;
    }
}
#else
INCLUDE_ASM(func_801E7BA0);
#endif
