#include "area075_13.h"

/* On a hit in the D_801F58A0 timing row: plays the sound, lowers the opponent gauge by 4 or 5 and steps its two actors. */
MATCH void func_801F45A8(void) {
    Actor* actor;

    if (D_801F58A0[D_801F58C9][D_801F58C4 % 15] != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
        g_Area075OpponentGauge[0] = D_801F58CC - (rand() % 2 + 4);
        g_SpawnedActors[D_801F58CE[0]].vx -= 1;
        actor = &g_Actors[D_801F58CE[2]];
        SELF_SET(actor);
        actor->unk_4A = 1;
        Script_AnimStepLoop();
    }
}
