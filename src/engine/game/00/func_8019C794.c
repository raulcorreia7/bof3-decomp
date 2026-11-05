#include "game_00.h"

MATCH void func_8019C794(void) {
    Actor*         work;
    AreaMapBundle* map;
    u8             code;
    u8             index;

    work = g_SpadWork;
    work->x.fixed += work->vx;
    work->unk_0A -= 1;
    work->y.fixed += work->vy;
    if (g_SpadWork->unk_0A == 0 ||
        (map = (AreaMapBundle*)MAP_BUNDLE_BASE,
         *(u16*)(g_SpadWork->x.part.integer * 2 +
                 (g_SpadWork->y.part.integer * map->width_00 * 2 + map->grid_off4_02 * 4) + (u32)map) == 0)) {
        code = 0x4E;
        /* Both reports share one call block. */
        goto report;
    }
    if (func_8019CAB4() != 0) {
        code = 0x4F;
    report:
        Actor_SelectScript(code);
        g_SpadWork->unk_01 += 1;
    } else if ((g_SpadWork->unk_0A & 1) == 0) {
        index = Actor_FindFreeSlot();
        if (index != GAME_NONE) {
            g_ActorSlots[index].flags_00 = 1;
            g_ActorSlots[index].type     = 0x1B;
            g_ActorSlots[index].unk_01   = 3;
        }
    }
    func_8014D978();
    Area_SetDrawMode();
}
