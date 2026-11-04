#include "game_00.h"

MATCH void Game_RequestAreaChange(u16 selection_seed, u32 context_a, u32 context_b, u8 context_kind) {
    g_GameContextSeed = selection_seed;
    g_GameEntryPosX   = context_a;
    g_GameEntryPosY   = context_b;
    g_GameContextKind = context_kind;
    func_801A02E8();
    func_801A0380((s32)context_a >> 0x10, (s32)context_b >> 0x10, g_GameContextSeed);
    g_GameStateIndex = GAME_REQUEST_AREA_CHANGE;
}
