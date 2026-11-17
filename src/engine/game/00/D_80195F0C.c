#include "game_00.h"

char D_80195F0C[4] = "%d";

FieldActionAltSteps g_FieldActionAltSteps = {
    FieldAction_RollAltStep,
    FieldAction_FindSmall,
    FieldAction_FindLarge,
    FieldAction_End,
    FieldAction_WaitMessage,
};
