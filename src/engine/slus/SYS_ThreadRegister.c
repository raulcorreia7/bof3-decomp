#include "engine/slus/slus.h"

/*
 * stores one callback entrypoint in the requested slot and marks it
 * ready for thread open state `2`.
 */
MATCH void SYS_ThreadRegister(s32 callback_slot, Callback callback) {
    D_80143B40[callback_slot].callback = callback;
    D_80143B40[callback_slot].state    = CALLBACK_SLOT_OPEN;
}
