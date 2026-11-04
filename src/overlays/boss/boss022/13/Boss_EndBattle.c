#include "boss022_13.h"

MATCH void Boss_EndBattle(void) {
    func_800AC844(0);
    g_SpadWork = (u8*)func_800AC754(0);
    Area_FindSceneRecord(0xAA);
    ((Actor*)g_SpadWork)->unk_2A = 0;
    ((Actor*)g_SpadWork)->unk_48 = 0;
    Actor_SelectScript(6);
}
