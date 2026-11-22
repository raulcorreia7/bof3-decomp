#include "engine/game/00/game_00.h"

/* func_801AF270 */
MATCH UvRect* UI_SpriteGetRect(u8 sprite_id, u8 flags) {
    if (flags & BYTE_MASK)
        return &D_801CCF7C[sprite_id & BYTE_MASK];
    return &D_801CCE84[sprite_id & BYTE_MASK];
}
