#include "game_00.h"

MATCH bool func_801C27E0(s8 tuning_delta) {
    if (func_801C2894(tuning_delta) & BYTE_MASK) {
        GFX_PaletteLoad(((SELF(Actor)->unk_05 << 6) + GAME_PALETTE_STAGE), 0);
        SELF(Actor)->header.flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        ACTOR_CLEAR_TINT();
        SELF(Actor)->tint.bytes.flags = 0;
        return true;
    }
    return false;
}
