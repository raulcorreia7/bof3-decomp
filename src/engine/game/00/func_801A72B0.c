#include "game_00.h"

MATCH void func_801A72B0(void* packed_selector) {
    D_80143F4E = (FIELD(u8, packed_selector, 0x0u) >> 4);
    ((void (*)(u8))Area_StartScrollRoute)(FIELD(u8, packed_selector, 0x1u));
}
