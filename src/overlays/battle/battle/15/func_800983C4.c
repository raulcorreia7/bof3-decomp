#include "battle_15.h"

MATCH void func_800983C4(void) {
    u8* temp = Resource_GetText(0x4000);
    Battle_AddMessage(2, 0xFF, temp);
    *(u8*)&g_Battle.ui_state += 1;
}
