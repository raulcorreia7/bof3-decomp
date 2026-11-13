#include "boss022_13.h"

MATCH void Boss_EndBattle(void) {
    func_800AC844(0);
    TASK_SET(func_800AC754(0));
    Area_SelectSceneRecord(0xAA);
    ((Actor*)g_Task)->unk_2A = 0;
    ((Actor*)g_Task)->unk_48 = 0;
    Actor_SelectScript(6);
}
