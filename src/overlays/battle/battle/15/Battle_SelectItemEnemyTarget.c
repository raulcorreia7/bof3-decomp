#include "battle_15.h"

/* func_80098C18 */
MATCH void Battle_SelectItemEnemyTarget(void) {
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
            if (func_8009AF7C() != 0u) {
                g_BattleActorTurn->command.target = 0u;
            } else {
                g_BattleActorTurn->command.target = Battle_TargetNext(0);
            }
            /* FAKE: byte pointer access keeps the address in a register so the
             * store merges into the shared SND_SEPlay delay slot. */
            g_Battle.ui_mode += 1;
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            return;
        }
    }
    if ((trigger & PADLright) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetNext(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetPrev(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
}
