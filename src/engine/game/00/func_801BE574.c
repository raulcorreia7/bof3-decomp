#include "game_00.h"

MATCH void func_801BE574(s32 count, u8* ids) {
    s32 i;

    for (i = 0; i < (count & BYTE_MASK); i++) {
        g_SpadWork = (Actor*)&((u8*)g_BattlePartyBattlers)[i * BATTLE_PARTY_STRIDE];
        ((u8*)g_BattlePartyBattlers)[i * BATTLE_PARTY_STRIDE] &= 0xDF;
        g_SpadWork->tint.bytes.unk_5D = 0;
        g_SpadWork->tint.bytes.unk_5E = 0;
        g_SpadWork->tint.bytes.unk_5F = 0;
        g_SpadWork->tint.bytes.flags  = 2;
        Party_ClearBattlerState(i & BYTE_MASK);
        g_SpadWork->unk_01            = 2;
        g_SpadWork->option_flags      = 0;
        g_SpadWork->unk_09            = 0;
        *(u32*)&D_80145FB4[i * 0x140] = ((u32*)FIELD(s32, g_AreaLoads[g_GameAreaId], 0x18u))[ids[i]];
        func_801BE710((GameResetRecord*)&((u8*)g_BattlePartyBattlers)[i * BATTLE_PARTY_STRIDE + 0x118]);
        GFX_StagePalette((g_SpadWork->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
    }
    g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
}
