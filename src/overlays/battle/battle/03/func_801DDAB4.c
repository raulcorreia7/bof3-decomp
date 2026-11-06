#include "battle_03.h"

MATCH void func_801DDAB4(u32 status) {
    if ((status & 0x80u) != 0u) {
        GFX_AllocPaletteFade((void*)SP_REF(volatile void*, 0x44u), -6, -10, 0, 0);
    }
}
