#include "game_00.h"

typedef struct GameWork {
    u8  unk_00[3];
    u8  state;
    s16 x;
    s16 unk_06;
    u8  unk_08[5];
    u8  unk_0D;
    u8  unk_0E[0x12];
    s32 unk_20;
} GameWork;

MATCH void func_8019977C(void) {
    GameWork* task;

    g_MenuActionHandlers[((GameWork*)g_MenuCurrentPanel)->state]();
    task = (GameWork*)g_MenuCurrentPanel;
    func_801D5634(7, task->x, task->unk_06, task->unk_20, task->unk_0D, task);
}
