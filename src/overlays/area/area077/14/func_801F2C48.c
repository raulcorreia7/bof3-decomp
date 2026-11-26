#include "area077_14.h"

MATCH void func_801F2C48(void) {
    Pos2* points;
    u8    i;

    i      = 0;
    points = MEM_PTR(Pos2, AREA_WORK);
    do {
        points[i].vx                        = 0;
        /* The Y column is its own address in the original; the two halves load apart. */
        MEM(s16, AREA_WORK + 2u + (i << 2)) = 0;
        i++;
    } while (i < 32);

    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    SELF(Actor)->screen_x         = 0;
    SELF(Actor)->screen_y         = 2560;
    SELF(Actor)->unk_32           = 0;
    SELF(Actor)->tint.bytes.rgb.r = 0;
    SELF(Actor)->header.mode++;
    if (SYS_TestFlag(g_SceneFlags, 0x25) != 0) {
        SND_SeqStop(0, 0);
        SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 3));
    }
}
