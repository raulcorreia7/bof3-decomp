#include "engine/slus/slus.h"

/*
 * stores one callback entrypoint in the requested slot and marks it
 * ready for thread open state `2`.
 */
MATCH void CallbackRegister(s32 slot_index, Callback callback) {
    D_80143B40[slot_index].callback = callback;
    D_80143B40[slot_index].state    = CALLBACK_SLOT_OPEN;
}
