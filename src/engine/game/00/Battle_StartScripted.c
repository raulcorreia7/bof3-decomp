#include "game_00.h"

MATCH void Battle_StartScripted(u8 mode_byte) {
    u8 seed;

    g_BattleEncounter = mode_byte;
    D_80145E91[0]     = 5;
    D_80145E92[0]     = 0;
    D_80145E93[0]     = 0;
    D_80145E94[0]     = 0;
    g_AreaWalkFlags |= AREA_WALK_TRANSITION;
    seed             = s_BattleModeRecords[(mode_byte & BYTE_MASK) * 4];
    g_BattleSurprise = 0;
    g_BattleOptions  = seed;
}
