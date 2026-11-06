#include "shared/etc.h"

extern u8  D_8014850E;
extern u8  D_80148510;
extern s16 D_801484CC;
extern u16 D_801484C0;
extern u16 D_801484C2;
/* This unit does not include start_08.h: it reads g_MenuPanelTasks[11].x and g_MenuPanelTasks[11].y
 * unsigned (lhu at 0x801D417C and 0x801D418C) while the header spells them
 * s16. The trio below repeats the header's declarations. */
extern s16 D_80148628;
extern u16 D_8014862A;
extern u8* D_801C893C[];
extern u8* D_801C8950[];

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 75.37%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D40D8(void) {
    u8*  flag;
    s8*  label;
    u16* pad;
    u8** records;

    Menu_DrawClutStrip(D_80144953);
    flag = &D_80148624;
    TEXT_SetVariable(0, 0xC,
                     Item_GetRecord(g_MenuPanelTasks[13].unk_0A, D_801C893C[D_8014850E][g_MenuPanelTasks[13].unk_0C]));
    g_MenuPanelTasks[11].unk_10 = 0x1A;
    label                       = &D_8014865B;
    *flag                       = 1;
    g_MenuPanelTasks[21].pos.x  = g_MenuPanelTasks[11].pos.x + ((1 - *label) << 5) + 0xDE;
    g_MenuPanelTasks[21].pos.y  = g_MenuPanelTasks[11].pos.y + 5;
    pad                         = &g_InputPressed;
    records                     = D_801C893C;
    if (*pad & (PADLright | PADLleft)) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        *label ^= 1;
    }
    if (D_80145AC2 & *pad) {
        if (*label != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            records[g_MenuPanelTasks[13].unk_0A][g_MenuPanelTasks[13].unk_0C]    = 0;
            D_801C8950[g_MenuPanelTasks[13].unk_0A][g_MenuPanelTasks[13].unk_0C] = 0;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 6));
        }
        D_80148651 -= 3;
        /* FAKE: retail reaches the neighbouring flag through the record base. */
        *(s8*)((u8*)flag - 0x113) = -1;
        return;
    }
    if (D_80145AC4 & *pad) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        *(s8*)((u8*)flag - 0x113) = -1;
        D_80148651 -= 3;
    }
}
#else
INCLUDE_ASM(func_801D40D8);
#endif
