#include "game_00.h"

MATCH void func_8019C954(void) {
    Actor* record;
    s32    index;
    s16    counter;

    index = D_80145E9B;
    TASK(Actor)->header.flags |= ACTOR_FLAG_SKIP_PALETTE_STAGE;
    TASK(Actor)->active_flags = 1;
    record                    = (Actor*)&g_SpawnedActors[index];
    TASK(Actor)->unk_2C       = record->unk_2C;
    TASK(Actor)->clut_select  = 0x7B;
    TASK(Actor)->palette_8bit = PALETTE_TYPE_CELLS_2;
    TASK(Actor)->sheet_page   = 0x1D;
    TASK(Actor)->sheet_row    = 0;
    TASK(Actor)->unk_4C       = record->unk_4C;
    TASK(Actor)->unk_2B       = 1;
    TASK(Actor)->draw_layer   = record->draw_layer;
    TASK(Actor)->unk_48       = 0;
    {
        u8* work;
        u8* next;

        work                    = TASK(u8);
        FIELD(s32, work, 0x34u) = record->pos.x.fixed;
        FIELD(s32, work, 0x38u) = record->pos.y.fixed;
        counter                 = COORD_INT(record->pos.z);
        work[0x5D]              = 0;
        next                    = TASK(u8);
        FIELD(s16, work, 0x3Eu) = counter;
        next[0x5E]              = 0;
    }
    TASK(Actor)->tint.bytes.rgb.b = 0;
    TASK(Actor)->tint.bytes.flags = 0;
    Script_Select(0x4E);
    TASK(Actor)->header.mode = 2;
}
