#ifndef OVERLAY_AREA_ENCOUNTER_H
#define OVERLAY_AREA_ENCOUNTER_H

#include "types.h"

#endif

/* Declarations of the executable and game/00 sources: an overlay that calls these without a prototype compiles the call differently, so they are visible only after ENGINE_LOCAL_DECLS. */
#if defined(ENGINE_LOCAL_DECLS) && !defined(OVERLAY_AREA_ENCOUNTER_H_LOCAL)
#define OVERLAY_AREA_ENCOUNTER_H_LOCAL

/* func_801A0490 */
u8*  Area_FindEncounterZoneOf(s32 map_x, s32 map_y, s32 table_index);
/* func_801B3C3C */
u8*  Area_FindEncounterZone(s32 bounds_x, s32 bounds_y);
void Area_RollEncounterThreshold(u32 keep_armed);
s32  Area_CanStartEncounter(void);
/* func_801C63B0 */
bool Area_PlaceEncounterParty(void);
/* func_801C6A7C */
s32  Area_PickEncounter(void);
/* func_801C6AEC */
s32  Area_RollEncounterEnemies(s32 candidate_id);
/* func_801C6BB4 */
bool Area_PlaceEncounterEnemies(void);
s32  Area_BuildEncounter(u8 work_mode, s32 work_index);

#endif
