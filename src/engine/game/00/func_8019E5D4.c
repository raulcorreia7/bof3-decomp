#include "game_00.h"

MATCH void func_8019E5D4(void) {
    s32 value;
    u8  sel;

    Area_SceneSelectRecord(0x18);

    SELF(Actor)->active_flags = 0;
    SELF(Actor)->mirror       = 0;
    SELF(Actor)->unk_2B++;
    SELF(Actor)->unk_48 = 0;

    value = rand();
    {
        Actor* coord = SELF(Actor);
        coord->pos.x.fixed += value & HALF_MASK;
    }
    value = rand();
    {
        Actor* record   = SELF(Actor);
        record->gravity = -8;
        record->vz      = 0;
        record->pos.y.fixed += value & HALF_MASK;
    }
    value = RANDOM_MASK(3);

    if (value >= 0) {
        sel = value;
        if (value >= 3) {
            sel = 2;
        }
    } else {
        sel = 0;
    }

    ACTOR_CLEAR_TINT();
    Script_Select(sel + 0xB);
    SELF(Actor)->header.step++;
}
