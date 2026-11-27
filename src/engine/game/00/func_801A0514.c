#include "game_00.h"

MATCH void func_801A0514(void) {
    s32    index;
    s32    slot_u8;
    Actor* entity;
    u32    next_u8;

    index = 0;

    do {
        slot_u8 = index & BYTE_MASK;

        entity = (Actor*)((u8*)g_Actors + (slot_u8 * ACTOR_SIZE));

        SELF_SET(entity);

        if (ACTOR_IN_USE(*entity)) {
            if (entity->unk_06 != 9) {
                if (entity->active_flags & 0x10) {
                    entity->draw_layer = 4;
                } else {
                    entity->draw_layer = g_AreaDrawMode;
                }

                goto block_7; /* the slot's state byte is already set */
            }

            if (g_AreaDrawMode != GFX_LAYER_BATTLE_SCENE) {
            block_7:
                {
                    Actor* scratch;
                    s32    type;
                    scratch = SELF(Actor);
                    type    = scratch->unk_06;
                    if (type == 10) {
                        index += 1;
                        Actor_ProjectForDraw();
                        next_u8 = index & BYTE_MASK;
                    } else {
                        Area_AddGridActor();
                        goto block_10; /* the type is not 10, step the slot */
                    }
                }
            } else {
                goto block_10; /* the slot is not active, step it */
            }
        } else {
        block_10:
            index += 1;
            next_u8 = index & BYTE_MASK;
        }
    } while (next_u8 < ENTITY_MAX);
}
