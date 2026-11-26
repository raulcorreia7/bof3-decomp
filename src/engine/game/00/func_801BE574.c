#include "game_00.h"

MATCH void func_801BE574(s32 count, u8* ids) {
    s32 i;

    for (i = 0; i < (count & BYTE_MASK); i++) {
        SELF_SET(&g_Game.members[i]);
        ((u8*)g_Game.members)[i * BATTLE_PARTY_STRIDE] &= 0xDF;
        ACTOR_CLEAR_TINT();
        SELF(Actor)->tint.bytes.flags = 2;
        Party_BattlersClearState(i & BYTE_MASK);
        SELF(Actor)->header.mode        = 2;
        SELF(Actor)->option_flags       = 0;
        SELF(Actor)->timer              = 0;
        g_Game.members[i].u.field.index = ((u32*)FIELD(s32, g_AreaLoads[g_GameAreaId], 0x18u))[ids[i]];
        func_801BE710((GameReset*)&((u8*)g_Game.members)[i * BATTLE_PARTY_STRIDE + 0x118]);
        GFX_PaletteLoad((SELF(Actor)->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
    }
    g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
}
