#include "battle_03.h"

MATCH void func_801E97A8(void) {
    BattlePanelTask* task;

    BATTLE_PANEL_TASK->ratio = (u8)(ENEMY_COMBATANT(BATTLE_PANEL_TASK->cell_0A.slot).hp * 0x37 /
                                    ENEMY_COMBATANT(BATTLE_PANEL_TASK->cell_0A.slot).stats.max_hp);
    if (ENEMY_COMBATANT(BATTLE_PANEL_TASK->cell_0A.slot).hp != 0 && BATTLE_PANEL_TASK->ratio == 0) {
        BATTLE_PANEL_TASK->ratio = 1;
    }
    task         = BATTLE_PANEL_TASK;
    task->hp     = ENEMY_COMBATANT(task->cell_0A.slot).hp;
    task->max_hp = ENEMY_COMBATANT(task->cell_0A.slot).stats.max_hp;
    task->cursor = 0;
    BATTLE_PANEL_TASK->state += 1;
}
