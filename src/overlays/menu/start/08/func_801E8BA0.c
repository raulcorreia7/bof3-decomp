#include "start_08.h"

MATCH s32 func_801E8BA0(void) {
    s32  bit_index;
    u8*  counter_byte;
    u8*  bitset;
    u8*  counter_address;
    u16* global_counter;

    Item_Add(ITEM_CAT_ITEM, ITEM_FAERIE_TIARA, 1, 0);
    bit_index       = GAME_NONE;
    bitset          = g_SceneEventFlags;
    counter_address = &D_8014869D;
    /* FAKE: keep pointer in register. */
    FAKE_USE(counter_address);
    counter_byte = counter_address;
    /* FAKE: keep saved pointer live. */
    FAKE_USE(counter_byte);
    global_counter      = &g_GameEntrySubstate;
    g_MenuStep.sub_step = 0xA;
    *counter_byte       = 0xB9;
    *global_counter += 1;
    do {
        if (SYS_TestFlag(bitset, bit_index) != 0) {
            break;
        }
        bit_index -= 1;
        *counter_byte -= 1;
    } while (bit_index >= 246);
    D_80145040 = g_Game.members[0].pos.x.fixed;
    D_80145044 = g_Game.members[0].pos.y.fixed;
    D_80145048 = g_GameAreaId;
    return 0;
}
