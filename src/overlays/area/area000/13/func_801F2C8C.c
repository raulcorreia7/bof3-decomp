#include "area000_13.h"

MATCH void func_801F2C8C(void) {
    SELF(Actor)->direction = g_CurrentActor->unk_79;
    Script_DispatchSelector(SELF(Actor)->direction);
}
