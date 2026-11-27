#include "engine/slus/slus.h"

#define SCRIPT_VALUE_SCENE_RECORD     0
#define SCRIPT_VALUE_AREA_ID          1
#define SCRIPT_VALUE_SCENE_FLAGS      2
#define SCRIPT_VALUE_VAR_0            3
#define SCRIPT_VALUE_VAR_1            4
#define SCRIPT_VALUE_VAR_2            5
#define SCRIPT_VALUE_VAR_3            6
#define SCRIPT_VALUE_SCENARIO_STATE   7
#define SCRIPT_VALUE_CELL_TYPE        8
#define SCRIPT_VALUE_SCENARIO_FLAG    9
#define SCRIPT_VALUE_SCRIPT_PC        10
#define SCRIPT_VALUE_LEADER_ID        11
#define SCRIPT_VALUE_EVENT_FLAGS      12
#define SCRIPT_VALUE_ALWAYS_ONE       13
#define SCRIPT_VALUE_SCENE_RECORD_ALT 14

/* returns the game-state word that `type` selects: the scenario state for types 0 and 14, then route,
 * map-record, flag and counter globals in type order, the staged scratchpad word at 0x58 for type 10, overlay words
 * for 11-13 and 0xFF otherwise.
 */
/* func_8015B870 */
/* Returns the state value a script condition selects by type. */
MATCH s32 Script_ReadValue(u32 type) {
    switch (type & BYTE_MASK) {
        case SCRIPT_VALUE_SCENE_RECORD:
        case SCRIPT_VALUE_SCENE_RECORD_ALT:
            return g_SceneRecord.sbyte;
        case SCRIPT_VALUE_AREA_ID:
            return g_GameAreaId;
        case SCRIPT_VALUE_SCENE_FLAGS:
            return *g_SceneFlags;
        case SCRIPT_VALUE_VAR_0:
            return g_ScriptVars[0];
        case SCRIPT_VALUE_VAR_1:
            return g_ScriptVars[1];
        case SCRIPT_VALUE_VAR_2:
            return g_ScriptVars[2];
        case SCRIPT_VALUE_VAR_3:
            return g_ScriptVars[3];
        case SCRIPT_VALUE_SCENARIO_STATE:
            /* FAKE: retail reads g_ScenarioState.state_04 as RecordKey. */
            return (*(RecordKey*)&g_ScenarioState.state_04).sbyte;
        case SCRIPT_VALUE_CELL_TYPE:
            return g_GameCellType;
        case SCRIPT_VALUE_SCENARIO_FLAG:
            return g_ScenarioState.flags_01 & 0x1;
        case SCRIPT_VALUE_SCRIPT_PC:
            return SELF(Actor)->script_pc;
        case SCRIPT_VALUE_LEADER_ID:
            return g_Game.members[0].chr.character_id;
        case SCRIPT_VALUE_EVENT_FLAGS:
            /* FAKE: retail reads g_SceneEventFlags as u32. */
            return (*(u32*)g_SceneEventFlags);
        case SCRIPT_VALUE_ALWAYS_ONE:
            return 1;
        default:
            return 0xFF;
    }
}
