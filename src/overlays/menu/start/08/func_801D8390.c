#include "start_08.h"

extern u8 D_80148656;

typedef struct Start08PanelHead {
    s16 unk_00;
    u8  pad_02[0x10E];
    u8  unk_110;
} Start08PanelHead;

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 88.89%. resume: a lever or header
 * fix that closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D8390(void) {
    s16* panel;
    u8*  state;
    u8*  slot;
    s32  pad;
    u8   count;

    Menu_DrawClutStrip(D_80144953);
    panel                       = &D_801484CC;
    *panel                      = 0x17;
    *((u8*)panel + 0x110)       = 1;
    g_MenuPanelTasks[19].unk_0B = 1;
    g_MenuPanelTasks[21].active = 1;
    slot                        = (u8*)panel + 0xA4;
    D_801485E0                  = g_MenuPanelTasks[4].pos.x;
    D_801485E2                  = g_MenuPanelTasks[4].pos.y + g_MenuPanelTasks[16].unk_0A * 0x36;
    g_MenuPanelTasks[21].pos.x  = g_MenuPanelTasks[16].pos.x + 0x2A;
    g_MenuPanelTasks[21].pos.y  = g_MenuPanelTasks[16].pos.y + 7;
    pad                         = INPUT_GetRepeatedButtons(g_InputPressed & INPUT_DIRECTIONAL);
    g_MenuPanelTasks[16].flags  = 0xFF;
    count                       = Party_CountOrder(0);
    if (pad & PADLup) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        g_MenuPanelTasks[16].unk_0A -= 1;
        if ((s8)g_MenuPanelTasks[16].unk_0A < 0) {
            g_MenuPanelTasks[16].unk_0A = count - 1;
        }
    } else if (pad & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        g_MenuPanelTasks[16].unk_0A += 1;
        if ((s32)(count & BYTE_MASK) - 1 < (s32)(u8)g_MenuPanelTasks[16].unk_0A) {
            g_MenuPanelTasks[16].unk_0A = 0;
        }
    }
    if (pad & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        slot[9] = 0x32;
        slot[0xB] -= 1;
        if ((s8)slot[0xB] < 0) {
            slot[0xB] = 3;
        }
    } else if (pad & PADLright) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        slot[9] = 0x31;
        slot[0xB] += 1;
        if ((u8)slot[0xB] >= 4) {
            slot[0xB] = 0;
        }
    }
    D_80148656 = slot[0xA];
    if (g_InputPressed & D_80145AC2) {
        SND_PlayCue(EMI_CUE_ID(1, 3));
        state                       = &D_801485DC;
        *state                      = 0;
        g_MenuPanelTasks[18].unk_01 = 6;
        g_MenuPanelTasks[18].unk_02 = 0xF;
        state[-0x24]                = 1;
        g_MenuPanelTasks[18].pos.x  = 0x28;
        g_MenuPanelTasks[18].pos.y  = 0x3C;
        g_BattleItemRow             = (g_MenuPanelTasks[16].unk_0B == 3) ? 6 : 5;
        g_MenuPanelTasks[18].unk_0B = 0;
        D_80148652 += 1;
    } else if (g_InputPressed & D_80145AC4) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_801485DC = 0;
        D_80148651 -= 5;
    }
}
#else
INCLUDE_ASM(func_801D8390);
#endif
