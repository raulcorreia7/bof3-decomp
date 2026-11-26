#include "engine/game/00/game_00.h"
#include "menu/save_data.h"

/* FAKE: the step increment stays on the mode symbol; both spellings name the same byte. */
/* func_801A852C */
/* Shows the entry message, then requests the Fairy Village area picked by the highest set flag of 246 to 255. */
MATCH void WorldMap_RunFairyEntry(void) {
    s8* state;
    s32 bit_index;
    s32 seed;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            MESSAGE_START_WAIT((Item_Count(ITEM_CATEGORY_ITEM, ITEM_FAERIE_TIARA, 0) & HALF_MASK) ? 0x21 : 0x20);
            (&g_SceneEventMode)[1] += 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                *state                 = 0;
            }
            break;
        case 2:
            if (g_GameStateIndex != *state) {
                bit_index = GAME_NONE;
                seed      = 0xB9;
                state += 0x63C;
                for (;;) {
                    if (SYS_TestFlag(state, bit_index) != 0) {
                        break;
                    }
                    bit_index--;
                    seed--;
                    if (bit_index < 246) {
                        break;
                    }
                }
                g_SaveData.return_point.x       = g_Game.members[0].pos.x.fixed;
                g_SaveData.return_point.y       = g_Game.members[0].pos.y.fixed;
                g_SaveData.return_point.area_id = g_GameAreaId;
                Game_RequestAreaChange(seed & HALF_MASK, TO_COORD(67), TO_COORD(22), FACING_DOWN_RIGHT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                Game_ClearScriptActive();
                g_SceneEventState.mode = SCENE_EVENT_NONE;
                g_SceneEventState.step = 0;
            }
            break;
    }
}
