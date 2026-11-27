#include "area075_13.h"

MATCH void func_801F46D4(void) {
    u16* timer;
    u8*  counter;

    if (g_PadStates[0].pressed & PADRdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 2));
        timer = &D_801F58CA;
        *timer -= rand() % 2 + 4;
        g_SpawnedActors[D_801F58CE[1]].vx -= 1;
        SELF_SET(&g_Game);
        g_Game.members[0].unk_4A = 1;
        Script_AnimStepLoop();
        D_801F58C8 = 0;
    } else {
        counter = &D_801F58C8;
        *counter += 1;
    }
}
