#include "game_00.h"

/* func_801AF270 */
MATCH u8* UI_GetSpriteRect(u8 sprite_id, u8 flags) {
    if (flags & BYTE_MASK)
        return (u8*)&D_801CCF7C[sprite_id & BYTE_MASK];
    return (u8*)&D_801CCE84[sprite_id & BYTE_MASK];
}
