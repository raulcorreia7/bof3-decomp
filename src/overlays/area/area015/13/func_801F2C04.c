#include "area015_13.h"

MATCH void func_801F2C04(void) {
    if (D_80146871 & 0x1) {
        g_EncounterZones[g_GameAreaId][1].rate = 2;
        g_EncounterZones[g_GameAreaId][2].rate = 2;
    } else {
        g_EncounterZones[g_GameAreaId][1].rate = 0;
        g_EncounterZones[g_GameAreaId][2].rate = 0;
    }
}
