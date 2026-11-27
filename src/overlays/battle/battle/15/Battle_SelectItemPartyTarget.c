#include "battle_15.h"

/* applies battle-selection cursor input: a held confirm/cancel pair jumps to a selection phase, a flagged
 * secondary-panel entry consumes the 0x5000 triggers, and the D-pad scrolls the active slot with the move cue.
 */
/* func_80098DC4 */
MATCH void Battle_SelectItemPartyTarget(void) {
    u16 held;
    s32 trigger;

    held = g_PadStates[0].pressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_mode = 4u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_mode = 3u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    if ((trigger & (PADLup | PADLdown)) != 0) {
        if ((Item_GetFlags(g_UIPanelTasks[16].unk_0A, g_ItemCategoryIds[g_UIPanelTasks[16].unk_0A][g_UIPanelTasks[16].unk_0C]) & ITEM_USABLE_MENU) != 0u) {
            g_BattleActorTurn->command.target = Battle_TargetNext(3);
            g_Battle.ui_mode -= 1u;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            return;
        }
    }
    if ((trigger & PADLright) != 0) {
        if ((func_8009AF7C() & BYTE_MASK) != 0u) {
            g_BattleActorTurn->command.target = func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1));
        } else {
            g_BattleActorTurn->command.target = Battle_TargetNext(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if ((trigger & PADLleft) != 0) {
        if ((func_8009AF7C() & BYTE_MASK) != 0u) {
            g_BattleActorTurn->command.target = func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1));
        } else {
            g_BattleActorTurn->command.target = Battle_TargetPrev(func_801DD7D8(g_Battle.party_count - 1, 0, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}
