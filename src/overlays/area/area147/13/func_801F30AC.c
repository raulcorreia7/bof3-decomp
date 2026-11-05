#include "area147_13.h"

MATCH void func_801F30AC(void) {
    u16 count;

    count = g_SpadWork->unk_30 - 0x10;
    g_SpadWork->unk_30 = count;
    if ((s16)count <= 0) {
        if (g_GameStateIndex == 0) {
            SND_PlayCue(0x201U);
        }
        g_SpadWork->state_02 = 1;
    }
    if ((s16)g_SpadWork->unk_32 != 0) {
        Area_Update(0);
    } else {
        Area_Update(-1);
    }
}
