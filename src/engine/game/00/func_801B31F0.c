#include "game_00.h"

typedef struct {
    u8  pad_00[0x7A];
    u8  kind;
    u8  pad_7B;
    u16 value;
    u8  pad_7E[0x18]; /* 0x7E-0x95 (frame-size evidence) */
} ScenarioRecord;

MATCH void func_801B31F0(void) {
    ScenarioRecord record;
    u8             kind;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        kind         = g_Game.current->u.field.kind_11E;
        record.kind  = kind;
        record.value = g_Game.current->u.field.value_120;
        if (kind != GAME_NONE) {
            Game_DispatchScenarioRecord(&record);
        }
        g_Task->header.step = 2;
    }
}
