#include "game_00.h"

MATCH void func_8019C954(void) {
    Actor* record;
    s32    index;
    s16    counter;

    index = D_80145E9B;
    g_Task->header.flags |= ACTOR_FLAG_SKIP_PALETTE_STAGE;
    g_Task->active_flags = 1;
    record               = (Actor*)&g_SpawnedActors[index];
    g_Task->unk_2C       = record->unk_2C;
    g_Task->unk_27       = 0x7B;
    g_Task->unk_28       = PALETTE_KIND_CELLS_2;
    g_Task->unk_25       = 0x1D;
    g_Task->unk_26       = 0;
    g_Task->unk_4C       = record->unk_4C;
    g_Task->unk_2B       = 1;
    g_Task->draw_layer   = record->draw_layer;
    g_Task->unk_48       = 0;
    {
        u8* work;
        u8* next;

        work                    = (u8*)g_Task;
        FIELD(s32, work, 0x34u) = record->pos.x.fixed;
        FIELD(s32, work, 0x38u) = record->pos.y.fixed;
        counter                 = COORD_INT(record->pos.z);
        work[0x5D]              = 0;
        next                    = (u8*)g_Task;
        FIELD(s16, work, 0x3Eu) = counter;
        next[0x5E]              = 0;
    }
    g_Task->tint.bytes.unk_5F = 0;
    g_Task->tint.bytes.flags  = 0;
    Actor_SelectScript(0x4E);
    g_Task->header.mode = 2;
}
