#include "game_00.h"

MATCH void func_801BE574(s32 count, u8* ids) {
    s32 i;

    for (i = 0; i < (count & BYTE_MASK); i++) {
        TASK_SET(&((u8*)g_Game.members)[i * BATTLE_PARTY_STRIDE]);
        ((u8*)g_Game.members)[i * BATTLE_PARTY_STRIDE] &= 0xDF;
        ACTOR_CLEAR_TINT();
        g_Task->tint.bytes.flags = 2;
        Party_ClearBattlerState(i & BYTE_MASK);
        g_Task->header.mode           = 2;
        g_Task->option_flags          = 0;
        g_Task->timer                 = 0;
        *(u32*)&D_80145FB4[i * 0x140] = ((u32*)FIELD(s32, g_AreaLoads[g_GameAreaId], 0x18u))[ids[i]];
        func_801BE710((GameReset*)&((u8*)g_Game.members)[i * BATTLE_PARTY_STRIDE + 0x118]);
        GFX_LoadPalette((g_Task->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
    }
    g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
}
