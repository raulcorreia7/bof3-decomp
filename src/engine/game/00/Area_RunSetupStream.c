#include "game_00.h"

MATCH void Area_RunSetupStream(u8* cursor) {
    s16 index;
    s16 slot;

    D_1F800000.cells.halves[0] = 0;
    D_1F800000.cells.halves[1] = 0;
    do {
        D_80147A58[(s16)D_1F800000.cells.halves[1]].header.flags = 0;
        index                                                    = (s16)D_1F800000.cells.halves[1] + 1;
        D_1F800000.cells.halves[1]                               = index;
    } while (index < 4);
    Area_SetScenarioId(cursor);
    if (D_1F800000.cells.halves[0] < ENTITY_MAX) {
        do {
            g_Actors[D_1F800000.cells.halves[0]].header.flags = 0;
            slot                                              = D_1F800000.cells.halves[0] + 1;
            D_1F800000.cells.halves[0]                        = slot;
        } while (slot < ENTITY_MAX);
    }
}
