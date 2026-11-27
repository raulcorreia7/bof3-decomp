#include "battle_15.h"

/* The command ring holds sixteen handles. */
#define BATTLE_RING_SLOT_MASK 0xF

/* Runs the equipment slot list: steps the slot cursor with wrap, queues the chosen item for the active member or backs out to the command ring. */
MATCH void Battle_SelectEquipItem(void) {
    s32  repeated;
    u16* pad_state;
    u16  pressed;
    u16  choice;
    u8   unused[0x28]; /* 40 bytes of frame the function never touches */

    if (g_UiPanelTasks[18].state == 0) {
        g_UiPanelTasks[19].active = 1;
        g_UiPanelTasks[19].pos.vx = g_UiPanelTasks[18].pos.vx + 6;
        g_UiPanelTasks[19].pos.vy = (u16)(g_UiPanelTasks[18].pos.vy + ((g_UiPanelTasks[18].unk_0A * 0xD) + 0x57));
    } else {
        g_UiPanelTasks[19].active = 0;
    }
    g_BattleMessages[((D_801EC328 - 1) & BATTLE_RING_SLOT_MASK)].text = UI_MessageGetText(D_8014862E == 0 ? 0x30 : 0x32);
    pad_state                                                         = &g_PadStates[0].pressed;
    repeated                                                          = INPUT_REPEATED(*pad_state, (PADLup | PADLdown));
    pressed                                                           = *pad_state;
    if (pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[18].state  = 1;
        g_UiPanelTasks[16].state  = 3;
        g_UiPanelTasks[21].active = 0;
        g_UiPanelTasks[4].active  = 1;
        g_UiPanelTasks[19].active = 0;
        g_Battle.ui_step          = 1;
        g_Battle.ui_mode          = 0;
        return;
    }
    if (pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (g_BattleTargetCursorCol != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_Game.members[BATTLE_ACTIVE_MEMBER->slot].u.turn.damage_flags.value |= BATTLER_DAMAGE_UNK_14;
            g_Game.members[BATTLE_ACTIVE_MEMBER->slot].u.turn.command.id      = g_BattleTargetCursorCol;
            /* g_BattleTargetCursorCol is this panel cell. */
            choice                                                            = g_UiPanelTasks[18].u.battle.cursor;
            g_BattleActorTurn->command.id                                     = choice;
            g_BattleMessages[((D_801EC328 - 1) & BATTLE_RING_SLOT_MASK)].text = UI_MessageGetText(Item_GetDescription(choice >> 8, choice & BYTE_MASK) & HALF_MASK);
            g_UiPanelTasks[18].state                                          = 1;
            g_UiPanelTasks[17].state                                          = 2;
            g_UiPanelTasks[19].active                                         = 0;
            g_UiPanelTasks[21].active                                         = 0;
            g_UiPanelTasks[4].active                                          = 1;
            g_Battle.ui_step                                                  = 7;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    }
    if (repeated & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[18].unk_0A--;
        if ((s8)g_UiPanelTasks[18].unk_0A < 0) {
            g_UiPanelTasks[18].unk_0A = 5;
        }
    }
    if (repeated & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        g_UiPanelTasks[18].unk_0A++;
        if ((s8)g_UiPanelTasks[18].unk_0A >= 6) {
            g_UiPanelTasks[18].unk_0A = 0;
        }
    }
}
