#include "area189_13.h"

#ifdef NON_MATCHING
NON_MATCHING u8 func_801F5D6C(void) {
    u8 index;

    if ((g_PadStates[0].pressed & PADstart) != 0) {
        index             = (D_8014933C < 1) ? 3 : 0;
        g_GameEntryAreaId = D_801F6388[index];
        g_GameEntryPosX   = D_801F6389[index] << 16;
        g_GameEntryPosY   = D_801F638A[index] << 16;
        D_80145048        = g_GameAreaId;
        g_GameEntryFacing = 4;
        D_80145040        = SELF(Actor)->pos.x.fixed;
        D_80145044        = SELF(Actor)->pos.y.fixed;
        D_8014504A += 1;
        D_8014504B = (SELF(Actor)->direction + D_801F62F0[rand() & 3]) & 0xF;
        Game_RequestAreaChange(g_GameEntryAreaId, g_GameEntryPosX, g_GameEntryPosY, g_GameEntryFacing);
        return 1;
    }
    return 0;
}
#else
INCLUDE_ASM(func_801F5D6C);
#endif
