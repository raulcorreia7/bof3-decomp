#ifndef OVERLAY_WORLD03_AREA151_13_H
#define OVERLAY_WORLD03_AREA151_13_H

/* The world03/area151/13 overlay: one file per split function
 * and its data. Only this image includes the file. */

#include "overlays/area/worlds/world03.h"

#define D_801F4D05            (D_801F4D04 + 1u)
#define D_801F5468            (D_801F4D04 + 0x764u)
#define AREA_HUD_SPRITE_CELLS D_801F5468

/* The scratchpad work pointer; the dispatch entry bytes select a handler. */

/* The world-area state byte tested by the work handlers. */
/* The world-map entry keys WORLD_MAP_SELECT_KEY_SCRIPT scans. */
extern WorldMapKey D_801F4CE8[7];
extern u8          D_801F4D04[];

/* Seed rows matched against g_GameEntryAreaId; column 0 is the seed, the
 * g_ScenarioState.scenario_id column is the message id. */
extern u16      D_801F5338[7][16];
/* The fish ids the pond keeper shows, ended by GAME_NONE, and the "Manillo"
 * item text at +0x7. */
extern u8       D_801F5419[];
extern u8       D_801F5420[];
/* The request selector and the area request slot. */
extern Callback D_801F542C[];
/* The state handler tables the dispatchers index. */
extern Callback D_801F5440[];
extern Callback D_801F5448[];
extern Callback D_801F5458[];
extern Callback D_801F54D8[];
/* D_801F54E4 */
/* D_801F54F4 */
extern Callback D_801F54FC[];

/* The work-mode steps the request wrapper runs. */

void func_801F3438(void);
/* The origin pan step the handler enters. */
/* func_801F3528 */
void Area_Update(void);
/* The origin pan step the handler enters. */
/* func_801F3A70 */
/* The value of area update step in the shared Area_Update body. */

extern WorldMapMarker D_801F54C0[6];
#define AREA_HUD_MASK_TABLE D_801F54C0

#include "overlays/area/shared/world_cloud.h"

#endif
