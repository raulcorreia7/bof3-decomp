#include "game_00.h"

MATCH void func_801A852C(void) {
    s8* state;
    s32 bit_index;
    s32 seed;

    state = &D_801448EC;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            Message_StartAreaMessage((Item_Count(ITEM_CAT_ITEM, ITEM_FAERIE_TIARA, 0) & 0xFFFF) ? 0x21 : 0x20);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            (&D_801448EB)[1] += 1;
            break;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                D_801448EB = 0;
                *state     = 0;
            }
            break;
        case 2:
            if (g_GameStateIndex != *state) {
                bit_index = 0xFF;
                seed      = 0xB9;
                state += 0x63C;
                for (;;) {
                    if (SYS_TestFlag(state, bit_index) != 0) {
                        break;
                    }
                    bit_index--;
                    seed--;
                    if (bit_index < 246) {
                        break;
                    }
                }
                D_80145040 = D_80145EC4;
                D_80145044 = D_80145EC8;
                D_80145048 = g_GameAreaId;
                Game_RequestAreaChange(seed & 0xFFFF, 0x430000, 0x160000, 4);
                g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
                Game_ClearScriptActive();
                D_801448EB = 0;
                D_801448EC = 0;
            }
            break;
    }
}
