#include "start_08.h"

extern s8 D_80148656;

#ifdef NON_MATCHING
NON_MATCHING void func_801D8680(void) {
    s16* val0;
    s32  tmp0;
    s32  val1;
    u8   tmp1;
    u8   tmp2;
    u8   tmp3;

    Menu_DrawClutStrip(D_80144953);
    *(s16*)(&D_801484CC)                             = 0x18;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    val0                                             = &D_801484CC + 0xEC;
    g_MenuPanelTasks[18].unk_0C                      = 0xFF;
    g_MenuPanelTasks[16].unk_0C                      = 0xFF;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = g_MenuPanelTasks[18].pos.x + 5;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y  = g_MenuPanelTasks[18].pos.y + ((g_MenuPanelTasks[18].unk_0B * 0x10) + 0x1A);
    tmp0                                             = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    val1                                             = g_MenuPanelTasks[16].unk_0B == 3;
    if (tmp0 & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        tmp3                        = g_MenuPanelTasks[18].unk_0B - 1;
        g_MenuPanelTasks[18].unk_0B = tmp3;
        if (tmp3 & 0x80) {
            g_MenuPanelTasks[18].unk_0B = *(&D_801EC4A4 + ((val1 & BYTE_MASK) * 6)) - 1;
        }
    } else if (tmp0 & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        tmp2                        = g_MenuPanelTasks[18].unk_0B + 1;
        g_MenuPanelTasks[18].unk_0B = tmp2;
        if ((*(&D_801EC4A4 + ((val1 & BYTE_MASK) * 6)) - 1) < (tmp2 & BYTE_MASK)) {
            g_MenuPanelTasks[18].unk_0B = 0;
        }
    }
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        tmp1 = FIELD(u8, (((val1 & BYTE_MASK) * 6) + &D_801EC4A4 + FIELD(u8, (val0), 0xB)), 0x1u);
        if (tmp1 != 0) {
            func_801D9304((s32)tmp1);
            return;
        }
        g_MenuPanelTasks[16].flags = 0xFF;
        g_MenuStep.state += 1;
        g_MenuPanelTasks[16].unk_0C = s_SkillOrderCursors[D_80148656][g_MenuPanelTasks[16].unk_0B];
        return;
    }
    if (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        FIELD(s8, (&D_801484CC), 0xECu) = 0;
        g_MenuStep.state -= 1;
    }
}
#else
INCLUDE_ASM(func_801D8680);
#endif
