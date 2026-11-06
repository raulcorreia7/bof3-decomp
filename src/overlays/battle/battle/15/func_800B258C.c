#include "battle_15.h"

MATCH void func_800B258C(void) {
    MenuPanelTask* task = g_MenuCurrentPanel;
    func_800B4220(task->pos.x, task->pos.y, ((u8*)task)[0xB]);
}
