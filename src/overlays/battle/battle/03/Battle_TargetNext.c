#include "battle_03.h"

/* func_801DB5CC */
MATCH u32 Battle_TargetNext(u32 start_slot) {
    u8 i;
    u8 slot;

    if ((u8)start_slot < 3) {
        i = start_slot;
        do {
            slot = i;
            if (Battle_SlotIsBlocked(slot) == 0) {
                return slot;
            }
            i++;
        } while (i < 3);
        for (i = 0; i < (u8)start_slot; i++) {
            slot = i;
            if (Battle_SlotIsBlocked(slot) == 0) {
                return slot;
            }
        }
    } else {
        i = start_slot;
        if ((u8)start_slot < 11) {
            do {
                slot = i;
                if (Battle_SlotIsBlocked(slot) == 0) {
                    return slot;
                }
                i++;
            } while (i < 11);
        }
        for (i = 3; i < (u8)start_slot; i++) {
            slot = i;
            if (Battle_SlotIsBlocked(slot) == 0) {
                return slot;
            }
        }
    }
    return 0xFF;
}
