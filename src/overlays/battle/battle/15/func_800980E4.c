#include "battle_15.h"

MATCH void func_800980E4(void) {
    u8  result;
    u8* game_ram;

    result                              = Battle_FindSelectableSlotForward(3);
    g_BattleMessageTurn->command.target = result;

    BattleStageAttackNameMessage(2, 0);

    g_BattleSelectionLatch = 1;
    g_InputRepeatButtons   = 0;
    game_ram               = (u8*)(u8*)(EFFECT_BANK_80140000);
    game_ram[0x62E3]       = (game_ram[0x62E3] + 1u);
}
