/* Every step re-reads the scratchpad cell. */
#define FAKE_DECL_SELF_VOLATILE
#include "area087_13.h"
#include "overlays/area/shared/WorldMap_SelectKeyScript.h"

MATCH void func_801F3120(void) {
    Actor* scratch;
    Actor* check;
    s32    key;
    /* FAKE: retail keeps the table offset in a1. */
    FAKE_REG(u32, i, "a1");
    u32 next;
    u32 mode;
    u8  state;
    u32 window;
    u32 window_span;

    WORLD_MAP_SELECT_KEY_SCRIPT(D_801F4DAC);
}
