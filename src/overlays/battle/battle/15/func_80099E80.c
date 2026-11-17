#include "battle_15.h"

MATCH void func_80099E80(void) {
    u16 packed;
    s32 flags;

    packed = g_Game.members[g_BattleMessageSlot[5] & BYTE_MASK].u.turn.command.id;
    flags  = Item_GetFlags(packed >> 8, packed & BYTE_MASK);
    if ((flags & ITEM_SHOW_ANIMATION) != 0) {
        if ((flags & ITEM_STORY_ITEM) != 0) {
            g_Battle.ui_step = 9;
        } else {
            g_Battle.ui_step = 8;
        }
        g_Battle.ui_state = 0;
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 3));
        return;
    }
    if ((flags & ITEM_USABLE_MENU) != 0) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_BOTH_SIDES;
    } else if ((flags & ITEM_STORY_ITEM) != 0) {
        if ((flags & ITEM_SHOW_NAME) != 0) {
            g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
        } else {
            g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
        }
    } else {
        g_BattleActorTurn->command.target = g_BattleMessageSlot[5];
    }
    g_Battle.ui_step  = 8;
    g_Battle.ui_state = 3;
}
