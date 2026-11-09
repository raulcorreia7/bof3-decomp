#include "engine/slus/slus.h"

/* reports bit **cursor of the D_80145548 mask. */
MATCH s32 func_8015B83C(u8** cursor) {
    return SYS_TestFlag((u8*)&D_80145548, **cursor) & BYTE_MASK;
}
