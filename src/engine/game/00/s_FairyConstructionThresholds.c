#include "game_00.h"

u8 s_FairyConstructionThresholds[12] = {0x14, 0x14, 0x14, 0x28, 0x14, 0x14, 0x3C, 0x14, 0x14, 0x14, 0x0D, 0x00};

FloorDamageColors g_PartyFloorDamageColors = {{
    PARTY_DAMAGE_COLOR_RED,
    PARTY_DAMAGE_COLOR_RED,
    PARTY_DAMAGE_COLOR_RED,
    PARTY_DAMAGE_COLOR_RED,
    PARTY_DAMAGE_COLOR_PURPLE,
    PARTY_DAMAGE_COLOR_YELLOW,
    PARTY_DAMAGE_COLOR_BLUE,
    PARTY_DAMAGE_COLOR_BLUE,
    PARTY_DAMAGE_COLOR_BLUE,
}};

FloorDamages g_PartyFloorDamages = {
    {
        {4, 0, 0},
        {8, 0, 0},
        {16, 0, 0},
        {32, 0, 0},
        {2, 0, STATUS_POISONED},
        {0, 0, STATUS_CONFUSED},
        {0, 4, 0},
        {0, 8, 0},
        {0, 32, 0},
    },
};

PaletteColors g_PartyDamageColors = {{0x0010, 0x4010, 0x0210, 0x4000}};
