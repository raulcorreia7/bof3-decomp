#include "area015_13.h"

MATCH void func_801F2C04(void) {
    if (D_80146871 & 0x1) {
        g_EncounterZones[g_GameAreaId][0xC]  = 2;
        g_EncounterZones[g_GameAreaId][0x14] = 2;
    } else {
        g_EncounterZones[g_GameAreaId][0xC]  = 0;
        g_EncounterZones[g_GameAreaId][0x14] = 0;
    }
}
