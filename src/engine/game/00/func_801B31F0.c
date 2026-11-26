#include "game_00.h"

typedef struct {
    u8  pad_00[0x7A];
    u8  type;
    u8  pad_7B;
    u16 value;
    u8  pad_7E[0x18]; /* 0x7E-0x95 (frame-size evidence) */
} ScenarioRecord;

MATCH void func_801B31F0(void) {
    ScenarioRecord record;
    u8             type;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        type         = g_Game.current->u.field.type;
        record.type  = type;
        record.value = g_Game.current->u.field.value;
        if (type != GAME_NONE) {
            Game_ScenarioDispatchRecord(&record);
        }
        SELF(Actor)->header.step = 2;
    }
}
