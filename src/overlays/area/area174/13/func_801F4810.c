#include "area174_13.h"
#include "overlays/area/shared/Actor_RunScriptRowStep.h"

MATCH void func_801F4810(void) {
    u8* bank;
    u8* table;
    u8* row;

    ACTOR_RUN_SCRIPT_ROW_STEP(SELF(Actor)->direction + 1);
}
