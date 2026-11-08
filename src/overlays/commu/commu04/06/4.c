#include "commu04_06.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

/* The commu04 overlay entry: the shared commu step byte selects the handler,
 * then the menu panels refresh while the game state is still zero. */
MATCH void func_801D0C04(void) {
    g_Commu04States[D_801F294C]();
    if (g_GameStateIndex == GAME_REQUEST_IDLE) {
        Menu_UpdatePanelTasks();
    }
}

MATCH void func_801D0C5C(void) {
    SYS_DISPATCH_BYTE(g_Commu04Step0Funcs, D_801F294D);
}

MATCH void func_801D0C98(void) {
    u8* state = &g_GameStateIndex;

    if (*state != 2) {
        Message_StartAreaMessage(0x60);
        *state = 2;
        D_801F294D += 1;
    }
}

MATCH void func_801D0CF4(void) {
    if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
        Menu_ResetPanelTasks();
        func_801D16A4();
        D_801D1774 = 4;
        D_801F294D += 1;
    }
}

INCLUDE_ASM(func_801D0D4C);

MATCH void func_801D11DC(void) {
    if (D_801D1774 < 4U) {
        D_801D1774 += 1;
    }
    UI_DrawWindow(0x14, (0x12 - (D_801D1774 * 0xC)) & 0xFFFE, 0x118, 0x13, 0xF2, g_WindowStyle);
    UI_DrawWindowOutline(0x16, 0x14 - (D_801D1774 * 0xC), 0x113, 0xF, 0);
    if (g_MenuPanelTasks[0].state == 0) {
        Menu_ResetPanelTasks();
        Message_StartAreaMessage(0x5F);
        g_GameStateIndex = GAME_REQUEST_MESSAGE;
        D_801F294C += 1;
    }
}

INCLUDE_ASM(func_801D12C8);

INCLUDE_ASM(func_801D1568);

INCLUDE_ASM(func_801D1628);

#include "overlays/commu/Fairy_AdvanceStep.h"

/* blocker: tail store order and a typed BattleOwnerKind view; first diff: sb zero,%lo(D_80148332) at 0x801D16D4. */
INCLUDE_ASM(func_801D16A4);
