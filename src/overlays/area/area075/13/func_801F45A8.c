#include "area075_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F45A8(void) {
    Actor* actor;
    u16*   gauge;
    u16    timer;

    timer = D_801F58C4;
    if (D_801F58A0[D_801F58C9][timer % 15] != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
        gauge = &D_801F58CC;
        *gauge -= rand() % 2 + 4;
        g_SpawnedActors[D_801F58CE[0]].vx -= 1;
        actor = &g_Actors[D_801F58CE[2]];
        TASK_SET(actor);
        actor->unk_4A = 1;
        Script_AnimStepLoop();
    }
}
#else
INCLUDE_ASM(func_801F45A8);
#endif
