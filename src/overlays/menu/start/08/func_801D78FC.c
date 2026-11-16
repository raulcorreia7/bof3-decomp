#include "start_08.h"

#ifdef NON_MATCHING
extern s8 D_80148656;

NON_MATCHING void func_801D78FC(void) {
    SkillOrder*    skill_order;
    MenuPanelTask* task;
    u8*            abilities;
    volatile u8*   panel_active;
    u16            buttons;
    u8             ability;
    u8             old_cursor;
    u8             i;
    s8             result;

    Menu_DrawClutStrip(D_80144953);
    panel_active = &D_801485DC;
    if (g_BattleMessageState == 0) {
        *panel_active                                          = 1;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 0;
        D_801485E0                                             = *(volatile u16*)((volatile u8*)&g_BattleMessageState + 1);
        D_801485E2                                             = *(volatile u16*)((volatile u8*)&g_BattleMessageState + 3) + D_8014857A * 54;
    } else {
        *panel_active = 0;
    }

    abilities   = Party_GetAbilities(D_8014857A, D_8014857B, 0);
    ability     = abilities[D_8014857C];
    skill_order = (SkillOrder*)g_BattleChoicePanel;
    D_801484CC  = g_Abilities[ability].description;
    if (g_BattleChoicePhase == 0) {
        D_80148624 = 1;
        D_80148628 = D_80148574 + 7;
        D_8014862A = D_80148576 + D_8014857A * 13 + 26;
    } else {
        D_80148624 = 0;
    }

    buttons = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if (D_801ED648 != 2) {
        if (buttons & PADLleft) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            skill_order->ability_group--;
            g_BattleChoicePanel[9] = 0x32;
            if ((s8)skill_order->ability_group < 0) {
                skill_order->ability_group = 3;
            }
            skill_order->cursor = s_SkillOrderCursors[D_80148656][skill_order->ability_group];
        } else if (buttons & PADLright) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            skill_order->ability_group++;
            g_BattleChoicePanel[9] = 0x31;
            if (skill_order->ability_group >= 4) {
                skill_order->ability_group = 0;
            }
            skill_order->cursor = s_SkillOrderCursors[D_80148656][skill_order->ability_group];
        }
    }

    old_cursor = skill_order->cursor;
    if (buttons & PADLup) {
        if (skill_order->cursor != 0) {
            skill_order->cursor--;
        }
    } else if ((buttons & PADLdown) && skill_order->cursor < 9) {
        skill_order->cursor++;
    }
    if (old_cursor != skill_order->cursor) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    s_SkillOrderCursors[D_80148656][skill_order->ability_group] = skill_order->cursor;

    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        abilities = Party_GetAbilities(skill_order->party_slot, skill_order->ability_group, 0);
        ability   = abilities[skill_order->cursor];
        if (ability == 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        } else if (D_801ED648 == 0) {
            if (func_801AF5B0(g_BattleChoicePanel[8], skill_order->party_slot, ability) == 0) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            } else if (g_Abilities[ability].targeting_flags & ABILITY_TARGET_ALL) {
                result     = func_801E7D20(g_CharSlot[g_PartyFieldOrder[skill_order->party_slot]], 0, ability, 0);
                D_801ED654 = result;
                if (result == 1 || result == 5) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 9));
                } else {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                }
            } else {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
                    task                          = &g_MenuPanelTasks[MENU_START_PANEL_ITEMS + i];
                    task->active                  = 1;
                    task->handler                 = 6;
                    task->mode                    = 0;
                    task->state                   = 10;
                    task->pos.x                   = 320;
                    task->pos.y                   = 62 + i * 54;
                    task->unk_0A                  = i;
                    task->unk_0B                  = 0;
                    task->unk_0C                  = 0;
                    g_MenuPanelTasks[i + 4].state = 7;
                }
                g_BattleChoicePhase      = 4;
                D_80148624               = 1;
                D_801485DC               = 0;
                D_80148658[0]            = 0;
                skill_order->swap_cursor = skill_order->cursor;
                D_80148651++;
            }
        } else if (func_801AF5B0(g_BattleChoicePanel[8], skill_order->party_slot, ability) != 0) {
            D_8014865B               = 0;
            skill_order->swap_cursor = skill_order->cursor;
            D_80148651 += 2;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        }
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        skill_order->cursor      = 0xFF;
        skill_order->swap_cursor = 0xFF;
        D_80148651--;
    }
}
#else
INCLUDE_ASM(func_801D78FC);
#endif
