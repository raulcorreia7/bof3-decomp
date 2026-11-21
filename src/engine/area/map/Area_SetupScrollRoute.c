#include "engine/game/00/game_00.h"

/* func_801A72B0 */
/* Starts the scroll route a type 0xC record selects. */
MATCH void Area_SetupScrollRoute(void* packed_selector) {
    D_80143F4E = (FIELD(u8, packed_selector, 0x0u) >> 4);
    ((void (*)(u8))Area_StartScrollRoute)(FIELD(u8, packed_selector, 0x1u));
}
