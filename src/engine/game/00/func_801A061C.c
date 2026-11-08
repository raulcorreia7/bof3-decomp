#include "game_00.h"

MATCH void func_801A061C(void) {
    u32    index;
    Actor* entity;
    u32    kind;

    index = 0;

    do {
        entity = (Actor*)((u8*)g_Actors + ((index & BYTE_MASK) * ACTOR_SIZE));
        g_Task = entity;
        kind   = entity->unk_06;

        if (kind >= 8 || kind == 7) {
            if (ACTOR_IN_USE(*entity)) {
                if (kind == 10) {
                    index += 1;
                    func_8015A944();
                    continue;
                }
                if (kind != 9) {
                    Area_SetDrawMode();
                }
            }
        }
        index += 1;
    } while ((index & BYTE_MASK) < ENTITY_MAX);
}
