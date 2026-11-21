#include "engine/game/00/game_00.h"

MATCH void Area_RunSetupStream(u8* cursor) {
    s16 index;
    s16 slot;

    g_ScratchPad.cells.halves[0] = 0;
    g_ScratchPad.cells.halves[1] = 0;
    do {
        g_PartyActors[(s16)g_ScratchPad.cells.halves[1]].header.flags = 0;
        index                                                         = (s16)g_ScratchPad.cells.halves[1] + 1;
        g_ScratchPad.cells.halves[1]                                  = index;
    } while (index < 4);
    Area_RunSetupRecords(cursor);
    if (g_ScratchPad.cells.halves[0] < ENTITY_MAX) {
        do {
            g_Actors[g_ScratchPad.cells.halves[0]].header.flags = 0;
            slot                                                = g_ScratchPad.cells.halves[0] + 1;
            g_ScratchPad.cells.halves[0]                        = slot;
        } while (slot < ENTITY_MAX);
    }
}
