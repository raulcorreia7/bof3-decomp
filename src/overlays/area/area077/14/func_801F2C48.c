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
    ((Actor*)g_Task)->screen_x           = 0;
    ((Actor*)g_Task)->screen_y           = 2560;
    ((Actor*)g_Task)->unk_32             = 0;
    ((Actor*)g_Task)->tint.bytes.rgb.red = 0;
    ((Actor*)g_Task)->header.mode++;
    if (SYS_TestFlag(g_SceneFlags, 0x25) != 0) {
        SND_StopSequence(0, 0);
        SND_PlaySE(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
}
