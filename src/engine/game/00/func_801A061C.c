#include "game_00.h"

MATCH void func_801A061C(void) {
    u32    index;
    Actor* entity;
    u32    type;

    index = 0;

    do {
        entity = (Actor*)((u8*)g_Actors + ((index & BYTE_MASK) * ACTOR_SIZE));
        TASK_SET(entity);
        type = entity->unk_06;

        if (type >= 8 || type == 7) {
            if (ACTOR_IN_USE(*entity)) {
                if (type == 10) {
                    index += 1;
                    Actor_ProjectForDraw();
                    continue;
                }
                if (type != 9) {
                    Area_SetDrawMode();
                }
            }
        }
        index += 1;
    } while ((index & BYTE_MASK) < ENTITY_MAX);
}
