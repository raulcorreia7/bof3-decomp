#include "area098_13.h"

/* Spawns the capture probe actor from the party member the task points at. */
MATCH void func_801F2C48(void) {
    u8            slot;
    u8            option_flags;
    SpawnedActor* spawned_actor;
    Actor*        actor;
    Actor*        parent;
    SpawnedActor* src;

    slot = Actor_FindFreeSpawned();
    if (slot != GAME_NONE) {
        D_801F6520    = g_Game.members[SELF(Actor)->option_flags].character_index != 0;
        spawned_actor = &g_SpawnedActors[slot];
        GFX_ClearRect(0x340, 0x100, 0x80, 0x100);
        option_flags        = SELF(Actor)->option_flags;
        src                 = (SpawnedActor*)&g_Game.members[option_flags];
        *spawned_actor      = *src;
        actor               = (Actor*)spawned_actor;
        actor->header.flags = 1;
        actor->header.mode  = 2;
        actor->header.step  = 0;
        actor->unk_05       = ACTOR_TYPE_FACING_PROBE;
        actor->pos.x.fixed  = g_Game.members[SELF(Actor)->option_flags].pos.x.fixed;
        actor->pos.y.fixed  = g_Game.members[SELF(Actor)->option_flags].pos.y.fixed;
        actor->pos.z.fixed  = g_Game.members[SELF(Actor)->option_flags].pos.z.fixed;
        actor->screen_x     = D_801F5F58[D_801F6520].x;
        actor->screen_y     = D_801F5F58[D_801F6520].y;
        actor->sheet_page   = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, 0x340, 0x100);
        actor->sheet_row    = 0x80;
        actor->active_flags |= 0x88;
        parent = SELF(Actor);
        g_Self = actor;
        Script_Select(actor->direction);
        Area_AddGridActor();
        Actor_Clear();
        g_Self        = parent;
        parent->timer = 2;
    }
    SELF(Actor)->header.mode += 1;
}
