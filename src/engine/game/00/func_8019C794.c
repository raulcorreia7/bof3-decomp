#include "game_00.h"

MATCH void func_8019C794(void) {
    Actor*         work;
    AreaMapBundle* map;
    u8             code;
    u8             index;

    work = SELF(Actor);
    work->pos.x.fixed += work->vx;
    work->unk_0A -= 1;
    work->pos.y.fixed += work->vy;
    if (SELF(Actor)->unk_0A == 0 ||
        (map = (AreaMapBundle*)MAP_BUNDLE_BASE, *(u16*)(COORD_INT(SELF(Actor)->pos.x) * 2 + (COORD_INT(SELF(Actor)->pos.y) * map->width * 2 + map->grid_offset * 4) + (u32)map) == 0)) {
        code = 0x4E;
        /* Both reports share one call block. */
        goto report;
    }
    if (func_8019CAB4() != 0) {
        code = 0x4F;
    report:
        Script_Select(code);
        SELF(Actor)->header.mode += 1;
    } else if ((SELF(Actor)->unk_0A & 0x1) == 0) {
        index = Actor_FindFreeSpawned();
        if (index != GAME_NONE) {
            g_SpawnedActors[index].header.flags = 1;
            g_SpawnedActors[index].type         = 0x1B;
            g_SpawnedActors[index].header.mode  = 3;
        }
    }
    Script_AnimStepLoop();
    Area_SetDrawMode();
}
