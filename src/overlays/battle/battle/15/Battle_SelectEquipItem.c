#include "battle_15.h"

/* The command ring holds sixteen handles. */
#define BATTLE_RING_SLOT_MASK 0xF

/* func_80099B74 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_SelectEquipItem(void) {
    s32  pad;
    u16* pad_state;
    u16  keys;
    u32  resource;
    u8*  resource_id;
    u8   slot;
    u16  choice;
    u8   prev;
    u8*  slot_cursor;
    u8   next;
    /* FAKE: retail reserves 0x20 unused frame bytes. */
    FAKE_STACK_PADS(u8, 0x28);

    if (g_BattlePanelMode == 0) {
        D_801485DC = 1;
        D_801485E0 = (u16)D_801485BC + 6;
        D_801485E2 = (u16)D_801485BE + ((g_BattleEquipSlot * 0xD) + 0x57);
    } else {
        D_801485DC = 0;
    }
    resource = 0x32;
    if (D_8014862E == 0) {
        resource = 0x30;
    }
    resource_id                                                       = UI_MessageGetText(resource);
    g_BattleMessages[((D_801EC328 - 1) & BATTLE_RING_SLOT_MASK)].text = resource_id;
    pad_state                                                         = &g_PadStates[0].pressed;
    pad                                                               = INPUT_REPEATED(*pad_state, (PADLup | PADLdown));
    keys                                                              = *pad_state;
    if (keys & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_BattlePanelMode   = 1;
        g_BattleChoicePhase = 3;
        D_80148624          = 0;
        D_801483C0          = 1;
        D_801485DC          = 0;
        g_Battle.ui_step    = 1;
        g_Battle.ui_mode    = 0;
        return;
    }
    if (keys & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (g_BattleTargetCursorCol != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            slot                                                                     = BATTLE_ACTIVE_MEMBER->slot;
            g_Game.members[slot].u.turn.damage_flags.volatile_value                  = g_Game.members[slot].u.turn.damage_flags.volatile_value | BATTLER_DAMAGE_UNK_14;
            g_Game.members[slot].u.turn.command.id                                   = (u16)g_BattleTargetCursorCol;
            choice                                                                   = (u16)g_BattleTargetCursorCol;
            g_BattleActorTurn->command.id                                            = choice;
            resource_id                                                              = UI_MessageGetText(Item_GetDescription((s32)(choice >> 8), choice & BYTE_MASK) & HALF_MASK);
            BATTLE_SELECTION_RECORD_HANDLE((D_801EC328 - 1) & BATTLE_RING_SLOT_MASK) = resource_id;
            D_80148597                                                               = 2;
            g_BattlePanelMode                                                        = 1;
            D_801485DC                                                               = 0;
            D_80148624                                                               = 0;
            D_801483C0                                                               = 1;
            g_Battle.ui_step                                                         = 7;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    }
    if ((pad & PADLup) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        slot_cursor  = &g_BattleEquipSlot;
        prev         = *slot_cursor - 1;
        *slot_cursor = prev;
        if ((s8)prev < 0) {
            *slot_cursor = 5;
        }
    }
    if ((pad & PADLdown) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        slot_cursor  = &g_BattleEquipSlot;
        next         = *slot_cursor + 1;
        *slot_cursor = next;
        if ((s8)next >= 6) {
            *slot_cursor = 0;
        }
    }
}
#else
INCLUDE_ASM(Battle_SelectEquipItem);
#endif
