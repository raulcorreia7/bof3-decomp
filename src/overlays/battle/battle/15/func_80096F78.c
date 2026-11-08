#include "battle_15.h"

MATCH void func_80096F78(void) {
    u8* temp = Message_GetText(0x4000);
    Battle_AddMessage(2, 0xFF, temp);
    *(u8*)&g_Battle.ui_state += 1;
}
