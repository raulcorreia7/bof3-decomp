#include "shared/etc.h"

extern u8  D_801484BD;
extern u8  D_801484BE;
extern u8  D_801484BF;
extern s16 D_801484C0;
extern s16 D_801484C2;
extern s16 D_801484CC;
extern u8  D_801485B9;
extern u8  D_801485BA;
extern s16 D_801485BC;
extern s16 D_801485BE;
extern u8  D_80148654;
extern u8  D_801ED68C;

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 92.47%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D9748(void) {
    volatile u8*   record;
    MenuPanelTask* rows;
    u8             i;

    record                       = &D_801484BC;
    i                            = 0;
    rows                         = (MenuPanelTask*)(record + 0x120);
    g_MenuPanelTasks[11].handler = 6;
    g_MenuPanelTasks[11].mode    = 9;
    g_MenuPanelTasks[11].state   = 2;
    record[0]                    = 1;
    g_MenuPanelTasks[11].pos.x   = 0x14;
    g_MenuPanelTasks[11].pos.y   = -0x14;
    g_MenuPanelTasks[11].unk_10  = 0;
    while (i < 2) {
        rows[i].unk_00[1] = 6;
        rows[i].unk_00[2] = 0xA;
        rows[i].unk_00[0] = 0;
        rows[i].unk_0A    = 0;
        i++;
    }
    g_MenuPanelTasks[18].mode    = 0xD;
    g_BattlePanelMode            = 2;
    D_801485B8                   = 1;
    g_BattleItemRow              = 7;
    g_MenuPanelTasks[18].unk_0B  = 0xFF;
    g_MenuPanelTasks[18].pos.x   = 0x70;
    g_MenuPanelTasks[18].pos.y   = -0x14;
    g_MenuPanelTasks[18].handler = 6;
    g_MenuPanelTasks[21].handler = 6;
    g_MenuPanelTasks[21].mode    = 0xE;
    g_MenuPanelTasks[21].active  = 0;
    Menu_DrawClutStrip(D_80144953);
    D_801ED68C = 0;
    SND_PlayCue(EMI_CUE_ID(1, 2));
    D_80148654 = 5;
    D_80148652 = 0;
    D_80148651 += 1;
}
#else
INCLUDE_ASM(func_801D9748);
#endif
