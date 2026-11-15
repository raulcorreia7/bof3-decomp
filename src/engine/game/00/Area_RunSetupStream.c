#include "game_00.h"

MATCH void Area_RunSetupStream(u8* cursor) {
    s16 index;
    s16 slot;

    D_1F800000.view.area.entity_counter = 0;
    D_1F800000.view.area.entry_data     = 0;
    do {
        D_80147A58[(s16)D_1F800000.view.area.entry_data].header.flags = 0;
        index                                                         = (s16)D_1F800000.view.area.entry_data + 1;
        D_1F800000.view.area.entry_data                               = index;
    } while (index < 4);
    Area_SetScenarioId(cursor);
    if (D_1F800000.view.area.entity_counter < ENTITY_MAX) {
        do {
            g_Actors[D_1F800000.view.area.entity_counter].header.flags = 0;
            slot                                                       = D_1F800000.view.area.entity_counter + 1;
            D_1F800000.view.area.entity_counter                        = slot;
        } while (slot < ENTITY_MAX);
    }
}
