#include "area098_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2C48(void) {
    u8            slot;
    u8            option_flags;
    SpawnedActor* row;
    Actor*        actor;
    Actor*        parent;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        D_801F6520 = g_Game.members[g_Task->option_flags].character_index != 0;
        row        = &g_SpawnedActors[slot];
        GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
        option_flags = g_Task->option_flags;
        /* FAKE: retail leaves the task load's delay slot empty. */
        FAKE_BARRIER();
        *row                = *(SpawnedActor*)&g_Game.members[option_flags];
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
        actor->unk_25       = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        actor->unk_26       = 0x80;
        actor->active_flags |= 0x88;
        parent = g_Task;
        g_Task = actor;
        Actor_SelectScript(actor->direction);
        Area_AddGridActor();
        Actor_Clear();
        g_Task        = parent;
        parent->timer = 2;
    }
    g_Task->header.mode += 1;
}
#else
INCLUDE_ASM(func_801F2C48);
#endif
