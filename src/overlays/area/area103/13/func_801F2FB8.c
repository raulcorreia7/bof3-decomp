#include "area103_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2FB8(void* row) {
    TASK(Actor)->param.actor_slot = (u8)(u32)row;
}
#else
INCLUDE_ASM(func_801F2FB8);
#endif
