#include "start_08.h"

#ifdef NON_MATCHING
/* Update of the start menu's skill-order list: the party slot and the ability
 * group cursors, the description of the selected skill, and the confirm that
 * picks it. */
NON_MATCHING void func_801D759C(void) {
    MenuPanelTask* task;
    u8*            window;
    s8*            chosen;
    s32            input;
    s32            count;
    s8             slot;
    s8             previous;
    s32            limit;

    Menu_DrawClutStrip(g_WindowClut);
    window = &g_UiPanelTasks[16].unk_08;
    if (D_801ED648 == 0) {
        window[0] = 1;
    } else {
        window[0] = 3;
    }
    g_UiPanelTasks[21].active = 0;
    if (g_BattleMessageState == 0) {
        window[0x64]              = 1;
        g_UiPanelTasks[19].unk_0B = 1;
        D_801485E0                = g_UiPanelTasks[4].pos.x;
        D_801485E2                = g_UiPanelTasks[4].pos.y + g_UiPanelTasks[16].unk_0A * 0x36;
    } else {
        window[0x64] = 0;
    }
    UI_MessageSetVariable(0, 5, (u8*)&g_Characters[g_CharSlot[g_PartyFieldOrder[g_UiPanelTasks[16].unk_0A]]]);
    D_801484CC                = 0x2F;
    input                     = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & INPUT_DIRECTIONAL);
    g_UiPanelTasks[16].unk_0C = 0xFF;
    g_UiPanelTasks[16].flags  = 0xFF;
    task                      = &g_UiPanelTasks[16];
    /* FAKE: retail keeps the whole return word; the u8 prototype extends it. */
    count                     = ((s32 (*)(s32))Party_CountOrder)(PARTY_ORDER_FIELD);
    previous                  = g_UiPanelTasks[16].unk_0A;
    if ((input & PADLup) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        slot                      = g_UiPanelTasks[16].unk_0A - 1;
        g_UiPanelTasks[16].unk_0A = slot;
        if (slot < 0) {
            g_UiPanelTasks[16].unk_0A = count - 1;
        }
    } else if ((input & PADLdown) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        limit = (u8)count;
        limit--;
        slot                      = g_UiPanelTasks[16].unk_0A + 1;
        g_UiPanelTasks[16].unk_0A = slot;
        if (limit < (u8)slot) {
            g_UiPanelTasks[16].unk_0A = 0;
        }
    }
    if (D_801ED648 != 2) {
        task->u.addr.unk_10 = 0;
        if ((input & PADLleft) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            task->unk_09 = 0x32;
            if ((s8)--task->unk_0B < 0) {
                task->unk_0B = 3;
            }
        } else if ((input & PADLright) != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            task->unk_09 = 0x31;
            if (++task->unk_0B >= 4) {
                task->unk_0B = 0;
            }
        }
    } else {
        task->u.addr.unk_10 = 1;
    }
    if (task->unk_0A != previous) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    chosen  = &g_PartyCursor;
    *chosen = task->unk_0A;
    if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
        g_UiPanelTasks[16].unk_0C = s_SkillOrderCursors[*chosen][g_UiPanelTasks[16].unk_0B];
        D_80148651++;
    } else if ((g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_801485DC = 0;
        D_80148651--;
    }
}
#else
INCLUDE_ASM(func_801D759C);
#endif
