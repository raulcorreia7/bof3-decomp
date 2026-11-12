#include "engine/slus/slus.h"

/* The shared MenuPanelTask view stops at 0x08; the draw fields at 0x0D, 0x10
 * and 0x12 are recovered from the accesses. */
typedef struct MenuPanelDrawTask {
    u8  unk_00[3];
    u8  state;
    u16 x;
    u16 unk_06;
    u8  unk_08[5];
    u8  unk_0D;
    u8  unk_0E[2];
    u16 unk_10;
    u16 unk_12;
} MenuPanelDrawTask;

MATCH void func_80159510(void) {
    MenuPanelDrawTask* task;
    task = (MenuPanelDrawTask*)g_MenuCurrentPanel;
    if (!(task->unk_0D & 0x1)) {
        func_80159B9C((s16)task->x >> 4, (s16)task->unk_06 >> 4, (u8)(task->unk_10 >> 4), (u8)(task->unk_12 >> 4));
    }
    UI_UpdateLayout();
}
