#include "boss055_16.h"

MATCH void func_800C2D2C(void) {
    Boss055Scripts scripts;

    scripts = D_800C1834;
    Area_SelectSceneRecord(0x318);
    g_Task->unk_48      = 0;
    g_Task->unk_24      = 0;
    g_Task->pos.z.fixed = 0;
    Actor_SelectScript(scripts.byte[g_Battle.unk_DE]);
    Battle_IsEnemyBlockedOnce();
    Area_AddActor();
    Boss_CopyEffectTransform();
    g_Task->header.step++;
}
