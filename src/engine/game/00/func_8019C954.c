#include "game_00.h"

MATCH void func_8019C954(void) {
    Actor* record;
    s32    index;
    s16    counter;

    index = D_80145E9B;
    SELF(Actor)->header.flags |= ACTOR_FLAG_SKIP_PALETTE_STAGE;
    SELF(Actor)->active_flags = 1;
    record                    = (Actor*)&g_SpawnedActors[index];
    SELF(Actor)->unk_2C       = record->unk_2C;
    SELF(Actor)->clut_select  = 0x7B;
    SELF(Actor)->palette_8bit = PALETTE_TYPE_CELLS_2;
    SELF(Actor)->sheet_page   = 0x1D;
    SELF(Actor)->sheet_row    = 0;
    SELF(Actor)->unk_4C       = record->unk_4C;
    SELF(Actor)->unk_2B       = 1;
    SELF(Actor)->draw_layer   = record->draw_layer;
    SELF(Actor)->unk_48       = 0;
    {
        Actor* work;
        Actor* next;

        work                   = SELF(Actor);
        work->pos.x.fixed      = record->pos.x.fixed;
        work->pos.y.fixed      = record->pos.y.fixed;
        counter                = COORD_INT(record->pos.z);
        work->tint.bytes.rgb.r = 0;
        next                   = SELF(Actor);
        COORD_INT(work->pos.z) = counter;
        next->tint.bytes.rgb.g = 0;
    }
    SELF(Actor)->tint.bytes.rgb.b = 0;
    SELF(Actor)->tint.bytes.flags = 0;
    Script_Select(0x4E);
    SELF(Actor)->header.mode = 2;
}
