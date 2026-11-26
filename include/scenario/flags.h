#ifndef SCENARIO_FLAGS_H
#define SCENARIO_FLAGS_H

#include "types.h"

#define SCENARIO_COUNT       20 /* SCENA00 to SCENA19 */
#define SCENE_FLAG_ROW_BYTES 8  /* 64 flag bits per scenario, tested with SYS_TestFlag */

/* The scenario that owns a row of g_SceneFlagRows. Only the scenarios the code names are listed. */
typedef enum ScenarioId {
    SCENARIO_NEW_GAME        = 0,  /* Menu_StartNewGame starts it */
    SCENARIO_DESERT_OF_DEATH = 14, /* SCENA14 runs the Oasis, desert camp, Desert of Death and Eden areas; the desert crossing flags live in its row */
    SCENARIO_TITLE           = 16, /* the title scene; the chapter counter skips it */
} ScenarioId;

/* Bits of the SCENARIO_DESERT_OF_DEATH row that one meaning covers; the other bits stay numbers. */
typedef enum DesertFlag {
    DESERT_FLAG_INTRO = 1, /* set while the crossing's opening scene runs (scena15 steps 1 to 7); the Desert of Death map marks the leader while it is set */
} DesertFlag;

#endif
