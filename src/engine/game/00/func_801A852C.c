#include "game_00.h"

MATCH void func_801A852C(void) {
    s8* state;
    s32 bit_index;
    s32 seed;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            Message_StartAreaMessage((Item_Count(ITEM_CAT_ITEM, ITEM_FAERIE_TIARA, 0) & HALF_MASK) ? 0x21 : 0x20);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            (&g_SceneEventMode)[1] += 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                *state           = 0;
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
                D_80145040 = g_Game.members[0].pos.x.fixed;
                D_80145044 = g_Game.members[0].pos.y.fixed;
                D_80145048 = g_GameAreaId;
                Game_RequestAreaChange(seed & HALF_MASK, TO_COORD(67), TO_COORD(22), FACING_DOWN_RIGHT);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                Game_ClearScriptActive();
                g_SceneEventMode = SCENE_EVENT_NONE;
                g_SceneEventStep = 0;
            }
            break;
    }
}
