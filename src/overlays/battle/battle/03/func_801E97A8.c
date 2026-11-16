#include "battle_03.h"

MATCH void func_801E97A8(void) {
    BattlePanelTask* task;

    BATTLE_PANEL_TASK->ratio = (ENEMY_COMBATANT(BATTLE_PANEL_TASK->selection.slot).hp * 0x37 / ENEMY_COMBATANT(BATTLE_PANEL_TASK->selection.slot).stats.max_hp);
    if (ENEMY_COMBATANT(BATTLE_PANEL_TASK->selection.slot).hp != 0 && BATTLE_PANEL_TASK->ratio == 0) {
        BATTLE_PANEL_TASK->ratio = 1;
    }
    task         = BATTLE_PANEL_TASK;
    task->hp     = ENEMY_COMBATANT(task->selection.slot).hp;
    task->max_hp = ENEMY_COMBATANT(task->selection.slot).stats.max_hp;
    task->cursor = 0;
    BATTLE_PANEL_TASK->state += 1;
}
