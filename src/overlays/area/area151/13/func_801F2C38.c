#include "area151_13.h"

MATCH void func_801F2C38(void) {
    s8* state;
    u8* src;
    u8* dst;
    s32 slot;
    s32 from;
    s32 index;
    s32 i;
    u32 id;
    u8  blank;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            if ((Area_GetCellCode(D_80145EC6, D_80145ECA) & BYTE_MASK) == 0xA1) {
                for (index = 0; index < 7; index++) {
                    if (g_GameContextSeed == D_801F5338[index][0]) {
                        break;
                    }
                }
                Message_StartAreaMessage((s16)D_801F5338[index][g_SceneState.scenario_id]);
            } else {
                blank = 0x5C;
                slot  = 0;
                from  = 0;
                dst   = (u8*)g_TextVariables;
                while (slot < 0xA0) {
                    id = D_801F5419[from];
                    if ((id & BYTE_MASK) == GAME_NONE) {
                        break;
                    }
                    if (g_FishingBestCatch[id & BYTE_MASK] != 0) {
                        if ((id & BYTE_MASK) == 0x16) {
                            src = D_801F5420;
                        } else {
                            src = Item_GetRecord(ITEM_CAT_ITEM, (id + 0x38) & BYTE_MASK);
                        }
                        for (i = 0; i < 12; i++) {
                            dst[i] = src[i];
                        }
                    } else {
                        for (i = 11; i >= 0; i--) {
                            dst[i] = blank;
                        }
                    }
                    D_801490E4[slot] = 0;
                    slot += 32;
                    from++;
                    dst += 0x20;
                }
                Message_StartAreaMessage(MSG_022);
            }
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            LOBU(g_SceneEventStep)++;
            break;

        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode      = SCENE_EVENT_NONE;
                *state                = 0;
                g_SceneEventSelection = 0;
            }
            break;
    }
}
