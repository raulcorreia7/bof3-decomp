#include "game_00.h"

typedef struct {
    u8  pad_00[0x7A];
    u8  unk_7A;
    u8  pad_7B;
    u16 unk_7C;
    u8  pad_7E[0x18]; /* 0x7E-0x95 (frame-size evidence) */
} GameRecord;

MATCH void func_801B31F0(void) {
    GameRecord record;
    u8         kind;

    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        kind          = g_GameState->kind_11E;
        record.unk_7A = kind;
        record.unk_7C = g_GameState->value_120;
        if (kind != GAME_NONE) {
            Game_DispatchScenarioRecord(&record);
        }
        SCRATCH_WORK->header.step = 2;
    }
}
