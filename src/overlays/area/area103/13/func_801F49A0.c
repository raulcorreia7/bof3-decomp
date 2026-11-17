#include "area103_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F49A0(s32 phase) {
    g_Task->header.step = phase;
}
#else
INCLUDE_ASM(func_801F49A0);
#endif
