#include "battle_03.h"

/* nonmatching unmeasured: tried the 0x140-byte panel copy as one struct assignment through a PartyBattler view of
 * D_801EBF20, which gives retail's aligned four-word loop instead of the first-draft word-by-word body (65.62%). residual: the
 * body is 80 bytes short and keeps s1-s3 saved where retail saves only s0. resume: a body whose per-field writes
 * re-read g_Task like the retail sequence and need no crossing temporaries. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E8684(void) {
    PartyBattler* temp_a0_112;
    PartyBattler* temp_a0_233;
    PartyBattler* temp_a1_173;
    PartyBattler* temp_a1_282;
    PartyBattler* temp_v1_420;
    PartyBattler* var_s0;
    s32           temp_a0_187;
    s32           temp_a0_216;
    s32           temp_a0_259;
    s32           temp_v0_163;
    s32           temp_v0_318;
    s32           temp_v0_356;
    s32           temp_v1_126;
    s32           var_a1_247;
    u8            temp_a0_284;
    u8            temp_a0_299;
    u8            temp_a1_314;
    u8            temp_a1_352;
    u8            temp_v0_135;
    u8            temp_v0_147;
    u8            temp_v1_190;
    u8            temp_v1_31;

    var_s0                            = SP_PTR(PartyBattler, 0x0);
    var_s0                            = SP_REF(PartyBattler*, 0x44);
    g_Task                            = (PartyBattler*)D_801EB4E0;
    g_GameState                       = &g_BattlePartyBattlers[D_801EB4E0->slot];
    temp_v1_31                        = D_801EB4E0->slot;
    D_801EB4E0->unk_40                = 0;
    g_BattlePartyBattlers[temp_v1_31] = *(PartyBattler*)(s_BattleBattlerTemplates + (temp_v1_31 * BATTLE_PARTY_STRIDE));
    *(D_80145E91 + ((g_Task)->slot * 0x140))     = 6;
    *(D_80145E92 + ((g_Task)->slot * 0x140))     = 4;
    *(D_80145E93 + ((g_Task)->slot * 0x140))     = 4;
    *(D_80145E94 + ((g_Task)->slot * 0x140))     = 1;
    *(&D_80145ED8 + ((g_Task)->slot * 0x140))    = 2;
    temp_a0_112                                  = g_Task;
    *(&D_80145ED0 + (temp_a0_112->slot * 0x140)) = 0;
    temp_v1_126                                  = temp_a0_112->slot * BATTLE_PARTY_STRIDE;
    *(&D_80145FB4 + temp_v1_126)                 = *(&D_80145FB4 + temp_v1_126) | 0x2000;
    temp_v0_135                                  = temp_a0_112->slot;
    *(D_801EC364 + (temp_v0_135 * 0x78))         = *(D_80143F2C + (temp_v0_135 * 8));
    temp_v0_147                                  = temp_a0_112->slot;
    *(D_801EC368 + (temp_v0_147 * 0x78))         = *(D_80143F30 + (temp_v0_147 * 8));
    temp_v0_163                                  = temp_a0_112->slot * 0x78;
    temp_a1_173                                  = g_Task;
    *(D_801EC36C + (temp_a1_173->slot * 0x78)) =
        Area_SampleHeight(*(D_801EC364 + temp_v0_163), *(D_801EC368 + temp_v0_163)) << 0x10;
    temp_a0_187 = temp_a1_173->slot * BATTLE_PARTY_STRIDE;
    temp_v1_190 = g_BattlePartyBattlers[temp_a1_173->slot].stats.level;
    if ((temp_v1_190 == 7) || (temp_v1_190 == 0)) {
        *(D_80145F1A + temp_a0_187)                  = D_801EB4C8;
        *(D_80145F10 + (temp_a1_173->slot * 0x140))  = D_801EB4CC;
        temp_a0_216                                  = temp_a1_173->slot * BATTLE_PARTY_STRIDE;
        *(D_80145F1E + temp_a0_216)                  = g_Characters[*(D_80145FCC + temp_a0_216)].fatigue;
        temp_a0_233                                  = g_Task;
        *(&D_80145FB4 + (temp_a0_233->slot * 0x140)) = D_801EB4D0;
        var_a1_247                                   = 0;
        g_BattlePartyBattlers[temp_a0_233->slot].flags_128.volatile_value = D_801EB4D4;
        do {
            temp_a0_259 = var_a1_247 & BYTE_MASK;
            var_a1_247 += 1;
            *(((g_Task)->slot * 0x140) + &D_80145FBC + temp_a0_259) = 0;
        } while ((u32)(var_a1_247 & BYTE_MASK) < 8U);
        func_801E0B64();
    }
    func_800A9BD8((g_Task)->slot);
    temp_a1_282                                   = g_Task;
    temp_a0_284                                   = temp_a1_282->slot;
    *(&D_80148344 + ((temp_a0_284 + 0xD) * 0x24)) = *(D_80145F18 + (temp_a0_284 * 0x140));
    temp_a0_299                                   = temp_a1_282->slot;
    *(&D_80148346 + ((temp_a0_299 + 0xD) * 0x24)) = *(D_80145F1A + (temp_a0_299 * 0x140));
    temp_a1_314                                   = temp_a1_282->slot;
    temp_v0_318                                   = temp_a1_314 * BATTLE_PARTY_STRIDE;
    *(&D_8014833B + ((temp_a1_314 + 0xD) * 0x24)) =
        (s8)((s32)(*(D_80145F18 + temp_v0_318) * 0x37) / (s32) * (D_80145F20 + temp_v0_318));
    temp_a1_352 = (g_Task)->slot;
    temp_v0_356 = temp_a1_352 * BATTLE_PARTY_STRIDE;
    *D_8014833C[temp_a1_352 + 0xD] =
        (u8)((s32)(*(D_80145F1A + temp_v0_356) * 0x37) / (s32) * (D_80145F22 + temp_v0_356));
    Actor_SelectScript(((g_Task)->unk_08 + 4) & BYTE_MASK);
    GFX_StagePalette(((g_Task)->slot << 6) + BATTLE_ACTION_BLOCK_TABLE, 0U);
    func_801DDAB4((u32) * (D_80145F10 + ((g_Task)->slot * BATTLE_PARTY_STRIDE)));
    GFX_UploadPaletteRows();
    temp_v1_420 = g_Task;
    temp_v1_420->flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task = var_s0;
    var_s0->mode += 1;
}
#else
INCLUDE_ASM(func_801E8684);
#endif
