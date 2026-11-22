#include "area000_13.h"

MATCH void func_801F2C8C(void) {
    TASK(Actor)->direction = g_CurrentActor->unk_79;
    Script_DispatchSelector(TASK(Actor)->direction);
}
