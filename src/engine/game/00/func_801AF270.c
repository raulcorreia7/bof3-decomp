#include "game_00.h"

MATCH u8* func_801AF270(u8 sprite_id, u8 flags) {
    if (flags & 0xFF)
        return (u8*)&D_801CCF7C[sprite_id & 0xFF];
    return (u8*)&D_801CCE84[sprite_id & 0xFF];
}
