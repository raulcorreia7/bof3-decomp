#include "engine/slus/slus.h"

/* forwards the byte at **cursor to Item_VitalHas and returns its low 8 bits. */
MATCH s32 Game_HasVitalItem(u8** cursor) {
    return Item_VitalHas(**cursor) & BYTE_MASK;
}
