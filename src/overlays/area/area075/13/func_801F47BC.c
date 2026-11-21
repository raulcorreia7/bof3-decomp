#include "area075_13.h"

MATCH void func_801F47BC(void) {
    if ((D_801F58C6 & 0x8) != 0) {
        return;
    }
    if ((g_InputPressed & PADRdown) == 0) {
        return;
    }
    g_SpawnedActors[D_801F58CE[1]].scene_step -= 1;
    TASK_SET(&g_Game);
    g_Game.members[0].unk_4A = 1;
    Actor_StepAnimLoop();
    D_801F58C7 += 1;
}
