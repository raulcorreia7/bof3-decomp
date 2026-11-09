#include "battle_15.h"

MATCH void func_80098C18(void) {
    u16 held;
    s32 trigger;

    held = g_InputPressed;
    if ((held & g_InputMasks[BATTLE_INPUT_CANCEL]) != 0u) {
        g_Battle.ui_state = 4u;
        return;
    }
    if ((held & g_InputMasks[BATTLE_INPUT_CONFIRM]) != 0u) {
        g_Battle.ui_state = 3u;
        return;
    }
    trigger = INPUT_REPEATED(held, INPUT_DIRECTIONAL);
    if ((trigger & (PADLup | PADLdown)) != 0) {
        if ((Item_GetFlags(g_MenuPanelTasks[16].unk_0A, D_801C893C[g_MenuPanelTasks[16].unk_0A][g_MenuPanelTasks[16].unk_0C]) & 0x80u) != 0u) {
            if (func_8009AF7C() != 0u) {
                g_BattleActorTurn->command.target = 0u;
            } else {
                g_BattleActorTurn->command.target = Battle_TargetNext(0);
            }
            /* FAKE: byte pointer access keeps the address in a register so the
             * store merges into the shared SND_PlayCue delay slot. */
            *(u8*)&g_Battle.ui_state += 1;
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            return;
        }
    }
    if ((trigger & PADLright) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetNext(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(+1)) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
    if ((trigger & PADLleft) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetPrev(func_801DD7D8(g_Battle.enemy_count + 2, 3, ACTOR_TARGET_STEP(-1)) & BYTE_MASK);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}
