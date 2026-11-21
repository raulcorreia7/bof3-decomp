#include "area098_13.h"

/* Spawns the capture probe actor from the party member the task points at. */
MATCH void func_801F2C48(void) {
    u8            slot;
    u8            option_flags;
    SpawnedActor* row;
    Actor*        actor;
    Actor*        parent;
    SpawnedActor* src;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        D_801F6520 = g_Game.members[g_Task->option_flags].character_index != 0;
        row        = &g_SpawnedActors[slot];
        GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
        option_flags        = g_Task->option_flags;
        src                 = (SpawnedActor*)&g_Game.members[option_flags];
        *row                = *src;
        actor               = (Actor*)row;
        actor->header.flags = 1;
        actor->header.mode  = 2;
        actor->header.step  = 0;
        actor->unk_05       = ACTOR_TYPE_FACING_PROBE;
        actor->pos.x.fixed  = g_Game.members[g_Task->option_flags].pos.x.fixed;
        actor->pos.y.fixed  = g_Game.members[g_Task->option_flags].pos.y.fixed;
        actor->pos.z.fixed  = g_Game.members[g_Task->option_flags].pos.z.fixed;
        actor->screen_x     = D_801F5F58[D_801F6520].x;
        actor->screen_y     = D_801F5F58[D_801F6520].y;
        actor->sheet_page   = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        actor->sheet_row    = 0x80;
        actor->active_flags |= 0x88;
        parent = g_Task;
        g_Task = actor;
        Script_Select(actor->direction);
        Area_AddGridActor();
        Actor_Clear();
        g_Task        = parent;
        parent->timer = 2;
    }
    g_Task->header.mode += 1;
}
